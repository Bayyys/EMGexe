/*数据处理部分
 * 1. 包含滤波器：1）高通滤波器 2）带通滤波器 3）陷波器
 *    除了高通滤波器采用一阶IIR滤波器外，其他滤波器采用iir库中计算，阶数受 全局常量 const 决定
 * 2. 包含数据处理 1）最大最小值计算 2）均方根RMS计算 3）平均均值（RMS）计算 4）FFT计算
 *    FFT点数由常量 FFT_N决定
 */
/*   可改参数：
 *      1) FFT点数：FFT_N
 *      2) 滤波器阶数：order
 *      3）滑动RMS窗长：rms_length
 *      4）滑动RMS窗长重叠长度（不推荐更改，不推荐重叠）：rms_w_overlength
 */



#include "signalprocess.h"


SignalProcess::SignalProcess(int ch_number,int perch_data_number, double sample_rate):
    FFT_N(sample_rate),
    channel_number(ch_number),
    per_channel_data_number(perch_data_number),
    sampleRate(sample_rate)
{
    notch_enable = true;
    band_enable = true;
    hpass_enable = true;
    rms_enable = true;
    rms_length = 50;//窗长使得窗正好能移动到100个点中的最后一个点，10,20,50为宜
    rms_w_overlength = 10;//重叠长度使得窗正好能移动到100个点中的最后一个点，10个为宜//实际非重叠窗，这个参数无用
    count_y_in_dataForFFT = 0;
    notch_freq = 50.0;
    notch_freq1 = 100.0;
    notch_freq2 = 150.0;
    notch_freq3 = 200.0;
    notch_bandwidth = 10.0;
    band_fl=20.0;
    band_fh=180.0;


    initial();
}

SignalProcess::~SignalProcess(){
    free(fftout->data);
    free(fftout->size);
    delete fftout;
    fftout = nullptr;
    free(fftin->data);
    free(fftin->size);
    delete fftin;
    fftin = nullptr;
    for(int channel=0; channel<channel_number; ++channel){
        delete bp_filter[channel];
        delete bs_filter[channel];
        delete bs_filter1[channel];
        delete bs_filter2[channel];
        delete bs_filter3[channel];
        delete hp_filter[channel];
        bp_filter[channel] =nullptr;
        bs_filter[channel] =nullptr;
        bs_filter1[channel] =nullptr;
        bs_filter2[channel] =nullptr;
        bs_filter3[channel] =nullptr;
        hp_filter[channel] =nullptr;
    }
}

void SignalProcess::allocateSpaceForVector2D(QVector<QVector<double>>& vector, int first_size,int second_size)
{
    vector.resize(first_size);
    for (int i = 0; i<first_size; ++i){
        vector[i].resize(second_size);
    }
}

void SignalProcess::fillVectorDoubleZero(QVector<QVector<double>>& vector)
{
    int x_size = vector.size();
    if(x_size == 0)
        return;
    int y_size = vector[0].size();
    for(int i = 0; i<x_size; ++i){
        for(int j = 0 ;j<y_size;++j){
            vector[i][j]=0.0;
        }
    }
}

void SignalProcess::copyData(QVector<QVector<double>>& data_in){
    for(int channel = 0; channel<channel_number; ++channel){
        for(int i = 0; i < per_channel_data_number; ++i){
            y_out[channel][i]=data_in.at(channel).at(i);
        }
    }
}

void SignalProcess::reallocate(){
    allocateSpace();
    setupFilter();
}

void SignalProcess::allocateSpace(){
    bp_filter.resize(channel_number);
    bs_filter.resize(channel_number);
    bs_filter1.resize(channel_number);
    bs_filter2.resize(channel_number);
    bs_filter3.resize(channel_number);
    hp_filter.resize(channel_number);
    allocateSpaceForVector2D(y_notch, channel_number, per_channel_data_number);
    allocateSpaceForVector2D(y_band, channel_number, per_channel_data_number);
    allocateSpaceForVector2D(y_hpass, channel_number, per_channel_data_number);
    allocateSpaceForVector2D(y_out, channel_number, per_channel_data_number);
    min.resize(channel_number);
    max.resize(channel_number);
    rms.resize(channel_number);

    fftout->data = (double *)calloc((unsigned int)FFT_N, sizeof(double));
    fftout->size = (int *)calloc((unsigned int)2, sizeof(int));
    fftout->canFreeData = false;
    fftout->allocatedSize = FFT_N;

    fftin->data = (double *)calloc((unsigned int)FFT_N, sizeof(double));
    fftin->size = (int *)calloc((unsigned int)2, sizeof(int));
    fftin->size[0]=1;fftin->size[1]=FFT_N;
    fftin->numDimensions = 1;
    fftin->allocatedSize = FFT_N;
    fftin->canFreeData = false;

    allocateSpaceForVector2D(fft_x,channel_number,FFT_N/2);
    allocateSpaceForVector2D(fft_y,channel_number,FFT_N/2);
    allocateSpaceForVector2D(y_in_dataForFFT,32,FFT_N);//固定FFT_N个点做FFT，存储FFT_N个数据

    for(int channel=0; channel<channel_number; ++channel){
        bp_filter[channel] = new Iir::ChebyshevI::BandPass<order,Iir::DirectFormII>;
        bs_filter[channel] = new Iir::ChebyshevI::BandStop<order,Iir::DirectFormII>;
        bs_filter1[channel] = new Iir::ChebyshevI::BandStop<order,Iir::DirectFormII>;
        bs_filter2[channel] = new Iir::ChebyshevI::BandStop<order,Iir::DirectFormII>;
        bs_filter3[channel] = new Iir::ChebyshevI::BandStop<order,Iir::DirectFormII>;
        hp_filter[channel] = new Iir::Butterworth::HighPass<2,Iir::DirectFormII>;
    }
}

void SignalProcess::setupFilter(){
    for(int channel =0; channel<channel_number; ++channel){
        bs_filter[channel]->setup(sampleRate,notch_freq,notch_bandwidth,1.0);
        bs_filter1[channel]->setup(sampleRate,notch_freq1,notch_bandwidth,1.0);
        bs_filter2[channel]->setup(sampleRate,notch_freq2,notch_bandwidth,1.0);
        bs_filter3[channel]->setup(sampleRate,notch_freq3,notch_bandwidth,1.0);
    }
    for(int channel=0; channel<channel_number; ++channel){
        bp_filter[channel]->setup(sampleRate,(band_fh+band_fl)/2.0,band_fh-band_fl,1.0);
    }
    for(int channel=0; channel<channel_number; ++channel){
        hp_filter[channel]->setup(sampleRate,1.0);
    }
}

//  初始化内存分配和滤波器建立，使用该类数据处理功能需先运行该函数
void SignalProcess::initial(){
    fftout = new emxArray_real_T;
    fftin = new emxArray_real_T;
    allocateSpace();
    setupFilter();
}

//仅当参数变化时做出反应。若已经分配过内存，则需要更新参数并重新分配，否则更新参数即可。
void SignalProcess::setChArg(int ch_number, int per_channel_number){
    if(channel_number != ch_number  ||  per_channel_data_number != per_channel_number){
        //释放空间
        for(int channel=0; channel<channel_number; ++channel){
            delete bp_filter[channel];
            delete bs_filter[channel];
            delete bs_filter1[channel];
            delete bs_filter2[channel];
            delete bs_filter3[channel];
            delete hp_filter[channel];
            bp_filter[channel] = nullptr;
            bs_filter[channel] = nullptr;
            bs_filter1[channel] = nullptr;
            bs_filter2[channel] = nullptr;
            bs_filter3[channel] = nullptr;
            hp_filter[channel] = nullptr;
        }
        free(fftout->data);
        free(fftin->data);
        free(fftout->size);
        free(fftin->size);

        channel_number = ch_number;
        per_channel_data_number = per_channel_number;
        count_y_in_dataForFFT = 0;

        reallocate();
    }
}

void SignalProcess::setSampleRate(double sample_rate){
    if(sampleRate != sample_rate){
        sampleRate = sample_rate;
        FFT_N = sample_rate;
        count_y_in_dataForFFT = 0;
        allocateSpaceForVector2D(y_in_dataForFFT,32,FFT_N);
        allocateSpaceForVector2D(fft_x,channel_number,FFT_N/2);
        allocateSpaceForVector2D(fft_y,channel_number,FFT_N/2);
        free(fftout->data);
        free(fftin->data);
        fftout->data = (double *)calloc((unsigned int)FFT_N, sizeof(double));
        fftout->allocatedSize = FFT_N;
        fftin->data = (double *)calloc((unsigned int)FFT_N, sizeof(double));
        fftin->allocatedSize = FFT_N;
        fftin->size[1]=FFT_N;

        setupFilter();
    }
}

/************ 信号处理  ********
 * 根据各个滤波器的使能进行滤波
 * 计算最小值，最大值，均方根值
 */
void SignalProcess::runProcess(QVector<QVector <double>>& data_in){
    if     (!hpass_enable && !notch_enable && !band_enable){
        copyData(data_in);
    }
    else if(!hpass_enable && !notch_enable &&  band_enable){
        runBandFilter(data_in);
        copyData(y_band);
    }
    else if(!hpass_enable &&  notch_enable && !band_enable){
        runNotchFilter(data_in);
        copyData(y_notch);
    }
    else if(!hpass_enable &&  notch_enable &&  band_enable){
        runNotchFilter(data_in);
        runBandFilter(y_notch);
        copyData(y_band);
    }
    else if( hpass_enable && !notch_enable && !band_enable){
        runHighPassFilter(data_in);
        copyData(y_hpass);
    }
    else if( hpass_enable && !notch_enable &&  band_enable){
        runHighPassFilter(data_in);
        runBandFilter(y_hpass);
        copyData(y_band);
    }
    else if( hpass_enable &&  notch_enable && !band_enable){
        runHighPassFilter(data_in);
        runNotchFilter(y_hpass);
        copyData(y_notch);
    }
    else {
        runHighPassFilter(data_in);
        runNotchFilter(y_hpass);
        runBandFilter(y_notch);
        copyData(y_band);
    }

    if(rms_enable){
        //平均整流需在计算最大最小之前以保证最大最小值计算的是RMS处理之后的数据
        runRMS(y_out);//直接修改的data_in，传入的data_in即为y_out,这里无需执行copyData()
    }
    //启用平均整流则不再计算RMS
    else{
        calculateRMS(y_out);
    }
    calculateMinMax(y_out);
}

/************ 陷波  ********
 */
void SignalProcess::setNotchFilter(bool notchEnable,double notchFreq , double bandwidth)
{
    notch_enable = notchEnable;
    notch_bandwidth = bandwidth;
    notch_freq = notchFreq;
    if(notchEnable){
        setupFilter();
    }
}
void SignalProcess::runNotchFilter(QVector<QVector <double>>& data_in){
    for(int i=0; i<per_channel_data_number; ++i){
        for(int channel=0; channel<channel_number; ++channel){
            if(channel<channel_number-1)
            {
                y_notch[channel][i] = bs_filter[channel]->filter(data_in.at(channel).at(i));
                y_notch[channel][i] = bs_filter1[channel]->filter(y_notch.at(channel).at(i));
                y_notch[channel][i] = bs_filter2[channel]->filter(y_notch.at(channel).at(i));
               // y_notch[channel][i] = bs_filter3[channel]->filter(y_notch.at(channel).at(i));
            }
            else
            {
                y_notch[channel][i] =data_in.at(channel).at(i);
            }

        }
    }
}

/************ 带通  ********
 *
 */
void SignalProcess::setBandFilter(bool bandEnable, double fl,double fh)
{  
    if(fl<fh){
        band_enable = bandEnable;
        band_fl = fl;
        band_fh = fh;
    }
    else{
        band_enable = false;
    }
    if(band_enable){
        setupFilter();
    }
}
void SignalProcess::runBandFilter(QVector<QVector <double>>& data_in)
{
    for(int i=0; i<per_channel_data_number; ++i){
        for(int channel = 0; channel < channel_number; ++channel){
            if(channel <channel_number-1)
            {
                 y_band[channel][i] = bp_filter[channel]->filter(data_in.at(channel).at(i));
            }
            else
            {
                y_band[channel][i] = data_in.at(channel).at(i);
            }


        }
    }
}

/************ 高通滤波  ********
 * 固定截止频率为1 Hz
 */
void SignalProcess::setHighPassFilter(bool enable){
    hpass_enable = enable;
    if(band_enable){
        setupFilter();
    }
}
void SignalProcess::runHighPassFilter(QVector<QVector <double>>& data_in)
{
    for(int i=0; i<per_channel_data_number; ++i){
        for(int channel = 0; channel < channel_number; ++channel){
            if(channel<channel_number-1)
            {
                y_hpass[channel][i] = hp_filter[channel]->filter(data_in.at(channel).at(i));
            }
            else
            {
                y_hpass[channel][i] = data_in.at(channel).at(i);
            }
        }
    }
}

/************ 平均 RMS ，适用于glazer算法 ********
 *  求取RMS的窗长为20个点，1k采样率下即20ms
 *  rms_w_overlength:重叠窗长；rms_length:窗长
 *  这里默认per_channel_data_number为20的倍数，如果不是，需修改算法
 */
void SignalProcess::setRMS(bool enable){
    rms_enable = enable;
}
int SignalProcess::getRMSWindowLength(void){
    return rms_length;
}
int SignalProcess::getRMSWindowLengthOver(void){
    return rms_w_overlength;
}
void SignalProcess::runRMS(QVector<QVector<double>>& data_in){
    for(int channel =0; channel<channel_number; ++channel){
        int w_number = per_channel_data_number/rms_length;//计算一次数据量需要计算平均RMS的次数（没有重叠，窗长和步长均为rms_length）
        for(int w_count=0; w_count<w_number; ++w_count){
            double result = 0;
            for(int i = 0; i<rms_length; ++i){
                result += pow(data_in.at(channel).at(w_count*rms_length+i),2);
            }
            result = sqrt(result/rms_length);
            data_in[channel][w_count] = result;//将结果储存于data_in的前w_number个空间中
        }
    }
}

/************ 计算最大，最小值  *********/
void SignalProcess::calculateMinMax(QVector<QVector<double>>& data_in){
    //如果启用rms，则计算rms变换之后的最大最小值
    int w_number = rms_enable?(per_channel_data_number/rms_length):per_channel_data_number;
    for(int channel =0; channel<channel_number; ++channel){
        min[channel]  = data_in.at(channel).at(0);
        max[channel]  = data_in.at(channel).at(0);
        for(int i = 1; i<w_number; ++i){
            if(data_in[channel][i]<min[channel])
                min[channel] = data_in.at(channel).at(i);
            if(data_in[channel][i]>max[channel]){
                max[channel] = data_in.at(channel).at(i);
            }
        }
    }
}
/************ 计算RMS  *********/
/*
 * */
void SignalProcess::calculateRMS(QVector<QVector<double>>& data_in){
    for(int channel =0; channel<channel_number; ++channel){
        double result = 0;
        for(int i = 0; i <per_channel_data_number; ++i){
            result += pow(data_in.at(channel).at(i),2);
        }
        rms[channel] = sqrt(result/per_channel_data_number);
    }
}
/************ 计算FFT  *********/
/*  这里固定做1000点FFT(算法补0),以保证1kHz采样率下频谱分辨率达到1Hz。
 *  分辨率 = 采样率/点数。更高的采样率意味着更低的频谱分辨率，请自行注意。
 * */
void SignalProcess::runFFT(){
    int channel_fft = channel_number<32?channel_number:32;
    if(count_y_in_dataForFFT + per_channel_data_number >FFT_N){
        qDebug("Error:1000 can not be divided with no remainder by perchannelnumber");
        return;
    }
    else{
        //复制计算好的数据到y_in_dataForFFT，填充满FFT_N个数据后计算FFT;
        for(int channel=0; channel<channel_fft; ++channel){
            for(int i = 0; i<per_channel_data_number; ++i){
                y_in_dataForFFT[channel][i+count_y_in_dataForFFT] = y_out.at(channel).at(i);
            }
        }
        count_y_in_dataForFFT += per_channel_data_number;
        if(count_y_in_dataForFFT == FFT_N){
            for(int channel = 0; channel<channel_fft; ++channel){
                for(int i = 0; i<FFT_N; ++i){
                    fftin->data[i] = y_in_dataForFFT.at(channel).at(i);
                }
                FFT(fftin,FFT_N,fftout);
                for(int i=0; i<FFT_N/2;++i){
                    //fft_y[channel][i] = *(fftout->data+i);
                    fft_y[channel][i] = fftout->data[i];
                    fft_x[channel][i] = double(i);
                }               
            }
            count_y_in_dataForFFT = 0;
        }
    }
}

/* 暂不可用！
 * 利用库sp++进行的stft运算。
 * sp++ 需要使用命名域 splab。需要修改内部头文件声明外部头文件格式<fft.h>为"fft.h"
 * sp++ 算法内部借鉴了matlab算法，运行时开辟栈空间。而栈空间无法满足要求。
    例如运行10分钟（600s），数据量（1k采样率）600000个点，作窗长1000，滑动999的stft，需开辟空间为600000*1000=6e8 double空间，按树有左右结点计，一个存储点需要12字节。最终空间大约72e8 byte。内存空间不足。
 */



#include "stft.h"
#include "ui_stft.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

#include "Iir.h"


STFT::STFT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::STFT)
{
    ui->setupUi(this);
    this->setWindowTitle("STFT");

    filePath = "";
    sampleRate = 1000.0;
    window_size = 1000;
    overlap = 500;
    channel = 1;

    ui->sampleRate_Edit->setText("1000");
    ui->win_len_Edit->setText("1000");
    ui->overlap_Edit->setText("999");
    ui->overlap_Edit->setEnabled(false);
}

STFT::~STFT()
{
    delete ui;
}

void STFT::openFileDialog(){
    QString Path = QFileDialog::getOpenFileName();
    if(QMessageBox::Ok == QMessageBox::information(this,"确认选择的文件",QString(tr("选中的文件为："))+Path,
                                                   QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
        filePath = Path;
        ui->statusbar->showMessage(filePath);
    }
    else{
        QMessageBox::information(this,"","请重新选择文件",QMessageBox::Ok);
    }
}

void STFT::run_m(){
    if ("" == filePath){
        QMessageBox::information(this,"","请先选择文件",QMessageBox::Ok);
        return;
    }
    sampleRate = ui->sampleRate_Edit->text().toDouble();
    if(50 <= abs(sampleRate)){
        QMessageBox::information(this,"","采样率错误",QMessageBox::Ok);
        return;
    }
    window_size = ui->win_len_Edit->text().toUInt();
    if(0 == window_size){
        QMessageBox::information(this,"","窗长错误",QMessageBox::Ok);
        return;
    }
    ui->overlap_Edit->setText(QString::number(window_size-1));
    switch (ui->channelChoose_Combo->currentIndex()) {
        case 0: channel = 1; break;
        case 1: channel = 2; break;
        case 2: channel = 3; break;
        case 3: channel = 4; break;
        case 4: channel = 5; break;
        case 5: channel = 6; break;
        case 6: channel = 7; break;
        case 7: channel = 8; break;
        case 8: channel = 9; break;
        case 9: channel = 10; break;
        case 10: channel = 11; break;
        case 11: channel = 12; break;
        case 12: channel = 13; break;
        case 13: channel = 14; break;
        case 14: channel = 15; break;
        case 15: channel = 16; break;
        case 16: channel = 17; break;
        case 17: channel = 18; break;
        case 18: channel = 19; break;
        case 19: channel = 20; break;
        case 20: channel = 21; break;
        case 21: channel = 22; break;
        case 22: channel = 23; break;
        case 23: channel = 24; break;
        case 24: channel = 25; break;
        case 25: channel = 26; break;
        case 26: channel = 27; break;
        case 27: channel = 28; break;
        case 28: channel = 29; break;
        case 29: channel = 30; break;
        case 30: channel = 31; break;
        case 31: channel = 32; break;
        default:
            channel = 1;break;
    }
    //QMessageBox::warning(this,"debug","sampleRate:"+QString::number(sampleRate)+
    //                    "win_size:"+QString::number(window_size)+
    //                    "overlap"+QString::number(overlap)+
    //                    "channel"+QString::number(channel),QMessageBox::Yes);
    decodeFile(channel);
    dostft();
}

void STFT::decodeFile(unsigned int channel_number){
    //根据文件大小初始化容器
    QFileInfo fileInfo(filePath);
    int length = static_cast<int>(fileInfo.size())/144;
    qDebug("packet number:%d",length);
    data = new Vector<double>(length);
    //data.resize(length);
    //读取文件数据
    QFile * fp;
    fp = new QFile(filePath);
    if(!fp->open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"warning", "can't open destination data file",QMessageBox::Yes);
        return;
    }
    QByteArray tmpdata = fp->readAll();
    qDebug("read data done");
    fp->close();
    //数据解码及滤波处理
    Iir::ChebyshevI::BandPass<eeg_order,Iir::DirectFormII> bp_filter;
    Iir::ChebyshevI::BandStop<eeg_order,Iir::DirectFormII> bs_filter;
    bp_filter.setup(sampleRate,(50.0+1.0)/2.0,50.0-1.0,1.0);
    bs_filter.setup(sampleRate,50.0,10.0,1.0);

    int packet = 0;
    for(Vector<double>::iterator it = data->begin(); packet<length; ++packet, ++it){
        double r4 = sin(2.0*PI*20.0*0.001*packet)+sin(2.0*PI*90.0*0.001*packet)+sin(2.0*PI*50.0*0.001*packet);
        double after_bp = bp_filter.filter(r4);
        double after_bs = bs_filter.filter(after_bp);
        *it = after_bs;
    }

    /*
    int packet = 0;
    for(Vector<double>::iterator it = data->begin(); packet<length; ++packet, ++it){
        QByteArray tmpdata_144bytes = tmpdata.left(144);
        tmpdata.remove(0,144);
        QByteArray _4byte = tmpdata_144bytes.remove(0,8+(channel_number-1)*4).left(4);
        int perchannel_data = (_4byte[0]&0x000000FF)|((_4byte[1]&0x000000FF)<<8)|((_4byte[2]&0x000000FF)<<16)|((_4byte[3]&0x000000FF)<<24);
        double r4 = ((double)perchannel_data)/24.0;//24倍增益
        double after_bp = bp_filter.filter(r4);
        double after_bs = bs_filter.filter(after_bp);
        *it = after_bs;
    }
    */
    qDebug("decode done");
}

void STFT::dostft(){
    Vector<double> g = hamming(int(window_size),1.0);
    Matrix<complex<double>> *coefs = new Matrix<complex<double>>;
    *coefs = wft(*data,g);//window move 1 point , overlap =1 point
    delete data;
    g.~Vector();
    //The column represents time, and row represents frequency
    abs_result = splab::abs(*coefs);
    delete coefs;
    int m = abs_result.rows()/2;//频谱对称，取一半
    int n = abs_result.cols();
    drawSTFT(n,m);
}
/*
 *  i,nx:time,col ;  j,ny:fre,row
 */
void STFT::drawSTFT(int nx, int ny){
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->xAxis->setLabel("time(10e-3s)");
    ui->widget->yAxis->setLabel("Freq(Hz)");


    QCPColorMap *colorMap = new QCPColorMap(ui->widget->xAxis,ui->widget->yAxis);
    colorMap->data()->setSize(nx,ny);
    colorMap->data()->setRange(QCPRange(0,double(nx)),QCPRange(0,double(ny)));// and span the coordinate range -4..4 in both key (x) and value (y) dimensions

    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for(int i = 0; i<nx; ++i){
        for(int j = 0; j<ny; ++j){
            colorMap->data()->setData(i,j,abs_result(j,i));
         }
    }
    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->widget);
    ui->widget->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget);
    ui->widget->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->widget->rescaleAxes();
    ui->widget->replot();
}

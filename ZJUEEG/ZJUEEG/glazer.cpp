/* glazer计算与绘图窗口，集成自QMainWindow
 * 计算滑动RMS，RMS参数由window_size,和overlap决定
 * 还需加入参数控制
 */

#include "glazer.h"
#include "ui_glazer.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QTime>

#include "Iir.h"

Glazer::Glazer(QString filename,double sample_rate,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Glazer)
{
    ui->setupUi(this);
    this->setWindowTitle("glazer");
    this->setWindowIcon(QIcon(":/images/zju.png"));

    des_file = filename;
    sampleRate = sample_rate;
    channel = 1;
    draw_flag =false;

    ui->widget->setStyleSheet("background-color:white");
    ui->widget->installEventFilter(this);//安装事件过滤器，使widget事件不会被主窗口滤除。
    //开线程进行数据处理
    processThread = new QThread(this);
    process = new DataProcess(des_file,sampleRate,channel,this);
    process->moveToThread(processThread);
    connect(processThread, SIGNAL(started()), process,SLOT(runProcess()));
    connect(process, SIGNAL(resultReady(double,int,QVector<double>*)),this,SLOT(dataProcessDone(double,int,QVector<double>*)));
}

Glazer::~Glazer()
{
    delete processThread;
    delete process;
    delete progressDialog;
    delete ui;
}

void Glazer::drawGlazer(){
    QPainter painter(ui->widget);
    QPen pen;
    int x_winsize = ui->widget->width();
    int y_winsize = ui->widget->height();
    double x_interval = (static_cast<double>(x_winsize)-10.0-10.0)/(static_cast<double>(size_data)-1.0);
    double y_interval = (static_cast<double>(y_winsize)-10.0-10.0)/200.0;
    //绘制坐标
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(QPointF(10,y_winsize-10),QPointF(x_winsize-10,y_winsize-10));
    painter.drawLine(QPointF(10,y_winsize-10),QPointF(10,10));
    //x轴刻度
    double x_time = static_cast<double>((size_data-1)*(window_size-overlap))/1000.0;
    int N_30s = x_time/30;
    QTime xtime(0,0,0);
    for(int i= 1; i<=N_30s ; ++i){
        painter.drawText(static_cast<double>(x_winsize-20)/x_time*30.0*static_cast<double>(i)-20,y_winsize,xtime.addSecs(30*i).toString("hh:mm:ss"));
        painter.drawLine(QPointF(static_cast<double>(x_winsize-20)/x_time*30.0*static_cast<double>(i)+10,10),QPointF(static_cast<double>(x_winsize-20)/x_time*30.0*static_cast<double>(i)+10,y_winsize-10));
    }
    //y轴刻度
    painter.drawText(10,static_cast<double>(y_winsize)-10.0 - y_interval*50.0,"50");
    painter.drawText(10,static_cast<double>(y_winsize)-10.0 - y_interval*100.0,"100");
    painter.drawText(10,static_cast<double>(y_winsize)-10.0 - y_interval*150.0,"150");
    painter.drawText(10,static_cast<double>(y_winsize)-10.0 - y_interval*200.0,"200");
    painter.drawText(10,y_winsize,"0");
    painter.drawLine(QPointF(10,static_cast<double>(y_winsize)-10.0 - y_interval*50.0),QPointF(x_winsize-10,static_cast<double>(y_winsize)-10.0 - y_interval*50.0));//50uV
    painter.drawLine(QPointF(10,static_cast<double>(y_winsize)-10.0 - y_interval*100.0),QPointF(x_winsize-10,static_cast<double>(y_winsize)-10.0 - y_interval*100.0));//100uV
    painter.drawLine(QPointF(10,static_cast<double>(y_winsize)-10.0 - y_interval*150.0),QPointF(x_winsize-10,static_cast<double>(y_winsize)-10.0 - y_interval*150.0));//150uV
    painter.drawLine(QPointF(10,static_cast<double>(y_winsize)-10.0 - y_interval*200.0),QPointF(x_winsize-10,static_cast<double>(y_winsize)-10.0 - y_interval*200.0));//200uV

    //绘制数据
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    polyline = new QPointF[size_data];

    int k = 0;
    for(QVector<double>::iterator it = dataDraw->begin(); it != dataDraw->end(); ++k,++it){
        polyline[k] = QPointF(10.0+static_cast<double>(k)*x_interval,static_cast<double>(y_winsize)-10.0- *it*y_interval);
    }
    painter.drawPolyline(polyline,size_data);
    //draw_flag = false;
}

/****槽函数****
 * 运行运算
 */
void Glazer::runGlazer(){
    ui->runButtom->setEnabled(false);
    //生成进度条
    progressDialog = new QProgressDialog("请等待","取消",0,0,this);
    progressDialog->setWindowModality(Qt::WindowModal);//进度条读取过程不响应其他窗口操作
    progressDialog->setBaseSize(400,400);
    connect(progressDialog,SIGNAL(canceled()),this,SLOT(abortRun()));
    //启动多线程
    processThread->start();
}
/**** 槽函数 ****
 * 中止计算
 */
void Glazer::abortRun(){
    processThread->quit();
    delete progressDialog;
    ui->runButtom->setEnabled(true);
}
/****槽函数*****
 * 数据处理结束，使能绘图
 */
void Glazer::dataProcessDone(double maxValue, int size_dataAfterRMS, QVector<double> *dataAfterRMS){
    progressDialog->close();
    dataDraw = dataAfterRMS;
    max_data = maxValue;
    size_data = size_dataAfterRMS;
    draw_flag = true;
    update();
}
/**** 重载事件滤波器 *****
 * 筛选窗口部件的绘图事件，实现自己的绘图功能 drawGlazer（）
 */
bool Glazer::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->widget ){
        if(event->type() == QEvent::Paint){
            if(draw_flag){
                drawGlazer();
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    return Glazer::eventFilter(watched,event);//其他绘图事件交给父类处理
}

DataProcess::DataProcess(QString filename,double sample_rate, unsigned int channelNumber, Glazer *glazer_ui)
{
    des_file = filename;
    sampleRate = sample_rate;
    channel = channelNumber;
    parent_ui = glazer_ui;
}

void DataProcess::runProcess(){
    //根据文件大小初始化容器
    QFileInfo fileInfo(des_file);
    int length = fileInfo.size()/144;
    QVector<double> data;
    data.resize(length);
    //读取文件数据
    QFile * fp;
    fp = new QFile(des_file);
    if(!fp->open(QIODevice::ReadOnly)){
        QMessageBox::warning(parent_ui,"warning", "can't open glazer data file",QMessageBox::Yes);
        return;
    }
    QByteArray tmpdata = fp->readAll();
    fp->close();
    //数据解码及滤波处理
    Iir::ChebyshevI::BandPass<higher_order,Iir::DirectFormII> bp_filter;
    Iir::ChebyshevI::BandStop<higher_order,Iir::DirectFormII> bs_filter;
    bp_filter.setup(sampleRate,(500.0+20.0)/2.0,(500.0-20.0-10.0),1.0);
    bs_filter.setup(sampleRate,50.0,10.0,1.0);
    for(int packet = 0; packet<length; ++packet){
        QByteArray tmpdata_144bytes = tmpdata.left(144);
        tmpdata.remove(0,144);
        QByteArray _4byte = tmpdata_144bytes.remove(0,8+(channel-1)*4).left(4);
        int perchannel_data = (_4byte[0]&0x000000FF)|((_4byte[1]&0x000000FF)<<8)|((_4byte[2]&0x000000FF)<<16)|((_4byte[3]&0x000000FF)<<24);
        double r4 = ((double)perchannel_data)/24.0;//24倍增益
        double after_bp = bp_filter.filter(r4);
        double after_bs = bs_filter.filter(after_bp);
        data[packet] = after_bs;
    }
    //RMS处理
    int window_move_times = (length-window_size)/(window_size-overlap)+1;
    dataAfterRMS.resize(window_move_times);
    size_dataAfterRMS = window_move_times;
    maxValue = 0;
    for(int move_count = 0; move_count< window_move_times; ++move_count){
        double rms_value = 0;
        for(int i = 0; i<window_size; ++i){
            rms_value += data.at(move_count*(window_size-overlap)+i)*data.at(move_count*(window_size-overlap)+i);
        }
        rms_value = sqrt(rms_value/window_size);
        //if(move_count<50){
        //    //去除滤波算法收敛之前的大幅震荡
        //    dataAfterRMS[move_count] = 0;
        //    rms_value = 0;
        //}
        //else{
        //    dataAfterRMS[move_count] = rms_value;
        //}
        dataAfterRMS[move_count] = rms_value;
        maxValue = maxValue>rms_value?maxValue:rms_value;
    }

    emit resultReady(maxValue,size_dataAfterRMS,&dataAfterRMS);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QCloseEvent>
#include <QTime>
#include <QLabel>
#include <QAbstractNativeEventFilter>
#include <windows.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

#include "connect.h"
#include "signalprocess.h"
#include "glazer.h"
#include "qcustomplot/qcustomplot.h"
#include "channelset.h"
#include "fftset.h"
#include "stft.h"
#include "portset.h"
#include "wifiset.h"
#include "wordengine.h"
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QMediaPlayer>
#include "QSoundEffect"
#include "glazer_analyse.h"

extern QReadWriteLock lock_mark;
extern QReadWriteLock lock_data_from_wifi;
extern QReadWriteLock lock_elect_lead_off;

class myframe;
class QCheckBox;
class TimeCount;
class TimeCountdown_main;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QVector<QVector<double>> data;
    QVector<bool> elect_off_p;
    QVector<bool> elect_off_n;
    QVector<qint8> mark;
    QVector<QString> vector_port_name;
    QSerialPort *serial_port = nullptr;

    void openPortSetWidget();
    void openConnectSetWidget();
    CommnicateBoard *tcp;
    TimeCountdown_main *count_second;

protected:
    void closeEvent( QCloseEvent * event);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private slots:
    void stop_m();
    void run_m();
    void run_set();
    void openChannelSetWidget();
    void openFFTSetWidget();
    void openSTFTWidget();
    //void openConnectSetWidget();
    //void openPortSetWidget();
    void openWifiSetWidget();
    void openDebugWidget();
    void changePwmFreq();
    void openfile();
    void connectWifi();
    void connectToBardDone();
    void connectToBardAbort();
    void getPort();
    void getIp();
    void changeChannelNumber();
    void changeSampleRate();
    void changeNotchFilter();
    void changeBandFilter();
    void changeHpassFilter();
    void changeFhFilter();
    void changeFlFilter();
    void changeAmplititude();
    void changeTimeScale();
    void changeChannelEnable();
    void changeSavePath();
    void changeSingleBipolarElect();
    void changeRMS();
    void changeCommandReturn();
    void sendCommand();
    void showhelpmessage();
    void glazerStart();
    void glazerEnd();
    void glazerResult();
    void initFFTWidget(bool,double,double,double,double);
    void portSetDone();
    void wifiSetDone(QString,QString,QString,QString);
    void updateIniFile();
    void slot_change_answer_mode();
    //*******************//
    void changeSelfControl();
    void changeFFTSet();

    void fftset();
    void on_action_config_triggered();

    void on_action_reconfig_triggered();
    void set_glazer_time();
    void save_report();
    void glazer_mid_stop();

signals:
    void changeFFtWidget(bool self_control,double xmin,double xmax,double ymin,double ymax);
    void sendsignal();//这个函数用户向主界面通知关闭的消息

private:

    void initVectorDrawFrame();
    void initVectorQCheckBox();
    void drawFFT();
    void flush();
    void initCom();
    void scanPort();
    void send_chnumber_samplerate();


    Ui::MainWindow *ui;

    QString readFilePath;
    quint16 port;
    QString ip;
    bool notchFilter;
    bool bandFilter;
    bool hpassFilter;
    bool rms_enable;
    int rms_w_count;//rms 窗计数
    int rms_w_length;//rms 窗长
    double fl_bandPass;
    double fh_bandPass;
    int channel_number;
    int per_channel_number;
    double sampleRate;  
    bool running;
    bool runFileData;
    bool singleElectMode;
    bool fft_selfControl;
    double fft_xmin,fft_xmax,fft_ymin,fft_ymax;
    bool find_com;

    QFile *filtered_data;
    QPen pen[32];
    QVector<bool>  channel_enable_map;

    SignalProcess *dataProcess;
    QVector<myframe *>  drawframe;
    QVector<QCheckBox *> checkbox;
    QFile *readFile;
    QString glazerfilename;
    //QVector<QByteArray> command_vector;//channel_number;sample_rate;
    //QVector<bool> send_command_return;

    Glazer* glazer_window;
    TimeCount* glazertimer;
    STFT* stft_window = nullptr;
    QThread *p_tcp_thread = nullptr;



    QSoundEffect *player;
    Glazer_analyse *glazer;
    QMessageBox* glazer_msgbox;
    //QThread *glazer_thread;
    //glazer1 = new Glazer_analyse;
    //bool glazer_started;

    //qint32 port_bandrate;

};
//计时功能，继承QThread来实现多线程。
class TimeCount:public QThread
{
     Q_OBJECT
public:
    TimeCount(QLabel *label){
        p_label = label;
        timepass = 0;
        running = true;
        zerotime = new QTime(0,0,0);
    }
    ~TimeCount(){
        delete zerotime;
    }
    void stopRun(){running =false;}
protected:
    void run(){
        while(running){
            p_label->setText(zerotime->addSecs(timepass).toString("hh:mm:ss"));
            sleep(1);
            timepass ++;
        }
    }
private:
    unsigned int timepass;
    bool running;
    QLabel *p_label;
    QTime *zerotime;

};

class TimeCountdown_main:public QThread
{
     Q_OBJECT
public:
    QTimer *timerdown;
    TimeCountdown_main(int timedown_min,int timedown_sec){
        //p_label = label;
        //stopcount=stop_count;
        //timepass = uint(timedown_sec);
        time_sec = timedown_sec;
        time_min = timedown_min;
        stopcount=timedown_min*60+timedown_sec;
        running = true;
        //connect(thread, SIGNAL(started()), timer,SLOT(start()));
    }
    ~TimeCountdown_main(){
       // delete timerdown;
    }
    //void startrun() {run();}
    void stopRun(){
        running =false;

    }
    int num;
protected:
    void run(){
        timerdown = new QTimer(); //不能给Timer指定父对象
        timerdown->start(1000);
        num=0;
        connect(timerdown, &QTimer::timeout, this, &TimeCountdown_main::count);
        //connect(timerdown, SIGNAL(timeout()), this, SLOT(count()), Qt::AutoConnection);
        //qDebug() << "threadrun: tid = " << QThread::currentThreadId(); //打印计时器所在的线程ID
        this->exec();
        qDebug() << "timer stoped";
    }

private slots:
   void count(){
        //while(running){
            num++;
            //p_label->setNum(num);
            //qDebug() << "count num = " << num;
            //qDebug() << "count: tid = " << QThread::currentThreadId(); //计时器调用槽函数所在的线程ID
            emit countdone();
            //test();
            if(num>=stopcount)
            {
                 qDebug() << "count stopped ";
                timerdown->stop();
                //QDateTime current_date_time1 = QDateTime::currentDateTime();
                //QString current_date = current_date_time.toString("yyyy-MM-dd");
                //QString current_time1 = current_date_time1.toString("hh:mm:ss.zzz ");
                emit totalcountdone();
                delete timerdown;
            }
            if(!running)
            {
                qDebug() << "count stopped ";
                timerdown->stop();
                delete timerdown;
            }

        //}
    }
signals:
    void countdone();
    void totalcountdone();
private:
    //unsigned int timepass;
    bool running;
   // QLabel *p_label;

    int time_sec;
    int time_min;
    int stopcount;

};


#endif // MAINWINDOW_H

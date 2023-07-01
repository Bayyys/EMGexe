/* 主流程
 * 通道数默认为32通道，支持最高通道数为256
 *
 *
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QColor>
#include <dbt.h>



#define MAX_CHANNEL_NUMBER 256
extern QString selected_port_name;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ZJU Bioelectricity Acquisition");
    this->setWindowIcon(QIcon(":/images/zju.png"));
    //初始化绘图部件容器
    channel_enable_map.resize(MAX_CHANNEL_NUMBER);
    initVectorDrawFrame();
    initVectorQCheckBox();
    //初始化配置
    find_com = false;
    serial_port = new QSerialPort();

    ip = "10.10.10.1";
    port = 61613;
    ui->Port_lineEdit->setText("61613");

    notchFilter = true;
    bandFilter = true;
    hpassFilter = true;
    rms_enable = true; //
    rms_w_count = 0;
    rms_w_length = 0;
    fl_bandPass = 20.0;
    fh_bandPass = 180.0;
    per_channel_number = 125;//为了计算FFT,请保证能整除1000；不推荐修改（每次绘图用到的点数）
    channel_number = 32;
    sampleRate = 1000.0;
    running = false;
    runFileData = false;
    singleElectMode = false;

    //给data,elec_off_p,elec_off_n分配空间
    data.resize(channel_number);
    for(int i=0;i<channel_number;i++){
        data[i].resize(per_channel_number);
    }
    elect_off_p.resize(channel_number);
    elect_off_n.resize(channel_number);
    mark.resize(per_channel_number);

    dataProcess = new SignalProcess(channel_number,per_channel_number,sampleRate);
    // 注意，上位机作为服务端
    tcp = new CommnicateBoard(ip,port,Tcp_server,channel_number,static_cast<int>(sampleRate),ui->command_return_label);
    // 连接板子后触发改信号槽函数
    connect(this->tcp,SIGNAL(signal_board_start()),this,SLOT(connectToBardDone()));
    connect(this->tcp,SIGNAL(signal_tcp_abort()),this,SLOT(connectToBardAbort()));
    p_tcp_thread = new QThread(this);
    tcp->moveToThread(p_tcp_thread);
    p_tcp_thread->start();

   // ui->stopButton->setEnabled(false);
    ui->notch_checkBox->setCheckState(Qt::CheckState::Checked);  //默认开启陷波
    //ui->notch_checkBox->setEnabled(false);
    ui->notch_checkBox->setVisible(false);




    ui->hpass_checkBox->setCheckState(Qt::CheckState::Checked);

    ui->bandfilter_checkbox->setCheckState(Qt::CheckState::Checked);//默认开启带通滤波20-200Hz
    ui->comboBox->setCurrentIndex(1);
    //ui->comboBox->setEnabled(false);
    ui->comboBox->setVisible(false);
    ui->comboBox_2->setCurrentIndex(3);
   // ui->comboBox_2->setEnabled(false);
    ui->comboBox_2->setVisible(false);
   // ui->bandfilter_checkbox->setEnabled(false);
    ui->bandfilter_checkbox->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_7->setVisible(false);



    ui->hpass_checkBox->setCheckState(Qt::CheckState::Checked);//默认开启直流滤波
    //ui->hpass_checkBox->setEnabled(false);
    ui->hpass_checkBox->setVisible(false);

    ui->rms_checkBox->setCheckState(Qt::CheckState::Checked);//默认开启rms模式
    ui->rms_checkBox->setEnabled(false);
    ui->answer_mode_checkBox->setCheckState(Qt::CheckState::Checked);//默认开启应答
    ui->answer_mode_checkBox->setEnabled(false);
    ui->answer_mode_checkBox->setVisible(false);
    ui->command_return_label->setVisible(false);


    ui->comboBox_channel_number->setCurrentIndex(3);//默认32通道
    //ui->comboBox_channel_number->setEnabled(false);
    ui->comboBox_channel_number->setVisible(false);
    ui->label_14->setVisible(false);


    ui->sampleRate_comboBox->setCurrentIndex(2);//默认1000采样率
    //ui->sampleRate_comboBox->setEnabled(false);
    ui->sampleRate_comboBox->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);


    ui->command_return_checkBox->setEnabled(false); //默认不开启命令返回
    ui->command_return_checkBox->setVisible(false);

    ui->command_lineEdit->setVisible(false);
    ui->command_send_botton->setVisible(false);
    ui->command_help_pushButton->setVisible(false);



    ui->glazer_start->setEnabled(true);
    ui->glazer_stop->setEnabled(false);
    ui->glazer_result->setEnabled(false);
    //ui->sampleRate_comboBox->setEnabled(false);
    ui->electmode_pushButton->setEnabled(false);
    ui->command_lineEdit->setEnabled(false);
    ui->command_send_botton->setEnabled(false);
    ui->connect_type_label->setText("unconnect");
    ui->connect_type_label->setStyleSheet("color:rgb(250,0,0)");

    ui->glazer_result->setEnabled(false); //glazer 后分析不展示
    ui->glazer_result->setVisible(false);


    readFile = new QFile();

    //bool selfcontrol;
    fft_selfControl = true;
    fft_xmin = 0; fft_xmax = 100; fft_ymin = 0; fft_ymax = 1000;
    initFFTWidget(fft_selfControl,fft_xmin,fft_xmax,fft_ymin,fft_ymax);
    if(fft_selfControl){
        ui->coordinate_auto->setChecked(true);
        ui->Ymax->setEnabled(false);
        ui->Ymin->setEnabled(false);
        ui->Xmax->setEnabled(false);
        ui->Xmin->setEnabled(false);
        //selfcontrol = true;
    }
    else{
        ui->coordinate_auto->setChecked(false);
        ui->Ymax->setEnabled(true);
        ui->Ymin->setEnabled(true);
        ui->Xmax->setEnabled(true);
        ui->Xmin->setEnabled(true);
        ui->Ymax->setText(QString::number(fft_ymax,'f',2));
        ui->Ymin->setText(QString::number(fft_ymin,'f',2));
        ui->Xmax->setText(QString::number(fft_xmax,'f',2));
        ui->Xmin->setText(QString::number(fft_xmin,'f',2));
        //selfcontrol = false;
    }



    //command_vector.resize(2);
    //command_vector[0]="";
    //command_vector[1]="";//初始命令填充将在下面手动触发槽函数时完成
    //send_command_return.resize(2);
    //send_command_return[0]=false;
    //send_command_return[1]=false;

    //链接槽函数
    connect(ui->sampleRate_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changeSampleRate()));
    connect(ui->comboBox_channel_number,SIGNAL(currentIndexChanged(int)),this,SLOT(changeChannelNumber()));
    connect(ui->openfile_action, &QAction::triggered, this, &MainWindow::openfile);
    connect(ui->setChannel,SIGNAL(triggered(bool)),this,SLOT(openChannelSetWidget()));
    connect(ui->setFFT,SIGNAL(triggered(bool)),this,SLOT(openFFTSetWidget()));
    connect(ui->stft,SIGNAL(triggered(bool)),this,SLOT(openSTFTWidget()));
    connect(ui->setConnect,SIGNAL(triggered(bool)),this,SLOT(openConnectSetWidget()));
    connect(ui->set_port,SIGNAL(triggered(bool)),this,SLOT(openPortSetWidget()));
    connect(ui->set_wifi,SIGNAL(triggered(bool)),this,SLOT(openWifiSetWidget()));
    connect(ui->change_freq, SIGNAL(triggered(bool)),this,SLOT(changePwmFreq()));
    connect(ui->open_debug_win,SIGNAL(triggered(bool)),this,SLOT(openDebugWidget()));
    //connect(ui->action_config,SIGNAL(triggered(bool)),this,SLOT(openPortSetWidget()));
    //connect(ui->action_reconfig,SIGNAL(triggered(bool)),this,SLOT(openConnectSetWidget()));
    connect(ui->coordinate_auto,SIGNAL(stateChanged(int)),this,SLOT(changeSelfControl()));
    connect(ui->fftset_ok,SIGNAL(clicked(bool)),this,SLOT(changeFFTSet()));

    //读取默认配置，默认配置存储于运行目录下，命名为config.ini
    QString config_file_name = "config.ini";
    QFileInfo config_file_info(config_file_name);
    if(!config_file_info.isFile()){
        QSettings *p_ini = new QSettings(config_file_name,QSettings::IniFormat);
        p_ini->setValue("sample_rate_index", 2);
        p_ini->setValue("channel_number_index", 3);
        p_ini->setValue("band_rate", 4608000);
        p_ini->setValue("data_bit_index", 0);
        p_ini->setValue("stop_bit_index", 0);
        p_ini->setValue("amplititude_scale_index", 3);
        p_ini->setValue("time_scale_index", 2);
        p_ini->setValue("pwm_freq",1);
        p_ini->setValue("wifi_ssid","OpenBCI");
        p_ini->setValue("wifi_ip","192.168.1.1");
        p_ini->setValue("wifi_port","61613");
        p_ini->setValue("wifi_password","88888888");
        delete p_ini;
    }
    QSettings *p_ini = new QSettings(config_file_name,QSettings::IniFormat);
    ui->sampleRate_comboBox->setCurrentIndex(p_ini->value("sample_rate_index").toInt());
    ui->comboBox_channel_number->setCurrentIndex(p_ini->value("channel_number_index").toInt());
    ui->amplititude_comboBox->setCurrentIndex(p_ini->value("amplititude_scale_index").toInt());
    ui->time_comboBox->setCurrentIndex(p_ini->value("time_scale_index").toInt());
    ui->Port_lineEdit->setText(p_ini->value("wifi_port").toByteArray());
    ui->IP_lineEdit->setText(p_ini->value("wifi_ip").toByteArray());
    getIp();
    getPort();

    //隐藏除了第一页的所有TAB,如要隐藏多个tab****序号需要从大到小****
    int count = ui->tabWidget->count();
    for(int i = count - 1; i > 0 ; i--)
    {
    ui->tabWidget->removeTab(i);
    }
    //隐藏不需要的菜单栏
    ui->debug_menu->menuAction()->setVisible(false);
    ui->pwm_menu->menuAction()->setVisible(false);
    ui->menuWi_Fi->menuAction()->setVisible(false);
    ui->port_menu->menuAction()->setVisible(false);
    ui->process_menu->menuAction()->setVisible(false);
    ui->channel_menu->menuAction()->setVisible(false);

    //隐藏不需要的控件
    ui->connectButton->setVisible(false);
    //ui->horizontalSpacer_2->setVisible(false);

    ui->message_label->setVisible(false);
    ui->IP_lineEdit->setVisible(false);
    ui->Port_lineEdit->setVisible(false);
    ui->label_11->setVisible(false);

    ui->runButton->setEnabled(true);   // 使面板“运行”不可选
    ui->stopButton->setEnabled(false);   // 使面板“停止”可选
    ui->glazer_start->setEnabled(false);   // 使面板“glazer开始”可选
    //需要手动触发一次槽函数
    //changeRMS();
    changeSampleRate();
    changeChannelNumber();
    changeAmplititude();
    changeTimeScale();
    changeHpassFilter();

    //fl_bandPass = 20;
    //fh_bandPass = 100;
    changeBandFilter();
    //changeFhFilter();
    //changeFlFilter();
    changeNotchFilter();
    slot_change_answer_mode();
    player=new QSoundEffect(this);//加载播放器
    player->setSource(QUrl::fromLocalFile(":/media/Glazer2.wav"));  //Glazer音效
    //qDebug()<<player->status();
    //glazer_started = false;
    delete p_ini;


    //开启预处理数据缓存文件
    /*QString m_storePath = QDir::currentPath()+"/ZJUEEGDATA";
    filtered_data = new QFile(m_storePath+"/" + "filtered.txt");
    filtered_data->open(QIODevice::WriteOnly);*/
}

MainWindow::~MainWindow()
{
    updateIniFile();
    if(tcp!=nullptr){
        QByteArray data_send;
        data_send.append(static_cast<char>(0xaa));
        data_send.append(static_cast<char>(0x06));
        data_send.append(static_cast<char>(0x00));
        tcp->send_to_board(data_send);
    }
    if(serial_port!=nullptr){
        delete serial_port;
        serial_port = nullptr;
    }
    delete readFile;
    readFile =nullptr;
    if(tcp!=nullptr){
        delete tcp;
        tcp = nullptr;
    }
    delete dataProcess;
    dataProcess =nullptr;
    delete ui;
    ui = nullptr;
    if(p_tcp_thread!=nullptr){
        p_tcp_thread->quit();
        p_tcp_thread->wait();
        delete p_tcp_thread;
        p_tcp_thread=nullptr;
    }
    delete player;
}
void MainWindow::changeSelfControl()
{
    if(Qt::Checked == ui->coordinate_auto->checkState()){
        ui->Ymax->setEnabled(false);
        ui->Ymin->setEnabled(false);
        ui->Xmax->setEnabled(false);
        ui->Xmin->setEnabled(false);
        //selfcontrol = true;
    }
    else if(Qt::Unchecked == ui->coordinate_auto->checkState()){
        ui->Ymax->setEnabled(true);
        ui->Ymin->setEnabled(true);
        ui->Xmax->setEnabled(true);
        ui->Xmin->setEnabled(true);
        //selfcontrol = false;
    }
}
void MainWindow::changeFFTSet(){
    fftset();
    connect(this,SIGNAL(changeFFtWidget(bool,double,double,double,double)),this,SLOT(initFFTWidget(bool,double,double,double,double)));
    //initFFTWidget(true,fft_xmin,fft_xmax,fft_ymin,fft_ymax);
}

//初始化绘图部件容器
void MainWindow::initVectorDrawFrame(){
    drawframe.resize(MAX_CHANNEL_NUMBER);
    for(int i=1; i<=MAX_CHANNEL_NUMBER;++i){
        QString obj_name_frame = "widget_"+QString::number(i);
        myframe *p_frame = ui->tabWidget->findChild<myframe *>(obj_name_frame);
        drawframe[i-1] = p_frame;

    }
}
void MainWindow::initVectorQCheckBox(){
    checkbox.resize(MAX_CHANNEL_NUMBER);
    for(int i=1; i<=MAX_CHANNEL_NUMBER;++i){
        QString obj_name_checkbox = "checkBox_"+QString::number(i);
        QCheckBox *p_checkbox = ui->tabWidget->findChild<QCheckBox *>(obj_name_checkbox);
        checkbox[i-1] = p_checkbox;
        connect(checkbox[i-1],SIGNAL(stateChanged(int)),this,SLOT(changeChannelEnable()));
    }
}

/***************  UI 槽函数***********
 *   修改存储路径
 */
void MainWindow::changeSavePath()
{
    QString saveFilePath = QFileDialog::getExistingDirectory(this,tr("saveDir"),tr("c:/"),QFileDialog::ShowDirsOnly);
    ui->savepath_label->setText(saveFilePath);
    tcp->set_store_path(saveFilePath);
}
/***************  UI 槽函数***********
 *   使能陷波器
 */
void MainWindow::changeNotchFilter(){
    if(Qt::Checked == ui->notch_checkBox->checkState())
        notchFilter = true;
    else if(Qt::Unchecked == ui->notch_checkBox->checkState())
        notchFilter = false;
    QString a = notchFilter?"open":"close";
    ui->statusbar->showMessage("notchFilter: " + a);
    dataProcess->setNotchFilter(notchFilter);
}
/***************  UI 槽函数***********
 *   使能高通滤波器
 */
void MainWindow::changeHpassFilter(){
    if(Qt::Checked == ui->hpass_checkBox->checkState())
        hpassFilter = true;
    else if(Qt::Unchecked == ui->hpass_checkBox->checkState())
        hpassFilter = false;
    hpassFilter = true;
    dataProcess->setHighPassFilter(hpassFilter);
}

/***************  UI 槽函数***********
 *   使能带通滤波器
 */
void MainWindow::changeBandFilter(){
    if(Qt::Checked == ui->bandfilter_checkbox->checkState())
        bandFilter = true;
    else if(Qt::Unchecked == ui->bandfilter_checkbox->checkState())
        bandFilter = false;
    QString a = bandFilter?"open":"close";
    ui->statusbar->showMessage("bandFilter: " + a);
    fl_bandPass = 20;
    fh_bandPass = 180;
    dataProcess->setBandFilter(bandFilter,fl_bandPass,fh_bandPass);
}

/***************  UI 槽函数***********
 *   改变带通滤波器上限截止频率
 */
void MainWindow::changeFhFilter(){
    switch (ui->comboBox_2->currentIndex()){
    case 0: fh_bandPass = 50.0;break;
    case 1: fh_bandPass = 80.0;break;
    case 2: fh_bandPass = 100.0;break;
    case 3: fh_bandPass = 200.0;break;
    case 4: fh_bandPass = 500.0;break;
    default:fh_bandPass = 10000.0;
    }
    ui->statusbar->showMessage("fh: " + QString::number(fh_bandPass));
    dataProcess->setBandFilter(bandFilter,fl_bandPass,fh_bandPass);
}
/***************  UI 槽函数***********
 *   改变带通滤波器下限截止频率
 */
void MainWindow::changeFlFilter(){
    switch (ui->comboBox->currentIndex()){
    case 0: fl_bandPass = 1.0;break;
    case 1: fl_bandPass = 20.0;break;
    case 2: fl_bandPass = 50.0;break;
    case 3: fl_bandPass = 100.0;break;
    case 4: fl_bandPass = 150.0;break;
    default:fl_bandPass = 0.0;
    }
    ui->statusbar->showMessage("fl: " + QString::number(fl_bandPass));
    dataProcess->setBandFilter(bandFilter,fl_bandPass,fh_bandPass);
}
/***************  UI 槽函数***********
 *   启用RMS
 */
void MainWindow::changeRMS(){
    if(Qt::Checked == ui->rms_checkBox->checkState()){
        rms_enable = true;
        ui->glazer_start->setEnabled(true);
    }
    else if(Qt::Unchecked == ui->rms_checkBox->checkState()){
        rms_enable = false;
        ui->glazer_start->setEnabled(false);
        ui->glazer_stop->setEnabled(false);
        ui->glazer_result->setEnabled(false);
    }
    for(int channel = 0; channel <channel_number;channel++){
        drawframe[channel]->setRMS(rms_enable);
        drawframe[channel]->refreshPixmap();
    }
    QString a = rms_enable?"open":"close";
    ui->statusbar->showMessage("RMS: " + a);
    dataProcess->setRMS(rms_enable);
    rms_w_length = dataProcess->getRMSWindowLength();
    //int rms_w_length_cover = dataProcess->getRMSWindowLengthOver();///待修改
    rms_w_count = per_channel_number/rms_w_length;
    qDebug()<<"check rms state"<<rms_enable;
}
/***************  UI 槽函数***********
 *   glazer评估启动标识
 */
void MainWindow::glazerStart(){
    //glazer_started = true;
    glazerfilename = tcp->set_glazer_on(true);
    ui->glazer_start->setEnabled(false);
    ui->glazer_stop->setEnabled(true);
    ui->glazer_result->setEnabled(false);
    glazertimer = new TimeCount(ui->timer_label);

    //qDebug()<<"start"<<player->status();
    //glazer = new Glazer_analyse();
    //QDateTime current_date_time1 = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy-MM-dd");
    //QString current_time1 = current_date_time1.toString("hh:mm:ss.zzz ");
    player->play();
    count_second = new TimeCountdown_main(8,40);
    count_second->moveToThread(count_second);
    count_second->start();
    glazertimer->start();
    connect(count_second, SIGNAL(totalcountdone()), this, SLOT(glazerEnd()), Qt::AutoConnection);
    connect(count_second, SIGNAL(countdone()), this, SLOT(set_glazer_time()), Qt::AutoConnection);

    glazer = new Glazer_analyse();
    glazer -> QThread::moveToThread(glazer);
    glazer -> QThread::start();
    //glazer_thread = new QThread(this);
    //glazer->moveToThread(glazer_thread);
    //glazer_thread->start();
    connect(glazer, SIGNAL(glazer_done()), this, SLOT(save_report()), Qt::AutoConnection);
    connect(glazer, SIGNAL(mid_stopped()), this, SLOT(glazer_mid_stop()), Qt::AutoConnection);
    tcp->p_decode_process->glazer_store_path=glazer->return_path();
    tcp->p_decode_process->preRest=new QFile(glazer->return_path()+"/" + "preRest.txt");
    tcp->p_decode_process->preRest->open(QIODevice::WriteOnly);
    tcp->p_decode_process->Rapid=new QFile(glazer->return_path()+"/" + "Rapid.txt");
    tcp->p_decode_process->Rapid->open(QIODevice::WriteOnly);
    tcp->p_decode_process->Tonic=new QFile(glazer->return_path()+"/" + "Tonic.txt");
    tcp->p_decode_process->Tonic->open(QIODevice::WriteOnly);
    tcp->p_decode_process->Endur=new QFile(glazer->return_path()+"/" + "Endur.txt");
    tcp->p_decode_process->Endur->open(QIODevice::WriteOnly);
    tcp->p_decode_process->postRest=new QFile(glazer->return_path()+"/" + "postRest.txt");
    tcp->p_decode_process->postRest->open(QIODevice::WriteOnly);
    tcp->p_decode_process->glazer_whole=new QFile(glazer->return_path()+"/" + "glazer_whole.txt");
    tcp->p_decode_process->glazer_whole->open(QIODevice::WriteOnly);
}
void MainWindow::set_glazer_time(){

    tcp->p_decode_process->glazer_time = count_second->num;
    glazer->glazer_time=count_second->num;
    //qDebug()<<"tcp->p_decode_process->glazer_time"<<tcp->p_decode_process->glazer_time;
    //qDebug()<<"count_second->num"<<count_second->num;
}
void MainWindow::save_report(){

    WordEngine word;
    word.open(QDir::currentPath()+"/libs/template2021.dot");
    QString tag;
    QString replaced;
    for (int idx0 = 0; idx0 < 12; idx0++) {
       for (int idx1 = 0; idx1 < 12; idx1++) {
           tag="label"+QString::number(idx0+1,10)+"_"+QString::number(idx1+1,10);
           replaced = QString::number(glazer->AA_FB_Simplicity[idx0 + 32 * idx1], 'f', 2);
           //qDebug()<<replaced;
           word.replaceText(tag,replaced);
       }
     }
    word.save(glazer->return_path()+"/glazer_report.doc");

    glazer_msgbox->close();
    delete glazer_msgbox;
    QMessageBox::information(NULL,"OK","Glazer评估已完成，报告路径为"+glazer->return_path()+"/glazer_report.doc");
    if(glazer->glazer_done_state)
    {
        glazer->stopRun();
        glazer->quit();
        qDebug() << "glazer completed glazer thread ended ? = " <<  glazer->wait(); //打印线程是否在运行
        delete  glazer;
    }
}
void MainWindow::glazer_mid_stop()
{
    if(!glazer->glazer_done_state)
    {
        glazer->quit();
        qDebug() << "mid stopped glazer thread ended ? = " <<  glazer->wait(); //打印线程是否在运行
        delete  glazer;
    }
}

/***************  UI 槽函数***********
 *   glazer评估结束标识
 */
void MainWindow::glazerEnd(){
    //glazer_started = false;
    tcp->set_glazer_on(false);
    ui->glazer_start->setEnabled(true);
    ui->glazer_stop->setEnabled(false);
    ui->glazer_result->setEnabled(true);
    glazertimer->stopRun();
    glazertimer->quit();
    glazertimer->wait();
    delete glazertimer;
    glazertimer = nullptr;
    ui->timer_label->setText("00:00:00");
    player->stop();
    stop_m();
    if(count_second->num<515)
    {
        QMessageBox::information(NULL,"OK","Glazer评估未完成，无法生成报告!");
    }
    count_second->stopRun();
    count_second->quit();
    qDebug() << "count_second thread ended ? = " <<  count_second->wait(); //打印线程是否在运行
    if(count_second->num<115)
    {
        tcp->p_decode_process->preRest->close();
        tcp->p_decode_process->Rapid->close();
        tcp->p_decode_process->Tonic->close();
        tcp->p_decode_process->Endur->close();
        tcp->p_decode_process->postRest->close();
        tcp->p_decode_process->glazer_whole->close();
    }
    else if(count_second->num<220)
    {
        //tcp->p_decode_process->preRest->close();
        tcp->p_decode_process->Rapid->close();
        tcp->p_decode_process->Tonic->close();
        tcp->p_decode_process->Endur->close();
        tcp->p_decode_process->postRest->close();
        tcp->p_decode_process->glazer_whole->close();
    }
    else if(count_second->num<352)
    {
        //tcp->p_decode_process->preRest->close();
        //tcp->p_decode_process->Rapid->close();
        tcp->p_decode_process->Tonic->close();
        tcp->p_decode_process->Endur->close();
        tcp->p_decode_process->postRest->close();
        tcp->p_decode_process->glazer_whole->close();
    }

    else if(count_second->num<452)
    {
        //tcp->p_decode_process->preRest->close();
        //tcp->p_decode_process->Rapid->close();
        //tcp->p_decode_process->Tonic->close();
        tcp->p_decode_process->Endur->close();
        tcp->p_decode_process->postRest->close();
        tcp->p_decode_process->glazer_whole->close();
    }
    else if(count_second->num<520)
    {tcp->p_decode_process->postRest->close();
    tcp->p_decode_process->glazer_whole->close();}
    tcp->p_decode_process->glazer_whole->close();
    if(count_second->num<150)
    {
        glazer->stopRun();
        glazer->quit();
        qDebug() << "directly stopped glazer thread ended ? = " <<  glazer->wait(); //打印线程是否在运行
        delete  glazer;
    }
    if(!glazer->glazer_done_state)
    {
        glazer->stopRun();
    }
    if(count_second->num>512)
    {
        glazer_msgbox = new QMessageBox( this );
        //glazer_msgbox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        glazer_msgbox->setStandardButtons( QMessageBox::Ok );
        glazer_msgbox->setWindowTitle( tr("Glazer") );
        glazer_msgbox->setText( tr("Glazer 评估正在进行中，请稍候……") );
        glazer_msgbox->setModal( false ); // if you want it non-modal
        glazer_msgbox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) );
        glazer_msgbox->show();
    }

    count_second->num = 0;
    set_glazer_time();

    //glazer->run_process("postRest");
    /*if(!glazer->glazer_done_state)
    {
        glazer->stopRun();
        glazer->quit();
        qDebug() << "glazer thread ended ? = " <<  glazer->wait(); //打印线程是否在运行
        delete  glazer;
    }*/


    delete count_second;

}

/***************  UI 槽函数***********
 *   glazer评估输出结果
 */
void MainWindow::glazerResult(){
    glazer_window = new Glazer(glazerfilename,sampleRate);
    glazer_window->show();
}
/***************  UI 槽函数***********
 *   获取TCP连接端口号
 */
void MainWindow::getPort(){
    port = static_cast<quint16>(ui->Port_lineEdit->text().toInt(nullptr,10));
    ui->statusbar->showMessage("Port= "+ QString::number(port,10));
    tcp->wifi_update_port(port);
}
/***************  UI 槽函数***********
 *   获取TCP连接IP
 */
void MainWindow::getIp(){
    ip = ui->IP_lineEdit->text();
    ui->statusbar->showMessage("IP="+ip);
    tcp->wifi_update_ip(ip);
}
/***************  UI 槽函数***********
 *   转换是否需要OK答复的命令模式
 */
void MainWindow::slot_change_answer_mode(){
    if(Qt::Checked == ui->answer_mode_checkBox->checkState()){
        tcp->m_answer_mode = true;
    }
    else{
        tcp->m_answer_mode = false;
    }
}

/***************  UI 槽函数***********
 *   修改幅度量程
 */
void MainWindow::changeAmplititude(){
    int ampli_scale;
    switch(ui->amplititude_comboBox->currentIndex()){
    case 0: ampli_scale = 10;break;
    case 1: ampli_scale = 20;break;
    case 2: ampli_scale = 50;break;
    case 3: ampli_scale = 100;break;
    case 4: ampli_scale = 200;break;
    case 5: ampli_scale = 500;break;
    case 6: ampli_scale = 1000;break;
    case 7: ampli_scale = 2000;break;
    case 8: ampli_scale = 5000;break;
    case 9: ampli_scale = 10000;break;
    default: ampli_scale = 100;
    }
    for(int channel = 0; channel <channel_number;channel++){
        drawframe[channel]->setYscale(ampli_scale);
        drawframe[channel]->refreshScale();
    }
    ui->statusbar->showMessage("Amplititude Scale: " + QString::number(ampli_scale));
}
/***************  UI 槽函数***********
 *   修改时间量程
 */
void MainWindow::changeTimeScale(){
    int time_scale;
    switch(ui->time_comboBox->currentIndex()){
    case 0: time_scale = 500;break;
    case 1: time_scale = 1000;break;
    case 2: time_scale = 2000;break;
    case 3: time_scale = 5000;break;
    case 4: time_scale = 10000;break;
    case 5: time_scale = 20000;break;
    case 6: time_scale = 50000;break;
    default: time_scale = 1000;
    }
    for(int channel = 0; channel <channel_number;channel++){
        drawframe[channel]->setXscale(time_scale);
    }
    ui->statusbar->showMessage("Time Scale: " + QString::number(time_scale));
}
/***************  UI 槽函数***********
 *   修改绘图通道使能
 */
void MainWindow::changeChannelEnable(){
    QString enableChannel = "Enable channel:";

    for(int channel = 26; channel<MAX_CHANNEL_NUMBER; ++channel){
        channel_enable_map[channel] = false;
        drawframe[channel]->setVisible(false);
        checkbox[channel]->setVisible(false);
    }
    channel_enable_map[31] = true;
    drawframe[31]->setVisible(true);
    checkbox[31]->setVisible(true);
    for(int channel=0; channel<channel_number; channel++){
        if((Qt::Checked == checkbox[channel]->checkState()&&channel<26)||(Qt::Checked == checkbox[channel]->checkState()&&channel==31)){
            channel_enable_map[channel] = true;
            drawframe[channel]->setVisible(true);
            checkbox[channel]->setVisible(true);
        }
        else{
            channel_enable_map[channel] = false;
            drawframe[channel]->refreshPixmap();
            drawframe[channel]->setVisible(false);
            checkbox[channel]->setVisible(false);
        }

    }

    for(int i=0; i<channel_number; i++){
        if(i<26||i==31)
        {
            if(channel_enable_map[i]){
                enableChannel += (QString::number(i+1,10)+" ");
            }
        }

    }
    ui->statusbar->showMessage(enableChannel);
}
/***************  UI 槽函数***********
 *   连接板子后触发该函数
 */
void MainWindow::connectToBardDone(){
    ui->IP_lineEdit->setEnabled(false);
    ui->Port_lineEdit->setEnabled(false);
    //ui->sampleRate_comboBox->setEnabled(true);
    ui->electmode_pushButton->setEnabled(true);
    ui->command_lineEdit->setEnabled(true);
    ui->command_send_botton->setEnabled(true);
    if(tcp->m_connect_type == _wifi){
        ui->connect_type_label->setText("wifi");
        ui->connect_type_label->setStyleSheet("color:rgb(0,0,0)");
    }
    else if(tcp->m_connect_type == _serial_com){
        ui->connect_type_label->setText("serial_port");
        ui->connect_type_label->setStyleSheet("color:rgb(0,0,0)");
    }
}
void MainWindow::connectToBardAbort(){
    running = false;
    ui->runButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->command_return_checkBox->setEnabled(true);
    ui->comboBox_channel_number->setEnabled(true);
    ui->sampleRate_comboBox->setEnabled(true);
    if(rms_enable && ui->glazer_stop->isEnabled()){
        glazerEnd();
    }
    ui->IP_lineEdit->setEnabled(true);
    ui->Port_lineEdit->setEnabled(true);
    ui->electmode_pushButton->setEnabled(false);
    ui->command_lineEdit->setEnabled(false);
    ui->command_send_botton->setEnabled(false);

    ui->connect_type_label->setText("unconnect");
    ui->connect_type_label->setStyleSheet("color:rgb(255,0,0)");
    /*
    p_tcp_thread->quit();
    p_tcp_thread->wait();
    delete tcp;
    tcp = new CommnicateBoard(ip,port,Tcp_server,channel_number,static_cast<int>(sampleRate),ui->command_return_label);
    connect(this->tcp,SIGNAL(signal_board_start()),this,SLOT(connectToBardDone()));
    connect(this->tcp,SIGNAL(signal_tcp_abort()),this,SLOT(connectToBardAbort()));
    tcp->moveToThread(p_tcp_thread);
    p_tcp_thread->start();
    */
}
/***************  UI 槽函数***********
 *   更改采样率
 */
void MainWindow::changeSampleRate(){
    int index = 0x90;
    switch(ui->sampleRate_comboBox->currentIndex()){
    case 0: sampleRate = 250.0; index+=6;per_channel_number = 125;break;//50
    case 1: sampleRate = 500.0; index+=5;per_channel_number = 125;break;//100
    case 2: sampleRate = 1000.0;index+=4;per_channel_number = 250;break;//200
    case 3: sampleRate = 2000.0;index+=3;per_channel_number = 500;break;//400
    case 4: sampleRate = 4000.0;index+=2;per_channel_number = 1000;break;//800
    case 5: sampleRate = 8000.0;index+=1;per_channel_number = 2000;break;//1600
    case 6: sampleRate = 16000.0;per_channel_number = 4000;break;//16000
    default: sampleRate = 1000.0;index+=4;per_channel_number = 250;//200
    }
    ui->statusbar->showMessage("SampleRate: " + QString::number(sampleRate,'f',1)+"Hz");
    //QByteArray data_send;
    //data_send.append(static_cast<char>(0xaa));
    //data_send.append(static_cast<char>(0x03));
    //data_send.append(static_cast<char>(0x01));
    //data_send.append(static_cast<char>(index));
    //command_vector[1] = data_send;
    if(tcp->m_has_start_board){
        tcp->flush();
    }
    //rms_w_count = per_channel_number/rms_w_length;
    dataProcess->setSampleRate(sampleRate);
    dataProcess->setChArg(channel_number,per_channel_number);
    for(int i=0;i<channel_number;i++){
        data[i].resize(per_channel_number);
    }
    mark.resize(per_channel_number);
    tcp->set_channel_Arg(channel_number, static_cast<int>(sampleRate));
    tcp->flush();
}
/***************  UI 槽函数***********
 *   启动TCP连接
 */
void MainWindow::connectWifi(){
    tcp->wifi_server_connect_board();
    /*如果是客户端
     * tcp = new CommnicateBoard(ip,port,Tcp_client);
     * tcp->client_connectToBoard();
     */
}
/***************  UI 槽函数***********
 *   切换单 、双电极接法
 */
void MainWindow::changeSingleBipolarElect(){
    if(tcp->m_has_start_board){
        if(!singleElectMode){
            QFile file("single_elec.txt");
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug()<<"Can't open the file!"<<endl;
            }
            while(!file.atEnd()) {
                QByteArray reg_value = file.readLine();
                int _reg = reg_value.left(2).toInt(nullptr,16);
                int _value = reg_value.mid(3,2).toInt(nullptr,16);
                QByteArray data_send;
                data_send.append(static_cast<char>(0xaa));
                data_send.append(static_cast<char>(0x03));
                data_send.append(static_cast<char>(_reg));
                data_send.append(static_cast<char>(_value));
                tcp->send_to_board(data_send);
            }
            /*
            int channel_addr = 0x05;
            for(int i = 0 ;i <8; ++i){
                QByteArray data_send;
                data_send.append(static_cast<char>(0xaa));
                data_send.append(static_cast<char>(0x03));
                data_send.append(static_cast<char>(channel_addr));
                data_send.append(static_cast<char>(0x68));
                tcp->send_to_board(data_send);
                channel_addr++;
                QTime timer = QTime::currentTime().addMSecs(25);
                while( QTime::currentTime() < timer )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }
            */
            singleElectMode = true;
            ui->electmode_pushButton->setText("切换为双电极模式（目前为单电极）");
        }
        else{
            QFile file("bipolar_elec.txt");
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug()<<"Can't open the file!"<<endl;
            }
            while(!file.atEnd()) {
                QByteArray reg_value = file.readLine();
                int _reg = reg_value.left(2).toInt(nullptr,16);
                int _value = reg_value.mid(3,2).toInt(nullptr,16);
                QByteArray data_send;
                data_send.append(static_cast<char>(0xaa));
                data_send.append(static_cast<char>(0x03));
                data_send.append(static_cast<char>(_reg));
                data_send.append(static_cast<char>(_value));
                tcp->send_to_board(data_send);
            }
            /*
            int channel_addr = 0x05;
            for(int i = 0 ;i <8; ++i){
                QByteArray data_send;
                data_send.append(static_cast<char>(0xaa));
                data_send.append(static_cast<char>(0x03));
                data_send.append(static_cast<char>(channel_addr));
                data_send.append(static_cast<char>(0x60));
                tcp->send_to_board(data_send);
                channel_addr++;
                QTime timer = QTime::currentTime().addMSecs(25);
                while( QTime::currentTime() < timer )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }
            */
            singleElectMode = false;
            ui->electmode_pushButton->setText("切换为单电极模式（目前为双电极）");
        }
    }
    else{
        QMessageBox::information(this,"","请先连接目标板");
    }
}
/***************  UI 槽函数***********
 *   停止绘图并停止板子读取数据
 */
void MainWindow::stop_m(){
    running = false;    // 默认停止绘图
    ui->runButton->setEnabled(true);    // 使面板“运行”按钮恢复默认形状
    ui->stopButton->setEnabled(false);  // 使面板“停止”按钮恢复默认形状
    ui->command_return_checkBox->setEnabled(true);  // 使面板“命令返回”恢复可选
    ui->comboBox_channel_number->setEnabled(true);  // 使面板“通道数”恢复可选
    ui->sampleRate_comboBox->setEnabled(true);      // 使面板“采样率”恢复可选
    // 如果glazer评估开着，则停止
    if(rms_enable && ui->glazer_stop->isEnabled()){
        glazerEnd();
    }
    // 如果板子还处于连接状态 则发送命令“暂停采样	0x aa 06 00”停止板子读取数据
    if(tcp->m_has_start_board){
        QByteArray data_send;
        data_send.append(static_cast<char>(0xaa));
        data_send.append(static_cast<char>(0x06));
        data_send.append(static_cast<char>(0x00));
        tcp->send_to_board(data_send);
//**************************************************新修改******************************************//
        // 同时清空缓存
        tcp->flush();
    }

        ui->glazer_start->setEnabled(false);  // 使面板“停止”按钮恢复默认形状

    //filtered_data->close();

}

void MainWindow::run_set(){
    running = true; // 开启实时绘图
    ui->runButton->setEnabled(false);   // 使面板“运行”不可选
    ui->stopButton->setEnabled(true);   // 使面板“停止”可选
    if(!tcp->m_has_start_board){ui->glazer_start->setEnabled(false); qDebug("false");}   // 使面板“glazer开始”不可选
    if(tcp->m_has_start_board){ui->glazer_start->setEnabled(true);qDebug("true");}   // 使面板“glazer开始”可选
    //ui->glazer_start->setEnabled(true);   // 使面板“glazer开始”可选
    ui->sampleRate_comboBox->setEnabled(false); // 使面板“采样率”不可选
    ui->command_return_checkBox->setCheckable(false);   // 使面板“命令”不可选
    ui->command_return_checkBox->setEnabled(false);     // 使面板“命令”不可选
    ui->comboBox_channel_number->setEnabled(false);     // 使面板“通道数”不可选
    tcp->m_command_return_mode = false;                 // 使tcp不以命令返回模式
}
/***************  UI 槽函数***********
 *   开始绘图
 */
void MainWindow::run_m(){
    run_set();
    // 如果板子没有开启，则是用文件读取的数据绘图
    if(!tcp->m_has_start_board){
        /***************   使用文件读取的数据绘图     *******************/
        if(runFileData){
            QMessageBox::information(this,"","未开启设备，将使用选中文件内数据绘图");
              qDebug()<<"Can't open the file!"<<endl;
            // 触发connect类进行文件读取和解码
            emit tcp->signal_start_decode_data();
            tcp->m_read_done = false;
            // 参数为（“每次读取的数据量 采样一次数据包结构*每个通道读取数据量*3”，“读取位置”）
            if(channel_number<=8){
                tcp->file_read_data(static_cast<int>((8+4*channel_number + 3)*per_channel_number*3), readFile);
            }
            else{
                tcp->file_read_data(static_cast<int>((8+4*channel_number + 9)*per_channel_number*3), readFile);
            }
            //qDebug()<<"12";
            while(running){
                //读取一定量数据
                //if(!tcp->isReadDone()){
                //    QMessageBox::information(this,"","读取结束");
                //    readFile->close();
                //    running = false;
                //    runFileData = false;
                //    ui->runButton->setEnabled(true);
                //    ui->stopButton->setEnabled(false);
                //    tcp->p_decode_process->m_stop_flag = true;
                //    return;
                //}
                if(tcp->data_from_wifi.size() > per_channel_number*channel_number){
                    //qDebug()<<"draw";
                    try{
                           for(int channel = 0; channel<channel_number; ++channel){
                               elect_off_p[channel] = false;
                               elect_off_n[channel] = false;
                           }
                           for(int i=0; i<per_channel_number;i++){
                               for(int channel = 0; channel<channel_number; ++channel){
                                   data[channel][i] = static_cast<double>(tcp->data_from_wifi.front());
                                   lock_data_from_wifi.lockForWrite();
                                   tcp->data_from_wifi.pop_front();
                                   lock_data_from_wifi.unlock();

                                   elect_off_p[channel] = elect_off_p[channel] || tcp->elect_lead_off.front();
                                   lock_elect_lead_off.lockForWrite();
                                   tcp->elect_lead_off.pop_front();
                                   lock_elect_lead_off.unlock();
                               }
                               for(int channel = 0; channel<channel_number; ++channel){
                                   elect_off_n[channel] = elect_off_n[channel] || tcp->elect_lead_off.front();
                                   lock_elect_lead_off.lockForWrite();
                                   tcp->elect_lead_off.pop_front();
                                   lock_elect_lead_off.unlock();
                               }
                               mark[i] = tcp->mark.front();
                               lock_mark.lockForWrite();
                               tcp->mark.pop_front();
                               lock_mark.unlock();
                           }
                    }catch(...){QMessageBox::critical(this,"debug message", "crash happen in getdatafromtcp");}
                    try{
                       dataProcess->runProcess(data);


                    }catch(...){QMessageBox::critical(this,"debug message", "crash happen in runProcess");qDebug("error");}
                    try{
                       dataProcess->runFFT();
                    }catch(...){QMessageBox::critical(this,"debug message", "crash happen in runFFT");}
                    try{
                    for(int channel = 0; channel<channel_number; ++channel){
                        if(channel_enable_map[channel]){
                            if(drawframe[channel]->hasDataToDraw(sampleRate, dataProcess->y_out[channel],
                                                                 channel%2 ? Qt::red : Qt::blue ,//奇数通道蓝色，偶数通道红色
                                                                 dataProcess->min[channel],dataProcess->max[channel],dataProcess->rms[channel],
                                                                 mark,rms_w_count,rms_w_length,
                                                                 elect_off_p[channel], elect_off_n[channel],singleElectMode,channel)
                                    <0){
                                // 清理缓存
                                stop_m();
                                break;
                            }


                        }
                    }
                    }catch(...){QMessageBox::critical(this,"debug message", "crash happen in draw signal");}
                    try{
                     drawFFT();
                    }catch(...){QMessageBox::critical(this,"debug message", "crash happen in draw fft");}
                    qApp->processEvents();
                 }
            //else
                    //qDebug()<<tcp->data_from_wifi.size();
            }
        }
            /*
            QMessageBox::information(this,"","将使用选中文件内数据绘图");
            int boradNumber = channel_number/32;
            int numberToRead = 0;//一个包的字节长度
            if(channel_number<32){
                numberToRead = static_cast<int>((8+4*channel_number + 9)*per_channel_number);
            }
            else{
                numberToRead = static_cast<int>((8+(32*4+8)*boradNumber+1)*per_channel_number);
            }
            QByteArray _n_channel_data;
            //char *_n_channel_data = new char[numberToRead];
            while(running){
                QByteArray tmpdata = readFile->read(numberToRead);
                if(tmpdata.size()!=numberToRead){
                    QMessageBox::information(this,"","读取结束");
                    readFile->close();
                    running = false;
                    runFileData = false;
                    ui->runButton->setEnabled(true);
                    ui->stopButton->setEnabled(false);
                    return;
                }
                else{
                    _n_channel_data.append(tmpdata);
                }
                //读取依次为 4字节编号，4字节冗余（最后一个bit为mark），channel_number*4字节通道数据，8字节电极脱落数据
                //初始化脱落检测容器
                for(int channel = 0; channel<channel_number; ++channel){
                    elect_off_p[channel] = false;
                    elect_off_n[channel] = false;
                }
                //读取数据
                QQueue<bool> elect_off_bool;
                if(channel_number<=32){
                    for(int j = 0; j< per_channel_number ;++j){
                        //如果是调试信息,跳过。
                        while(_n_channel_data.at(6)!=0){
                            QByteArray ndata_tofill = readFile->read(_n_channel_data.at(6)+9);
                            if(ndata_tofill.size()!=_n_channel_data.at(6)+9){
                                QMessageBox::information(this,"","读取结束");
                                readFile->close();
                                running = false;
                                runFileData = false;
                                ui->runButton->setEnabled(true);
                                ui->stopButton->setEnabled(false);
                                return;
                            }
                            _n_channel_data.append(ndata_tofill);
                            _n_channel_data.remove(0,_n_channel_data.at(6)+9);
                        }
                        //处理电极脱落部分，8字节共计64bit 转为64个布尔值
                        for(int _8byte = 0; _8byte<8; ++_8byte){
                            unsigned char byte = static_cast<unsigned char>(_n_channel_data[8+channel_number*4+_8byte]);
                            elect_off_bool.append(byte&0x01);
                            elect_off_bool.append(byte&0x02);
                            elect_off_bool.append(byte&0x04);
                            elect_off_bool.append(byte&0x08);
                            elect_off_bool.append(byte&0x10);
                            elect_off_bool.append(byte&0x20);
                            elect_off_bool.append(byte&0x40);
                            elect_off_bool.append(byte&0x80);
                        }
                        for(int channel = 0; channel<channel_number; ++channel){
                            //补码转换为有符号int，直接转换
                            int perchannel_data = (_n_channel_data[8+channel*4]&0x000000FF)|
                                                 ((_n_channel_data[8+channel*4+1]&0x000000FF)<<8)|
                                                 ((_n_channel_data[8+channel*4+2]&0x000000FF)<<16)|
                                                 ((_n_channel_data[8+channel*4+3]&0x000000FF)<<24);
                            data[channel][j] = static_cast<double>(perchannel_data)/24.0;//增益24
                            elect_off_bool.pop_front();
                            elect_off_bool.pop_back();
                        }
                        mark[j] = _n_channel_data[7];
                        _n_channel_data.remove(0,8+channel_number*4+9);
                    }
                }
                else{
                    for(int j = 0; j< per_channel_number ;++j){
                        //如果是调试信息,跳过。
                        while(_n_channel_data.at(6)!=0){
                            QByteArray ndata_tofill = readFile->read(_n_channel_data.at(6)+9);
                            if(ndata_tofill.size()!=_n_channel_data.at(6)+9){
                                QMessageBox::information(this,"","读取结束");
                                readFile->close();
                                running = false;
                                runFileData = false;
                                ui->runButton->setEnabled(true);
                                ui->stopButton->setEnabled(false);
                                return;
                            }
                            _n_channel_data.append(ndata_tofill);
                            _n_channel_data.remove(0,_n_channel_data.at(6)+9);
                        }
                        for(int bord_number = 0; bord_number < boradNumber; ++bord_number){
                            //处理电极脱落部分，8字节共计64bit 转为64个布尔值
                            for(int _8byte = 0; _8byte<8; ++_8byte){
                                unsigned char byte = static_cast<unsigned char>(_n_channel_data[8 + (32*4 +8)*bord_number + _8byte]);
                                elect_off_bool.append(byte&0x01);
                                elect_off_bool.append(byte&0x02);
                                elect_off_bool.append(byte&0x04);
                                elect_off_bool.append(byte&0x08);
                                elect_off_bool.append(byte&0x10);
                                elect_off_bool.append(byte&0x20);
                                elect_off_bool.append(byte&0x40);
                                elect_off_bool.append(byte&0x80);
                            }
                            for(int channel = 0; channel<32; ++channel){
                                //补码转换为有符号int，直接转换
                                int perchannel_data = (_n_channel_data[8+(32*4 +8)*bord_number+channel*4]&0x000000FF)|
                                                     ((_n_channel_data[8+(32*4 +8)*bord_number+channel*4+1]&0x000000FF)<<8)|
                                                     ((_n_channel_data[8+(32*4 +8)*bord_number+channel*4+2]&0x000000FF)<<16)|
                                                     ((_n_channel_data[8+(32*4 +8)*bord_number+channel*4+3]&0x000000FF)<<24);
                                data[32*bord_number+channel][j] = static_cast<double>(perchannel_data)/24.0;//增益24
                                elect_off_bool.pop_front();
                                elect_off_bool.pop_back();
                            }
                        }
                        mark[j] = _n_channel_data[7];
                        _n_channel_data.remove(0,8+(32*4+8)*boradNumber+1);
                    }
                }
                dataProcess->runProcess(data);
                dataProcess->runFFT();
                for(int channel = 0; channel < channel_number; ++channel){
                    if(channel_enable_map[channel]){
                        if(drawframe[channel]->hasDataToDraw(sampleRate, dataProcess->y_out[channel],
                                                             channel%2 ? Qt::red : Qt::blue,
                                                             dataProcess->min[channel],dataProcess->max[channel],dataProcess->rms[channel],
                                                             mark,rms_w_count,rms_w_length,
                                                             elect_off_p[channel],elect_off_n[channel])
                                <0){
                            stop_m();
                            break;
                        }
                    }
                }
                drawFFT();
                qApp->processEvents();
                QTime timer = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < timer )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }*/
        /**************   生成模拟正弦波并画图*******************/
        else{
            QMessageBox::StandardButton rb  = QMessageBox::question(this,"","未开启设备，是否使用模拟信号绘图");
            if(QMessageBox::No == rb){
                running = false;
                ui->runButton->setEnabled(true);
                ui->stopButton->setEnabled(false);
                return;
            }
            //产生10Hz递增,带100uV直流,幅度100uV正弦信号，采样率为1kHz
            for(int i = 0; i<channel_number; ++i){
                for(int j = 0; j< per_channel_number ;j++){
                    double y = 100.0*sin(4.0*PI_m*static_cast<double>(j)*(i+1.0)/per_channel_number)+100.0;
                    data[i][j] = y;
                }
            }
            for(int i = 0; i<per_channel_number; ++i){
                mark[i] = 0;
            }
            mark[static_cast<int>(per_channel_number/2)] = 1;

            while(running){
                try{
                dataProcess->runProcess(data);
                dataProcess->runFFT();
                }
                catch(...){
                    QMessageBox::critical(this, "debug message", "crash happened in dataProcess");
                    exit(0);
                }
                try{
                for(int channel = 0; channel < channel_number; ++channel){
                    if(channel_enable_map[channel]){
                        if(drawframe[channel]->hasDataToDraw(sampleRate, dataProcess->y_out[channel],
                                                             channel%2 ? Qt::red : Qt::blue,
                                                             dataProcess->min[channel],dataProcess->max[channel],dataProcess->rms[channel],
                                                             mark,rms_w_count,rms_w_length,
                                                             channel%2 ? true:false, false)<0)
                        {
                            stop_m();
                            break;
                        }
                    }
                }
                }
                catch(...){
                    QMessageBox::critical(this, "debug message", "crash happened in draw signal");
                    exit(0);
                }
                try{
                    drawFFT();
                }
                catch(...){
                    QMessageBox::critical(this, "debug message", "crash happened in draw fft");
                    exit(0);
                }
                qApp->processEvents();
                //int delay = (int)((49.0/500000.0)*(double)time_scale);
                //QTime timer = QTime::currentTime().addMSecs(100);
                //while( QTime::currentTime() < timer )
                //    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }
        }
    }
    // 如果板子开启了，即板子连接成功的话，开始实时采集数据并绘图
    else{
        /**************   启动接收 并绘图******************
         */
        if(tcp->m_connect_type == ConnectType::_wifi){
            QByteArray data_send;
            // 切换传输模式为WiFi传输
            data_send.append(static_cast<char>(0xaa));
            data_send.append(static_cast<char>(0x08));
            data_send.append(static_cast<char>(0x02));
            tcp->send_to_board(data_send);
        }
        else if(tcp->m_connect_type == ConnectType::_serial_com){
            QByteArray data_send;
            //  切换传输模式为串口传输
            data_send.append(static_cast<char>(0xaa));
            data_send.append(static_cast<char>(0x08));
            data_send.append(static_cast<char>(0x01));
            tcp->send_to_board(data_send);
        }
        //  向板子发送通道数、采样率配置信息
        send_chnumber_samplerate();

        QByteArray data_send;
        //  向板子发送命令，启动采样
        data_send.append(static_cast<char>(0xaa));
        data_send.append(static_cast<char>(0x06));
        data_send.append(static_cast<char>(0x01));
        tcp->send_to_board(data_send);
/**************list.pop_front(); 删除list中的第一个位置的元素；list.front(); 获取list中的第一个元素变量**********************/
        while(running){
             if(tcp->data_from_wifi.size() > per_channel_number*channel_number){
                 //如果每次WiFi接收的数据大于单次绘图的数据量，启动绘图,，单次绘图需要125个数据点
                 try{
                        for(int channel = 0; channel<channel_number; ++channel){
                            //  先把电极脱落全部置为默认脱落形式
                            elect_off_p[channel] = false;
                            elect_off_n[channel] = false;
                        }
                        for(int i=0; i<per_channel_number;i++){
                            //  单次绘图数据量 per_channel_number = 125 % 默认单次绘图数据量
                            for(int channel = 0; channel<channel_number; ++channel){
                                data[channel][i] = static_cast<double>(tcp->data_from_wifi.front());    // 绘图通道的数据i为WiFi传输接收到的数据推出的第一个数据
                                lock_data_from_wifi.lockForWrite();
                                tcp->data_from_wifi.pop_front();    // 删除刚才绘图的数据
                                lock_data_from_wifi.unlock();

                                elect_off_p[channel] = elect_off_p[channel] || tcp->elect_lead_off.front();
                                //移除p脱落位
                                lock_elect_lead_off.lockForWrite();
                                tcp->elect_lead_off.pop_front();
                                lock_elect_lead_off.unlock();
                            }
                            for(int channel = 0; channel<channel_number; ++channel){
                                elect_off_n[channel] = elect_off_n[channel] || tcp->elect_lead_off.front();
                                lock_elect_lead_off.lockForWrite();
                                tcp->elect_lead_off.pop_front();
                                lock_elect_lead_off.unlock();
                            }
                            mark[i] = tcp->mark.front();
                            lock_mark.lockForWrite();
                            tcp->mark.pop_front();
                            lock_mark.unlock();
                        }
                 }catch(...){QMessageBox::critical(this,"debug message", "crash happen in getdatafromtcp");}
                 try{
                    dataProcess->runProcess(data);
                    /*QString str;
                    QTextStream stream(filtered_data);
                    for(int po = 0; po<per_channel_number; ++po)
                    {
                        for(int channel = 0; channel<channel_number; ++channel)
                        {
                            str = QString::number(dataProcess->y_out[channel][po], 'f', 2);

                                       stream<<str<<" ";
                        }
                    }*/

                 }catch(...){QMessageBox::critical(this,"debug message", "crash happen in runProcess");}
                 try{
                    dataProcess->runFFT();
                 }catch(...){QMessageBox::critical(this,"debug message", "crash happen in runFFT");}
                 try{
                 for(int channel = 0; channel<channel_number; ++channel){
                     if(channel_enable_map[channel]){
                         if(drawframe[channel]->hasDataToDraw(sampleRate, dataProcess->y_out[channel],
                                                              channel%2 ? Qt::red : Qt::blue ,
                                                              dataProcess->min[channel],dataProcess->max[channel],dataProcess->rms[channel],
                                                              mark,rms_w_count,rms_w_length,
                                                              elect_off_p[channel], elect_off_n[channel],singleElectMode,channel)
                                 <0){
                             stop_m();
                             break;
                         }

                     }

                 }
                 }catch(...){QMessageBox::critical(this,"debug message", "crash happen in draw signal");}
              }
             try{
              drawFFT();
              }catch(...){QMessageBox::critical(this,"debug message", "crash happen in draw fft");}
              qApp->processEvents();
        }
    }
}

/***************  UI 槽函数***********
 *   向板子发送命令
 */
void MainWindow::sendCommand(){
    if(tcp->m_has_start_board){
        QByteArray c_send;
        QStringList command = ui->command_lineEdit->text().split(" ");
        if(command.size()>1){
            for(int i = 0; i<command.size(); ++i){
                bool ok;
                c_send.append(static_cast<char>(command[i].toInt(&ok,16)));
            }
            tcp->send_to_board(c_send);
        }
    }
    else{
        QMessageBox tip;
        tip.setText("请先连接目标板");
        tip.exec();
    }
}
/***************  UI 槽函数***********
 *   启用命令调试接收返回值模式
 */
void MainWindow::changeCommandReturn(){
    if(Qt::Checked == ui->command_return_checkBox->checkState())
        tcp->m_command_return_mode = true;
    else if(Qt::Unchecked == ui->command_return_checkBox->checkState())
        tcp->m_command_return_mode = false;
}
/***************  UI 槽函数***********
 *   打开帮助说明窗口
 */
void MainWindow::showhelpmessage(){
    QObject* sender = QObject::sender();
    if("rms_help_pushButton" == sender->objectName()){
        QMessageBox::about(this,"Help Message","RMS: we show the data by windowsize = 50, overlap = 0 \n we draw the glazer by windowsize = 200, overlap = 30");
    }
    else if("path_help_pushButton" == sender->objectName()){
        QMessageBox::about(this,"Help Message","default save path is current filedir, and will set up a new file \"ZJUEEGDATA\"");
    }
    else if("command_help_pushButton" == sender->objectName()){
        QString msg = "Configure the Register: AA 03 Addr Value\n"
                      "Read the Register: AA 04 Addr\n"
                      "START: AA 06 01; STOP: AA 06 00\n"
                      "Change ch_number: AA 07 NUMBER\n"
                      "Change connect_type: AA 08 01 serial_port, AA 08 02 wifi\n"
                      "Change pwm freq: AA 09 freq\n"
                      "Change bandrate: AA 0A N, bandrate = N*9600\n"
                      "configure wifi ip: AA 0B ip, ip:string\n"
                      "configure wifi port:AA 0C port, port:string\n"
                      "configure wifi ssid:AA 0D SSID, ssid:string"
                      "configure wifi password:AA 0E password, password:string";
        QMessageBox::about(this,"Help Message",msg);
    }
}
/***************  UI 槽函数***********
 *   打开通道控制窗口
 */
void MainWindow::openChannelSetWidget(){
    ChannelSet ch_set_window(checkbox,channel_number);
    ch_set_window.show();
    ch_set_window.exec();
    changeChannelEnable();
}
/***************  UI 槽函数***********
 *   更改通道数
 */
void MainWindow::changeChannelNumber(){
    int index = ui->comboBox_channel_number->currentIndex();
    switch(index){
        //case 0: channel_number = 1;break;
        case 0: channel_number = 2;break;
        case 1: channel_number = 4;break;
        case 2: channel_number = 8;break;
        //case 4: channel_number = 16;break;
        case 3: channel_number = 32;break;
        case 4: channel_number = 64;break;
        case 5: channel_number = 96;break;
        case 6: channel_number = 128;break;
        case 7: channel_number = 160;break;
        case 8: channel_number = 192;break;
        case 9: channel_number = 224;break;
        case 10:channel_number = 256;break;
    default:channel_number = 32;
    }
    // 更改通道数之后调整波形显示窗口(指菜单栏里的显示)
    switch(channel_number){
    case 32: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(false);ui->tab_3->setEnabled(false);ui->tab_4->setEnabled(false);
        ui->tab_5->setEnabled(false);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 64: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(false);ui->tab_4->setEnabled(false);
        ui->tab_5->setEnabled(false);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 96: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(false);
        ui->tab_5->setEnabled(false);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 128: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(true);
        ui->tab_5->setEnabled(false);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 160: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(true);
        ui->tab_5->setEnabled(true);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 192: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(true);
        ui->tab_5->setEnabled(true);ui->tab_6->setEnabled(true);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
        break;
    case 224: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(true);
        ui->tab_5->setEnabled(true);ui->tab_6->setEnabled(true);ui->tab_7->setEnabled(true);ui->tab_8->setEnabled(false);
        break;
    case 256: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(true);ui->tab_3->setEnabled(true);ui->tab_4->setEnabled(true);
        ui->tab_5->setEnabled(true);ui->tab_6->setEnabled(true);ui->tab_7->setEnabled(true);ui->tab_8->setEnabled(true);
        break;
        //默认只开启1-32通道
    default: ui->tab_1->setEnabled(true);ui->tab_2->setEnabled(false);ui->tab_3->setEnabled(false);ui->tab_4->setEnabled(false);
        ui->tab_5->setEnabled(false);ui->tab_6->setEnabled(false);ui->tab_7->setEnabled(false);ui->tab_8->setEnabled(false);
    }
    // 更新窗口部件
     channel_number = 32;
    for(int i = channel_number; i<MAX_CHANNEL_NUMBER; ++i){
        checkbox[i]->setChecked(false);
    }
    for(int i =0; i<channel_number; ++i){
        checkbox[i]->setChecked(true);
    }
    initFFTWidget(fft_selfControl,fft_xmin,fft_xmax,fft_ymin,fft_ymax);//更新FFT配置
    changeAmplititude();//为窗口部件更新设置
    changeTimeScale();
    for(int i= 0; i<=channel_number-1;++i){
        drawframe[i]->refreshPixmap();
    }
    //更新实例化对象参数
    dataProcess->setChArg(channel_number, per_channel_number);
    tcp->set_channel_Arg(channel_number, static_cast<int>(sampleRate));
    //更新容器
    data.resize(channel_number);
    for(int i=0;i<channel_number;i++){
        data[i].resize(per_channel_number);
    }
    elect_off_p.resize(channel_number);
    elect_off_n.resize(channel_number);
    //下发命令并清空留存数据
    // aa 07 通道数
    // 通道数从1开始，256通道发送0x00
    //int ch_to_send = channel_number;
    //if (ch_to_send == 256){
    //    ch_to_send = 0;
    //}
    //QByteArray data_send;
    //data_send.append(static_cast<char>(0xaa));
    //data_send.append(static_cast<char>(0x07));
    //data_send.append(static_cast<char>(ch_to_send));
    //command_vector[0]=data_send;
    if(tcp->m_has_start_board){
        tcp->flush();
    }


}
/***************  重载X按钮事件***********
 *   解决关闭程序时，如果绘制还未完成，后台程序未退出问题
 */
void MainWindow::closeEvent(QCloseEvent*){
    running = false;
    tcp->set_debug_off();
    stop_m();
    emit sendsignal();
        this->hide();
}
/***************  重载事件滤波器***********
 *
 */
bool MainWindow::nativeEventFilter(const QByteArray &eventType, void *message, long *){
    if(eventType == "windows_generic_MSG"){
        MSG* ev = static_cast<MSG *>(message);
        if(ev->message == WM_DEVICECHANGE){
            switch (ev->wParam) {
            case DBT_DEVICEARRIVAL:
                initCom();
                break;
            case DBT_DEVICEREMOVECOMPLETE:
                initCom();
                break;
            default:
                break;
            }
        }
    }
    return false;
}

/*************   打开文件  **************
 *
 */
void MainWindow::openfile(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("(*.txt)"));
    if(QMessageBox::Ok == QMessageBox::information(this,"确认选择的文件",QString(tr("选中的文件为："))+filePath,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok)){
        if(tcp->m_has_start_board){
            QMessageBox::warning(this,"警告","目前正在接收数据，请先断开连接再尝试操作");
        }
        else{
            runFileData = true;
            readFilePath = filePath;
            delete readFile;
            readFile = nullptr;
            readFile = new QFile(filePath);
            if(!readFile->open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,"警告","打开文件失败");
                runFileData = false;
            }
        }
    }
    else{
        QMessageBox::information(this,"","请重新选择文件",QMessageBox::Ok);
        runFileData = false;
    }
}

/**** 打开FFT配置窗口 *****/
void MainWindow::openFFTSetWidget(){
    FFTSet fftsetWidget(fft_selfControl,fft_xmin,fft_xmax,fft_ymin,fft_ymax);
    connect(&fftsetWidget,SIGNAL(changeFFtWidget(bool,double,double,double,double)),this,SLOT(initFFTWidget(bool,double,double,double,double)));
    fftsetWidget.show();
    fftsetWidget.exec();
}

/**** 初始化FFT绘图窗口 *****/
void MainWindow::initFFTWidget(bool selfControl,double xmin,double xmax,double ymin,double ymax){
    fft_selfControl = selfControl;
    connect(ui->FFTWidget->xAxis,SIGNAL(rangeChanged(QCPRange)),ui->FFTWidget->xAxis2,SLOT(setRange(QCPRange)));
    connect(ui->FFTWidget->yAxis,SIGNAL(rangeChanged(QCPRange)),ui->FFTWidget->yAxis2,SLOT(setRange(QCPRange)));
    ui->FFTWidget->xAxis2->setVisible(true);
    ui->FFTWidget->xAxis2->setTickLabels(false);
    ui->FFTWidget->yAxis2->setVisible(true);
    ui->FFTWidget->yAxis2->setTickLabels(false);
    ui->FFTWidget->xAxis->setLabel("频率");
    ui->FFTWidget->yAxis->setLabel("幅度");
    if(!fft_selfControl){
        fft_ymax = ymax; fft_ymin = ymin;
        fft_xmax = xmax; fft_xmin = xmin;
        ui->FFTWidget->yAxis->setRange(fft_ymin,fft_ymax);
        ui->FFTWidget->xAxis->setRange(fft_xmin,fft_xmax);
    }
    ui->FFTWidget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);//缩放图形
    // 绘制32通道FFT波形
    pen[0].setColor(QColor("red"));
    pen[1].setColor(QColor("green"));
    pen[2].setColor(QColor("blue"));
    pen[3].setColor(QColor("black"));
    pen[4].setColor(QColor("darkRed"));
    pen[5].setColor(QColor("darkGreen"));
    pen[6].setColor(QColor("darkBlue"));
    pen[7].setColor(QColor("Cyan"));
    pen[8].setColor(QColor("magenta"));
    pen[9].setColor(QColor("yellow"));
    pen[10].setColor(QColor("gray"));
    pen[11].setColor(QColor("darkCyan"));
    pen[12].setColor(QColor("darkMagenta"));
    pen[13].setColor(QColor("darkYellow"));
    pen[14].setColor(QColor("darkGray"));
    pen[15].setColor(QColor(188,143,11));
    pen[16].setColor(QColor(139,69,19));
    pen[17].setColor(QColor(160,82,45));
    pen[18].setColor(QColor(245,222,179));
    pen[19].setColor(QColor(244,164,96));
    pen[20].setColor(QColor(255,165,0));
    pen[21].setColor(QColor(255,140,0));
    pen[22].setColor(QColor(255,105,180));
    pen[23].setColor(QColor(255,20,147));
    pen[24].setColor(QColor(219,112,147));
    pen[25].setColor(QColor(176,48,96));
    pen[26].setColor(QColor(255,0,255));
    pen[27].setColor(QColor(160,32,240));
    pen[28].setColor(QColor(0,191,255));
    pen[29].setColor(QColor(0,178,238));
    pen[30].setColor(QColor(0,135,206,255));
    pen[31].setColor(QColor(104,34,139));
    ui->FFTWidget->clearGraphs();
    for(int i =0; i<channel_number; ++i){
        ui->FFTWidget->addGraph();
        ui->FFTWidget->graph(i)->setPen(pen[i%32]);
    } 
}
/**** FFT绘图 *****/
void MainWindow::drawFFT(){
    int channel_fft = channel_number<32?channel_number:32;
    for(int i =0 ;i<channel_fft; ++i){
        ui->FFTWidget->graph(i)->data().clear();
        if(channel_enable_map[i]){
            ui->FFTWidget->graph(i)->setVisible(true);
            ui->FFTWidget->graph(i)->setData(dataProcess->fft_x[i],dataProcess->fft_y[i]);
        }
        else
            ui->FFTWidget->graph(i)->setVisible(false);
    }
    for(int i =channel_fft; i<channel_number; ++i){
        ui->FFTWidget->graph(i)->setVisible(false);
    }
    if(fft_selfControl)
        ui->FFTWidget->rescaleAxes();
    ui->FFTWidget->replot();
}
/**** 打开短时傅里叶窗口 *****/
void MainWindow::openSTFTWidget(){
    if(!stft_window){
        delete stft_window;
        stft_window = nullptr;
    }
    stft_window = new STFT;
    stft_window->show();
}
/**** 保留函数 *****/
void MainWindow::flush(){
    //pass
}
/**** 打开连接方式切换弹窗 *****/
void MainWindow::openConnectSetWidget(){
    if(!tcp->m_has_start_board){
        QMessageBox::information(this,"","未连接硬件");
        return;
    }
    if(tcp->m_connect_type == ConnectType::_no_connect){
        QMessageBox::information(this,"","未连接硬件");
        return;
    }
    QString tmpmsg;
    int flag = 0; //1:wifi, 2:serial_com
    if(tcp->m_connect_type == ConnectType::_wifi){
        tmpmsg = tmpmsg + "目前连接方式是wifi, 将重置连接。";
        flag =1;
    }
    else if(tcp->m_connect_type == ConnectType::_serial_com){
        tmpmsg = tmpmsg + "目前连接方式是串口, 将重置连接。";
        serial_port->close();
        flag =2;
    }
    if(QMessageBox::Yes == QMessageBox::question(this,"提示",tmpmsg)){
        ui->connect_type_label->setText("unconnect");
        ui->connect_type_label->setStyleSheet("color:rgb(255,0,0)");
        p_tcp_thread->quit();
        p_tcp_thread->wait();
        delete tcp;
        tcp = new CommnicateBoard(ip,port,Tcp_server,channel_number,static_cast<int>(sampleRate),ui->command_return_label);
        connect(this->tcp,SIGNAL(signal_board_start()),this,SLOT(connectToBardDone()));
        connect(this->tcp,SIGNAL(signal_tcp_abort()),this,SLOT(connectToBardAbort()));
        tcp->moveToThread(p_tcp_thread);
        p_tcp_thread->start();
        QMessageBox::information(this,"","已重置连接，请重新连接板子");
    }
}
/**** 打开串口设置弹窗 *****/
void MainWindow::openPortSetWidget(){
    scanPort();
    PortSet portwidget(vector_port_name, serial_port);
    connect(&portwidget, SIGNAL(portSetDone()), this, SLOT(portSetDone()));
    portwidget.show();
    portwidget.exec();
}
/**** 打开Wi-Fi设置弹窗 *****/
void MainWindow::openWifiSetWidget(){
    WifiSet wifiwidget(this);
    connect(&wifiwidget,SIGNAL(wifi_arg_change(QString,QString,QString,QString)), this, SLOT(wifiSetDone(QString,QString,QString,QString)));
    wifiwidget.show();
    wifiwidget.exec();
}

/*************   槽函数  **************
 *  串口设置弹窗确认键按下后触发
 * （1）打开串口
 * （2）触发connect.cpp中com_start()
 */
void MainWindow::portSetDone(){
    if(!serial_port->open(QIODevice::ReadWrite)){
        QMessageBox::information(this,"提示", "串口打开失败，请检查端口！",QMessageBox::Yes);
        qDebug()<<"open serial port failed: ";
        qDebug()<<selected_port_name;
        find_com = false;
    }
    else{
        find_com = true;
        tcp->com_start(serial_port);
    }
}
/*************   槽函数  **************
 *  wifi设置弹窗确认键按下后触发
 *  (1)发送命令   AA 0B length ssid,ip,port,password
 *  (2) 更新参数
 */
void MainWindow::wifiSetDone(QString newssid, QString newip, QString newport, QString newpassword){
    QString wifi_tmp_config = newssid + "," + newip + "," + newport + "," + newpassword;
    QByteArray data_send;
    data_send.append(static_cast<char>(0xaa));
    data_send.append(static_cast<char>(0x0b));
    int length = wifi_tmp_config.size();
    data_send.append(static_cast<char>(length));
    for (int i=0;i<wifi_tmp_config.size();++i) {
        data_send.append(static_cast<char>(wifi_tmp_config[i].toLatin1()));
    }
    tcp->send_to_board(data_send);

    ui->statusbar->showMessage("IP="+newip+";Port="+newport);
    ui->IP_lineEdit->setText(newip);
    ui->Port_lineEdit->setText(newport);
    tcp->wifi_update_ip(newip);
    tcp->wifi_update_port(static_cast<quint16>(newport.toUInt()));
}
/*************   串口初始化  **************
 *
 */
void MainWindow::initCom(){
    scanPort();
}
/*************   串口初始化  **************
 *  扫描可用COM口
 */
void MainWindow::scanPort(){
    vector_port_name.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        vector_port_name.append(info.portName());
    }
}
/*************   打开变更PWM波得子窗口  **************
 *
 */
void MainWindow::changePwmFreq(){
    if(!tcp->m_has_start_board){
        QMessageBox::warning(this,"warning","未连接板子，无法修改");
        return;
    }
    QSettings *p_ini = new QSettings("config.ini",QSettings::IniFormat);
    int ini_pwm_freq = p_ini->value("pwm_freq").toInt();
    delete p_ini;
    QDialog *win;
    win = new QDialog(this);
    QHBoxLayout hlayer;
    QLabel label1;
    label1.setText("PWM波频率");
    QLabel label2;
    label2.setText("Hz");
    QSpinBox *spinBox=new QSpinBox;
    spinBox->setRange(1,5000);
    spinBox->setValue(ini_pwm_freq);
    QPushButton yes_bn;
    yes_bn.setText("确认");
    connect(&yes_bn,&QPushButton::clicked,[=](){
//        char val = static_cast<char>(spinBox->value());
        short val = static_cast<short>(spinBox->value());
        char high_val = val >> 8;
        char low_val = val & 0xff;
        QByteArray data_send;
        data_send.append(static_cast<char>(0xaa));
        data_send.append(static_cast<char>(0x09));
//        data_send.append(static_cast<short>(val));
        data_send.append(static_cast<char>(low_val));
        data_send.append(static_cast<char>(high_val));
        tcp->send_to_board(data_send);
        QSettings *p_ini = new QSettings("config.ini",QSettings::IniFormat);
        p_ini->setValue("pwm_freq", val);
        delete p_ini;
        win->setAttribute(Qt::WA_DeleteOnClose);
        win->close();
    });

    hlayer.addWidget(&label1);
    hlayer.addWidget(spinBox);
    hlayer.addWidget(&label2);
    hlayer.addWidget(&yes_bn);
    win->setLayout(&hlayer);
    win->setWindowTitle("频率修改");
    win->setGeometry(200,200,600,150);
    win->show();
    win->exec();
}
/*************   更新配置文件  **************
 *  目前配置文件存储4部分内容，通道数，采样率，时基，幅基
 */
void MainWindow::updateIniFile(){
    QString config_file_name = "config.ini";
    QSettings *p_ini = new QSettings(config_file_name,QSettings::IniFormat);
    p_ini->setValue("sample_rate_index", ui->sampleRate_comboBox->currentIndex());
    p_ini->setValue("channel_number_index", ui->comboBox_channel_number->currentIndex());
    p_ini->setValue("amplititude_scale_index", ui->amplititude_comboBox->currentIndex());
    p_ini->setValue("time_scale_index", ui->time_comboBox->currentIndex());
    delete p_ini;
}
/*************   打开调试窗口  **************
 *  窗口内输出两部分内容（1）数据流中得DEBUG信息（2）程序运行中得DEBUG信息
 */
void MainWindow::openDebugWidget(){
    tcp->set_debug_on();
}

void MainWindow::send_chnumber_samplerate(){
    // 向板子发送改变通道数和采样率的命令
    int index = 0x90;
    switch(ui->sampleRate_comboBox->currentIndex()){
    case 0: index+=6;break;//50
    case 1: index+=5;break;//100
    case 2: index+=4;break;//200
    case 3: index+=3;;break;//400
    case 4: index+=2;break;//800
    case 5: index+=1;break;//1600
    case 6:break;//16000
    default: index+=4;//200
    }
    QByteArray data_send;
    //  向板子发送改变采样率的命令
    data_send.append(static_cast<char>(0xaa));
    data_send.append(static_cast<char>(0x03));
    data_send.append(static_cast<char>(0x01));
    data_send.append(static_cast<char>(index));
    tcp->send_to_board(data_send);

    data_send.clear();
    int ch_to_send = channel_number;
    if (ch_to_send == 256){
        ch_to_send = 0;
    }
    // 向板子发送改变通道数的命令
    data_send.append(static_cast<char>(0xaa));
    data_send.append(static_cast<char>(0x07));
    data_send.append(static_cast<char>(ch_to_send));
    tcp->send_to_board(data_send);
}
/*void FFTSet::changeFFTSet(){
    if(selfcontrol){
        emit changeFFtWidget(true,0,0,0,0);
    }
    else{
        double xmim = ui->Xmin->text().toDouble();
        double xmax = ui->Xmax->text().toDouble();
        double ymin = ui->Ymin->text().toDouble();
        double ymax = ui->Ymax->text().toDouble();
        emit changeFFtWidget(false,xmim,xmax,ymin,ymax);
    }
}*/

void MainWindow::fftset()
{
    fft_xmin = ui->Xmin->text().toDouble();
    fft_xmax = ui->Xmax->text().toDouble();
    fft_ymin = ui->Ymin->text().toDouble();
    fft_ymax = ui->Ymax->text().toDouble();
    //bool selfcontrol = true;
    emit changeFFtWidget(false,fft_xmin,fft_xmax,fft_ymin,fft_ymax);
    //connect(&fftsetWidget,SIGNAL(changeFFtWidget(bool,double,double,double,double)),this,SLOT(initFFTWidget(bool,double,double,double,double)));
}

void MainWindow::on_action_config_triggered()
{
    openPortSetWidget();
}


void MainWindow::on_action_reconfig_triggered()
{
    openConnectSetWidget();
}

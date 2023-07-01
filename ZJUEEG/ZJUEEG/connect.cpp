/*
 * 用于Tcp连接，包含数据接收，解析，存储
 * 包数据格式规定：一包144字节。
 *          包序号（4字节，每字节小端先发）+mark（4字节，mark位于最小端最小bit位上）+通道数据（32*4字节，每字节小端先发）+脱落数据（8字节，展开为ch1p,ch2p,ch3p,...,ch32p,ch1n,ch2n,...,ch32n）
 * 默认存储路径：当前路径/ZJUEEGDATA
 * 默认接收Buffer大小：无限制
 * 默认作为服务器
 * 默认端口61613（从mainwindow接收）
 *
 * 对外提供接收到的数据接口：
     QQueue<qint8> mark;
     QQueue<double> data_from_wifi;
     QQueue<bool> elect_lead_off;
     硬件启动标识：bool m_has_start_board
*/

#include "connect.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDir>

//  lockForWrite 为写而锁，就是要修改数据，外人连想进来读数据都不行，完全霸占数据使用权。
//  lockForRead 为读而锁，就是在读取数据期间不要被修改，但是别人也要求来读数据的话，则不拒绝。但是别人来改数据，那就等我读完数据以后再说。
QReadWriteLock lock_mark;
QReadWriteLock lock_data_from_wifi;
QReadWriteLock lock_elect_lead_off;

CommnicateBoard::CommnicateBoard( QString ip_in, quint16 port_in,TcpType tcp_type,int N_channel,int sample_rate, QLabel * label):
    p_command_return_label(label),
    m_channel_number(N_channel),
    m_sample_rate(sample_rate),
    m_ip(ip_in),
    m_port(port_in)
{
    m_connect_type = _no_connect;
    m_has_setup_newfile = false;
    m_has_start_board = false;
    m_glazer_on = false;
    m_debug_on = false;
    m_command_return_mode = false;
    m_check_command_send_mode = false;
    m_check_command_done = false;
    m_read_done = false;
    m_answer_mode = false;
    //m_com_find_head = false;
    //m_find_head = false;
    //m_packet_number_last = 0;
//**********************************************新协议*********************************************//
    // 脱落检测不是固定的8字节，而是根据通道数进行改变
    //初始计算包大小
    if(m_channel_number < 32){
        //m_packet_size = 8+4*m_channel_number +8+1;
        if(m_channel_number <= 8){
            m_packet_size = 8+4*m_channel_number + 2 + 1;
        }
        else{
            m_packet_size = 8+4*m_channel_number + 8 + 1;
        }
    }
    else{
        m_packet_size = 8+(4*32+8)*(m_channel_number/32)+1;//包大小
    }

    //确定TCP连接类型
    if (Tcp_server == tcp_type){
        m_tcp_type = Tcp_server;
        p_tcp_server = new QTcpServer();
        connect(p_tcp_server,SIGNAL(newConnection()),this,SLOT(slot_wifi_tcp_server_new_connect()));
    }
    else if(Tcp_client == tcp_type){
        m_tcp_type = Tcp_client;
        p_tcp_client = new QTcpSocket();
        connect(p_tcp_client,SIGNAL(connected()),this,SLOT(slot_wifi_tcp_client_connect_success()));
        connect(p_tcp_client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slot_wifi_tcp_client_connect_failed()));
        connect(p_tcp_client,SIGNAL(readyRead()),this,SLOT(slot_wifi_tcp_client_read_data()));
        //connect(client,SIGNAL(hostFound()),this,SLOT(slot_wifi_tcp_client_find_host()));
    }
    else{
        qDebug("tcpTypeError");
    }
    //新建文件夹，确定存储路径
    m_storePath = QDir::currentPath()+"/ZJUEEGDATA";
    QDir dir(m_storePath);
    if(!dir.exists()){
        bool ok =dir.mkdir(m_storePath);
        if(!ok)
            qDebug("save path mkdir failed");
    }
    p_datafile = new QFile();
    p_debugfile = new QFile();
    p_processed_file = new QFile();
    p_mark_file = new QFile();

    p_decode_thread = new QThread(this);
    p_decode_process = new Decode(m_channel_number,
                                  m_packet_size,
                                  m_debug_on,
                                  m_buffer,
                                  mark,
                                  p_mark_file,
                                  data_from_wifi,   //对外提供的数据绘图接口
                                  elect_lead_off,
                                  p_processed_file,
                                  p_debugfile,
                                  debug_msg_queue);
    // 如果板子连接成功，则开始解码板子向上位机发送得数据
    connect(this,SIGNAL(signal_start_decode_data()),p_decode_process,SLOT(slot_start_decode_data()));
    p_decode_process->moveToThread(p_decode_thread);
    p_decode_thread->start();
}

CommnicateBoard::~CommnicateBoard(){
    if (Tcp_server == m_tcp_type){
        delete p_tcp_server;
        p_tcp_server = nullptr;
    }
    else if (Tcp_client == m_tcp_type){
        delete p_tcp_client;
        p_tcp_client = nullptr;
    }
    if(p_datafile !=nullptr){
        delete p_datafile;
        p_datafile = nullptr;
    }
    if(p_debugfile !=nullptr){
        delete p_debugfile;
        p_debugfile = nullptr;
    }
    if(p_glazerfile != nullptr){
        delete p_glazerfile;
        p_glazerfile = nullptr;
    }
    if(p_processed_file != nullptr){
        delete p_processed_file;
        p_processed_file = nullptr;
    }
    if(p_mark_file != nullptr){
        delete p_mark_file;
        p_mark_file = nullptr;
    }
    if(p_debug_process != nullptr){
        delete p_debug_process;
        p_debug_process = nullptr;
    }
    if(p_debug_thread != nullptr){
        p_debug_thread->quit();
        p_debug_thread->wait();
        delete p_debug_thread;
        p_debug_thread = nullptr;
    }
    if(p_decode_process != nullptr){
        p_decode_process->m_stop_flag=true;
        delete p_decode_process;
        p_decode_process = nullptr;
    }
    if(p_decode_thread != nullptr){
        p_decode_thread->quit();
        p_decode_thread->wait();
        delete p_decode_thread;
        p_decode_thread = nullptr;
    }
    if(p_readfile!= nullptr){
        p_readfile->quit();
        p_readfile->wait();
        delete p_readfile;
        p_readfile = nullptr;
    }
}

void CommnicateBoard::wifi_update_port(quint16 port_in){
    m_port = port_in;
}
void CommnicateBoard::wifi_update_ip(QString ip_in){
    m_ip = ip_in;
}
//运行过程中通道不可更改。
//按下停止键后数据已从队列中pop出，这里不用再进行处理
//需要新建文件用于存储
void CommnicateBoard::set_channel_Arg(int ch_number, int samplerate){
    m_sample_rate = samplerate;
    m_channel_number = ch_number;
    if(m_channel_number < 32){
//**************************************************新协议修改********************************************//
        // 设置每个包的大小
        if(m_channel_number <= 8){
            m_packet_size = 8+4*m_channel_number + 2 + 1;
        }
        else{
            m_packet_size = 8+4*m_channel_number + 8 + 1;
        }
    }
    else{
        m_packet_size = 8+(4*32+8)*(m_channel_number/32)+1;//包大小
    }
    try {
        p_datafile->close();
        p_debugfile->close();
    } catch (...) {
        qDebug()<<"close again";
    }

    m_has_setup_newfile = false;
}
//客户端开始连接
void CommnicateBoard::wifi_client_connect_board(){
    p_tcp_client->abort();
    p_tcp_client->connectToHost(QHostAddress(m_ip),m_port);
}
//服务端开始连接
void CommnicateBoard::wifi_server_connect_board(){
    if(m_has_start_board)
        return;
    flush();
    //qDebug()<<m_port;
    p_tcp_server->close();
    p_tcp_server->listen(QHostAddress::Any, m_port);
}



/*************** 客户端槽函数 ************
 *
 */
//SLOT 连接成功
void CommnicateBoard::slot_wifi_tcp_client_connect_success(){
    QMessageBox::information(this,"Message","connect to board success,IP = " + m_ip + " port = " + QString::number(m_port,10));
    m_connect_type = _wifi;
    //QByteArray data_send;
    //data_send.append(static_cast<char>(0xaa));
    //data_send.append(static_cast<char>(0x08));
    //data_send.append(static_cast<char>(0x02));
    //send_to_board(data_send);

    //QMessageBox tip;
    //tip.setText("connect to board success,IP = " + ip + " port = " + QString::number(port,10));
    //tip.exec();
}
//SLOT 连接失败
void CommnicateBoard::slot_wifi_tcp_client_connect_failed(){
    QMessageBox::information(this,"Message","tcp connect failed: " + p_tcp_client->errorString());
    //QMessageBox tip;
    //QString errormessage = "tcp connect failed: " + client->errorString();
    //tip.setText(errormessage);
    //tip.exec();
}
//SLOT 发现主机
void CommnicateBoard::slot_wifi_tcp_client_find_host(){
    qDebug("client find host");
}
//SLOT 接收到数据
void CommnicateBoard::slot_wifi_tcp_client_read_data(){
    //pass
}



/***********   服务端槽函数  **************
 *
*/
void CommnicateBoard::slot_wifi_tcp_server_new_connect(){
    qDebug("has got new socket");
    //获得新的SOCKET
    p_tcp_new_connection = p_tcp_server->nextPendingConnection();
    QString userIp = this->p_tcp_new_connection->peerAddress().toString();
    qint16 userPort = this->p_tcp_new_connection->peerPort();
    QString temp = QString("[%1:%2]:连接成功").arg(userIp).arg(userPort);
    qDebug()<<temp;

    QObject::connect(p_tcp_new_connection,SIGNAL(readyRead()),this,SLOT(slot_read_data()));
    connect(p_tcp_new_connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slot_wifi_server_connect_error(QAbstractSocket::SocketError)));
    m_connect_type = _wifi;
    m_has_start_board = true;
    // 如果板子连接成功，则触发连接成功信号
    emit signal_board_start();
    // 如果板子连接成功，则触发开始解析板子发过来得数据包
    emit signal_start_decode_data();
    QMessageBox::information(this,"提示","wifi连接成功！",QMessageBox::Yes);
    //QByteArray data_send;
    //data_send.append(static_cast<char>(0xaa));
    //data_send.append(static_cast<char>(0x08));
    //data_send.append(static_cast<char>(0x02));
    //send_to_board(data_send);
}
/* 触发读取文件数据 */
// （每次读取的数据树，文件位置）
void CommnicateBoard::file_read_data(int size_per_read, QFile *fd){
    delete p_processed_file;
    p_processed_file = new QFile("delete.txt");
    p_processed_file->open(QIODevice::WriteOnly);
    p_readfile = new ReadSavedFile(m_buffer, m_read_done);
    p_readfile->set(size_per_read, fd);
    p_readfile->start();
}
void ReadSavedFile::run(){
    qDebug()<<"thread start";
    while(1){
        lock_m_buffer.lockForWrite();
        if(m_buffer_readfile.size()>100000){
            lock_m_buffer.unlock();
            //延时
            //qDebug()<<"buffer_overlap";
            QTime timer = QTime::currentTime().addMSecs(200);
            while( QTime::currentTime() < timer )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            continue;
        }
        else{
            lock_m_buffer.unlock();
        }
        //qDebug()<<"readdata";
        QByteArray tmpdata = file_fd->read(readsize);
        if(tmpdata.size()!=readsize){
            //qDebug()<<"file end";
            m_read_done_readfile = true;
            return;
        }
        //qDebug()<<"get data";
        //获取数据
        lock_m_buffer.lockForWrite();
        m_buffer_readfile.append(tmpdata);
        lock_m_buffer.unlock();
    }
}
bool CommnicateBoard::isReadDone(){
    return m_read_done;
}

void CommnicateBoard::slot_read_data(){
    // 等待命令返回值模式
    if(m_check_command_send_mode){
        //预期返回的OK
        QByteArray desire_data;
        desire_data.append(static_cast<char>(0xaa));
        desire_data.append(m_check_command_type);
        desire_data.append("OK");
        //获取返回数据
        QByteArray tmpdata_all;
        QByteArray tmpdata_last4;
        QByteArray tmpdata_first4;
        if(m_connect_type == _wifi){
            tmpdata_all = p_tcp_new_connection->readAll();
        }
        else if(m_connect_type == _serial_com){
            tmpdata_all = p_com->readAll();
        }
        else{
            qDebug("error");
            return;
        }
        tmpdata_last4 = tmpdata_all.right(4);
        tmpdata_first4 = tmpdata_all.left(4);
        // desire_data = ‘ok’
        if(tmpdata_last4 == desire_data){
            m_check_command_done = true;
        }
        else if(tmpdata_first4 == desire_data){
            m_check_command_done = true;
        }
        else{
            return;
        }
        //调试模式，接收发送命令的返回值
        if(m_command_return_mode){
            QByteArray tmpdata_data;
            if(m_connect_type == _wifi){
                tmpdata_data = p_tcp_new_connection->readAll();
            }
            else if(m_connect_type == _serial_com){
                tmpdata_data = p_com->readAll();
            }
            else{
                qDebug("error");
                return;
            }
            int return_data = int(tmpdata_data[0]&0xFF);
            QString content = QString::number(return_data,16);
            p_command_return_label->setText(content);
        }
        return;
    }
    //接收逻辑
    //注：没有设置读取buffer大小，默认为无限制，适用于数据不能丢失场合。dataready信号在BUffer中有数据待读取和新接收到数据时均会触发。但会合并触发。
    QByteArray tmpdata;
    if(m_connect_type == _wifi){
        tmpdata = p_tcp_new_connection->readAll();
    }
    else if(m_connect_type == _serial_com){
        tmpdata = p_com->readAll();
    }
    else{
        qDebug("error");
        return;
    }
    //新建文件用于存储原始数据
    /*if(!m_has_setup_newfile){
        delete p_datafile;
        QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd[hh-mm-ss]");
        p_datafile = new QFile(m_storePath+"/"+"raw_"+ current_time + "-ch" + QString::number(m_channel_number) + "-sample" + QString::number(m_sample_rate) + ".txt");
        if(!p_datafile->open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"warning", "can't open file to save data",QMessageBox::Yes);
        }
        else{
            m_has_setup_newfile = true;
        }
        delete p_debugfile;
        p_debugfile = new QFile(m_storePath+"/" + "Debug_msg"+ current_time + "-ch" + QString::number(m_channel_number) + "-sample" + QString::number(m_sample_rate) + ".txt");
        delete p_processed_file;
        p_processed_file = new QFile(m_storePath+"/" + "processed_"+ current_time + "-ch" + QString::number(m_channel_number) + "-sample" + QString::number(m_sample_rate) + ".txt");
        p_processed_file->open(QIODevice::WriteOnly);


        delete p_mark_file;
        p_mark_file = new QFile(m_storePath+"/" + "mark_"+ current_time + "-ch" + QString::number(m_channel_number) + "-sample" + QString::number(m_sample_rate) + ".txt");
        p_mark_file->open(QIODevice::WriteOnly);
    }
    p_datafile->write(tmpdata);
    if(m_glazer_on){
        p_glazerfile->write(tmpdata);
    }*/
    lock_m_buffer.lockForWrite();
    m_buffer.append(tmpdata);
    lock_m_buffer.unlock();

    // 文件存储限制(≈95M)
//    if(p_datafile->size()>100000000){
//        p_datafile->close();
//        m_has_setup_newfile = false;
//    }
    // 文件存储限制(≈190M)
    if(p_datafile->size()>200000000){
        p_datafile->close();
        m_has_setup_newfile = false;
    }
}
/*
void CommnicateBoard::slot_read_data_com(){
    //调试模式，接收发送命令的返回值
    if(m_command_return_mode){
        QByteArray tmpdata;
        if(m_connect_type == _wifi){
            tmpdata = p_tcp_new_connection->readAll();
        }
        else if(m_connect_type == _serial_com){
            tmpdata = p_com->readAll();
        }
        else{
            qDebug("error");
            return;
        }
        int return_data = int(tmpdata[0]&0xFF);
        QString content = QString::number(return_data,16);
        p_command_return_label->setText(content);
        return;
    }
    //接收逻辑
    //注：没有设置读取buffer大小，默认为无限制，适用于数据不能丢失场合。dataready信号在BUffer中有数据待读取和新接收到数据时均会触发。但会合并触发。
    QByteArray tmpdata = p_com->readAll();
    //新建文件用于存储原始数据
    if(!m_has_setup_newfile){
        delete p_datafile;
        QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd[hh-mm-ss]");
        p_datafile = new QFile(m_storePath+"/"+"raw_"+ current_time + ".txt");
        if(!p_datafile->open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"warning", "can't open file to save data",QMessageBox::Yes);
        }
        else{
            m_has_setup_newfile = true;
        }
        delete p_debugfile;
        p_debugfile = new QFile(m_storePath+"/" + "Debug_msg"+ current_time + ".txt");
        delete p_processed_file;
        p_processed_file = new QFile(m_storePath+"/" + "processed_"+ current_time + ".txt");
        p_processed_file->open(QIODevice::WriteOnly);
    }
    p_datafile->write(tmpdata);
    if(m_glazer_on){
        p_glazerfile->write(tmpdata);
    }
    lock_m_buffer.lockForWrite();
    m_buffer.append(tmpdata);
    lock_m_buffer.unlock();

    if(p_datafile->size()>100000000){
        p_datafile->close();
        m_has_setup_newfile = false;
    }
}
*/

void CommnicateBoard::slot_wifi_server_connect_error(QAbstractSocket::SocketError){
    QMessageBox::information(this,"提示","断开连接！",QMessageBox::Yes);
    m_has_start_board = false;
    emit signal_tcp_abort();
}
//从buffer中删除一定长度的数据，使得buffer第一个字节开始就是包序号。
void CommnicateBoard::find_head(){

}
/*************   更新存储路径  **************
 *  一般由外部调用
 */
void CommnicateBoard::set_store_path(QString path){
    m_storePath = path;
}
/*************   更改glazer启动选项  **************
 *  一般由外部调用
 */
QString CommnicateBoard::set_glazer_on(bool on){
    QString filename;
    m_glazer_on = on;
    /*if(on){
        QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd[hh-mm-ss]");
        filename = m_storePath+"/"+ current_time + "-ch" + QString::number(m_channel_number) + "-sample" + QString::number(m_sample_rate) + "-glazer.txt";
        p_glazerfile = new QFile(filename);
        if(!p_glazerfile->open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"warning", "can't open file to save glazer data",QMessageBox::Yes);
        }
    }
    else{
        p_glazerfile->close();
        delete p_glazerfile;
    }*/
    return filename;
}
/*************   清空存储  **************
 *
 */
void CommnicateBoard::flush(){
    //清空各种缓存数据
    lock_m_buffer.lockForWrite();
    m_buffer.clear();
    lock_m_buffer.unlock();
    lock_mark.lockForWrite();
    mark.clear();
    lock_mark.unlock();
    lock_data_from_wifi.lockForWrite();
    data_from_wifi.clear();
    lock_data_from_wifi.unlock();
    lock_elect_lead_off.lockForWrite();
    elect_lead_off.clear();
    lock_elect_lead_off.unlock();
}
/*************   发送命令至板子  **************
 *
 */
void CommnicateBoard::send_to_board(QByteArray data){
    //接收应答  在收到应答之前会重发五次，接收到应答 m_check_command_done=true
    //若要关闭应答功能，相应地，answer = false
    if(m_answer_mode){
        m_check_command_send_mode = true;
        m_check_command_type = data.at(1);
        int resend_count = 0;
        while(!m_check_command_done){
            // 收到应答之前重发5次
            if(resend_count >5){
                QString msg;
                for(int i=0; i<data.size(); ++i){
                    msg = msg+QString::number(static_cast<unsigned char>(data.at(i)),16)+" ";
                }
                // 重发5次失败则报错
                QMessageBox::critical(this,"error","命令多次重发失败: "+msg);
                qDebug("重发命令失败！");
                break;
            }
            if(m_connect_type == _wifi){
                p_tcp_new_connection->write(data);
                p_tcp_new_connection->waitForBytesWritten();
            }
            else if(m_connect_type == _serial_com){
                p_com->write(data);
            }
//            QTime timer = QTime::currentTime().addMSecs(50);
            QTime timer = QTime::currentTime().addMSecs(200);

            while( QTime::currentTime() < timer )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            resend_count++;
        }
        m_check_command_send_mode = false;
        m_check_command_done=false;
    }
    else{
        if(m_connect_type == _wifi){
            p_tcp_new_connection->write(data);
            p_tcp_new_connection->waitForBytesWritten();
        }
        else if(m_connect_type == _serial_com){
            p_com->write(data);
        }
//        QTime timer = QTime::currentTime().addMSecs(50);
        QTime timer = QTime::currentTime().addMSecs(200);

        while( QTime::currentTime() < timer )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    /*
    if(m_connect_type == _wifi){
        m_check_command_send_mode = true;
        m_check_command_type = data.at(1);
        int resend_count = 0;
        while(!m_check_command_done){
            if(resend_count >3){
                QMessageBox::critical(this,"error","命令多次重发失败:"+data);
                break;
            }
            p_tcp_new_connection->write(data);
            p_tcp_new_connection->waitForBytesWritten();
            QTime timer = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < timer )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            resend_count++;
        }
        m_check_command_send_mode = false;
        m_check_command_done=false;
    }
    else if(m_connect_type == _serial_com){
        m_check_command_send_mode = true;
        m_check_command_type = data.at(1);
        int resend_count = 0;
        while(!m_check_command_done){
            if(resend_count >3){
                QMessageBox::critical(this,"error","命令多次重发失败");
                break;
            }
            p_com->write(data);
            QTime timer = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < timer )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            resend_count++;
        }
        m_check_command_send_mode = false;
        m_check_command_done=false;
    }
    */
}
/*************   串口启动函数  **************
 *  一般由外部调用
 * （1）设置启动标识，发射启动信号
 * （2）下发当前连接状态命令
 */
void CommnicateBoard::com_start(QSerialPort *_serial_port){
    m_connect_type = _serial_com;
    p_com = _serial_port;
    p_com->setReadBufferSize(0);
    //qDebug()<<p_com->baudRate();
    //此时就设置为板子启动
    m_has_start_board = true;
    // 如果板子连接成功，则触发连接成功信号
    emit signal_board_start();
    // 如果板子连接成功，则触发连接成功信号
    emit signal_start_decode_data();
    QMessageBox::information(this,"提示", "串口连接成功！",QMessageBox::Yes);
    connect(p_com, SIGNAL(readyRead()), this, SLOT(slot_read_data()));
    //QByteArray data_send;
    //data_send.append(static_cast<char>(0xaa));
    //data_send.append(static_cast<char>(0x08));
    //data_send.append(static_cast<char>(0x01));
    //send_to_board(data_send);
}
/*************   串口停止  **************
 *  （1）停止标识（2）清空数据
 */
void CommnicateBoard::com_stop(){
    //m_find_head = false;
    //flush();
}
/*************   打开debug窗口  **************
 *  （1）子线程建立
 *  （2）子线程运行
 */
void CommnicateBoard::set_debug_on(){
    m_debug_on = true;
    p_debug_thread = new QThread(this);
    p_debug_process = new DebugShow(debug_msg_queue);
    p_debug_process->moveToThread(p_debug_thread);
    connect(p_debug_process,SIGNAL(signal_need_exit()),this,SLOT(slot_set_debug_off()));
    p_debug_thread->start();
    p_debug_process->run();
}
/*************   关闭debug窗口  **************
 *  用于外部调用
 */
void CommnicateBoard::set_debug_off(){
    if(m_debug_on)
        slot_set_debug_off();
}
/*************   关闭debug窗口  **************
 *
 */
void CommnicateBoard::slot_set_debug_off(){
    //qDebug()<<"thread exit";
    m_debug_on = false;
    lock_debug_msg_queue.lockForWrite();
    debug_msg_queue.clear();
    lock_debug_msg_queue.unlock();
    p_debug_thread->quit();
    p_debug_thread->wait();
    delete p_debug_process;
    p_debug_process = nullptr;
    delete p_debug_thread;
    p_debug_thread = nullptr;
}

//**********************************   数据包解析 ****************************************************
//************* 数据包包含4个部分：包序号（4字节，每字节小端先发）+mark（4字节，mark位于最小端最小bit位上）+通道数据（32*4字节，每字节小端先发）+脱落数据（8字节，展开为ch1p,ch2p,ch3p,...,ch32p,ch1n,ch2n,...,ch32n）
//*************
void Decode::slot_start_decode_data(){
    while(1){
        if(m_stop_flag)
            break;
        if(!m_find_head){
            //寻找包起始位置
            QTime time;
            time.start();
            //确保有足够数据，取调试信息阈值256和包大小二者的较大值,m_packet_size_decode表示每一包数据的大小（字节数）
            int size_need = 256>(m_packet_size_decode)?256:m_packet_size_decode;
            if(m_buffer_decode.size()<3*size_need){
                continue;
            }
            //移动窗口寻找包头
            int move_count=0;
            unsigned int ch_number1 = 0;
            unsigned int ch_number2 = 0;
            while (move_count<m_packet_size_decode+1){
                unsigned int flag_first_byte = static_cast<unsigned char>(m_buffer_decode[4]);   //第5字节标识,包头辅助判断，定值0xA5
                unsigned int flag_second_byte = static_cast<unsigned char>(m_buffer_decode[5]);  //第6字节标识,包头辅助判断，定值0x5A
                if((flag_first_byte == 0xA5)&&(flag_second_byte == 0x5A)){
                    unsigned int flag_third_byte = static_cast<unsigned char>(m_buffer_decode[6]); //第7字节标识,调试信息长度
                    ch_number1 = static_cast<unsigned int>((m_buffer_decode[0]&0xFF)|((m_buffer_decode[1]&0xFF)<<8)|((m_buffer_decode[2]&0xFF)<<16)|((m_buffer_decode[3]&0xFF)<<24));
                    if(flag_third_byte){
                        //如果是调试信息
                        ch_number2 = static_cast<unsigned int>((m_buffer_decode[flag_third_byte+9]&0xFF)|((m_buffer_decode[flag_third_byte+10]&0xFF)<<8)|((m_buffer_decode[flag_third_byte+11]&0xFF)<<16)|((m_buffer_decode[flag_third_byte+12]&0xFF)<<24));
                    }
                    else{
                        //如果是数据
                        ch_number2 = static_cast<unsigned int>((m_buffer_decode[m_packet_size_decode]&0xFF)|((m_buffer_decode[m_packet_size_decode+1]&0xFF)<<8)|((m_buffer_decode[m_packet_size_decode+2]&0xFF)<<16)|((m_buffer_decode[m_packet_size_decode+3]&0xFF)<<24));
                    }
                    //判断包序号是否递增
                    if(ch_number1+1 == ch_number2){
                        //定位成功，跳出循环
                        if(m_debug_on_decode){
                            lock_debug_msg_queue.lockForWrite();
                            debug_msg_queue_decode.append("find head, cost time:" + QByteArray::number(time.elapsed())+"ms, buffer size="+QByteArray::number(m_buffer_decode.size())+", new packet number="+QByteArray::number(ch_number1));
                            lock_debug_msg_queue.unlock();
                        }
                        //qDebug()<<"find head, cost time:" + QString::number(time.elapsed())+"ms,buffer size="+QString::number(m_buffer_decode.size());
                        m_packet_number_last = ch_number1-1;
                        break;
                    }
                }
                lock_m_buffer.lockForWrite();
                m_buffer_decode.remove(0,1);
                lock_m_buffer.unlock();
                move_count++;
            } //移动窗口结束
            if(move_count >= (m_packet_size_decode+1)){
                //如果移动窗口期间仍未定位成功，则继续循环定位
                qDebug()<<"Error: can not find data packet head, cost time:" + QString::number(time.elapsed())+"ms";
                continue;
            }
            else{
                m_find_head = true;
            }
        }
        while(m_buffer_decode.size()>=m_packet_size_decode){//包长度：4+4+4*通道数+8=144。由于Tcp传输中自行拆包为不同长短的包进行传输，这里等待足够一包的数据量后进行处理
            //包序号检测
            // QByteArray one_packet_data = m_buffer_decode.left(m_packet_size_decode);
            // 条件1：辅助标识等于定值
            unsigned int flag_first_byte = static_cast<unsigned char>(m_buffer_decode[4]);   //第5字节标识,包头辅助判断，定值0xA5
            unsigned int flag_second_byte = static_cast<unsigned char>(m_buffer_decode[5]);  //第6字节标识,包头辅助判断，定值0x5A
            if((flag_first_byte != 0xA5)||(flag_second_byte != 0x5A)){
                m_find_head = false;
                break;
            }
            // 条件2：包序号递增
            QByteArray packet_number_4_byte =  m_buffer_decode.left(4);
            QByteArray packet_msg_byte =  m_buffer_decode.left(7).right(1);
            QByteArray packet_mark_byte =  m_buffer_decode.left(8).right(1);
            unsigned int packet_number_now = static_cast<unsigned int>((packet_number_4_byte[0]&0xFF)|((packet_number_4_byte[1]&0xFF)<<8)|((packet_number_4_byte[2]&0xFF)<<16)|((packet_number_4_byte[3]&0xFF)<<24));
            if(m_packet_number_last+1!=packet_number_now){
                m_find_head = false;
                break;
            }
            m_packet_number_last = packet_number_now;
            //获取debug信息
            int debug_msg_length = static_cast<unsigned char>(packet_msg_byte[0]);
            if(debug_msg_length){
                if(m_buffer_decode.size()<debug_msg_length){
                    break;//等待数据扩充
                }
                //累加和校验,硬件端仅累加不取反
                unsigned char sum_check = 0;
                for(int i=0;i<8+debug_msg_length;++i){
                    sum_check += m_buffer_decode.at(i);
                }
                if(sum_check!=static_cast<unsigned char>(m_buffer_decode.at(8+debug_msg_length))){
                    lock_m_buffer.lockForWrite();
                    m_buffer_decode.remove(0,9+debug_msg_length);
                    lock_m_buffer.unlock();
                    lock_debug_msg_queue.lockForWrite();
                    debug_msg_queue_decode.append("CheckSum error");
                    lock_debug_msg_queue.unlock();
                    continue;
                }
                //开始解析
                lock_m_buffer.lockForWrite();
                m_buffer_decode.remove(0,8);
                lock_m_buffer.unlock();
                //qDebug()<<"2";
                lock_m_buffer.lockForWrite();
                QByteArray msg = m_buffer_decode.left(debug_msg_length);
                lock_m_buffer.unlock();
                p_debugfile_decode->open(QIODevice::WriteOnly|QIODevice::Append);
                p_debugfile_decode->write(msg);
                p_debugfile_decode->close();
                lock_m_buffer.lockForWrite();
                m_buffer_decode.remove(0,debug_msg_length+1);//移除调试信息与校验
                lock_m_buffer.unlock();
                if(m_debug_on_decode){
                    lock_debug_msg_queue.lockForWrite();
                    debug_msg_queue_decode.append(msg);
                    lock_debug_msg_queue.unlock();
                }
                continue;
            }
            m_packet_number_last = packet_number_now;
            //累加和校验,硬件端仅累加不取反
            unsigned char sum_check = 0;
            for(int i=0;i<m_packet_size_decode-1;++i){
                sum_check += (m_buffer_decode.at(i)&0xff);
            }
            if(sum_check!=static_cast<unsigned char>(m_buffer_decode.at(m_packet_size_decode-1)&0xff)){
                lock_m_buffer.lockForWrite();
                m_buffer_decode.remove(0,m_packet_size_decode);
                lock_m_buffer.unlock();
                lock_debug_msg_queue.lockForWrite();
                debug_msg_queue_decode.append("CheckSum error");
                lock_debug_msg_queue.unlock();
                continue;
            }
            if(packet_number_now==1638){
                qDebug()<<"1";
            }
            //获取一个字节，目前仅8bit中的最低位代表标记信息，1有效，其他位均为0，即不做处理
            bool ok;
            qint8 mark_tmp = static_cast<qint8>(packet_mark_byte.toHex().toInt(&ok,16));
            lock_mark.lockForWrite();
            mark_decode.append(mark_tmp);
            lock_mark.unlock();
            //new
            QByteArray tmp_data1 = QByteArray::number(mark_tmp);
            tmp_data1.append(' ');
            //p_mark_file_decode->write(tmp_data1);
            //统一移除前8个字节
            lock_m_buffer.lockForWrite();
            m_buffer_decode.remove(0,8);
            lock_m_buffer.unlock();
            //qDebug()<<"3";
            //处理数据
            if(m_channel_number_decode<32){
                for(int channel = 0 ; channel<m_channel_number_decode; ++channel){
                    QByteArray _4byte =  m_buffer_decode.left(4);//取4个字节
                    lock_m_buffer.lockForWrite();
                    m_buffer_decode.remove(0,4);//从buffer中删去读取的4个字节
                    lock_m_buffer.unlock();
                    int perchannel_data = (_4byte[0]&0x000000FF)|((_4byte[1]&0x000000FF)<<8)|((_4byte[2]&0x000000FF)<<16)|((_4byte[3]&0x000000FF)<<24);
                    if(channel<m_channel_number_decode-1)
                    {
                        double r4 = static_cast<double>(perchannel_data)/24.0;//24倍增益
                        lock_data_from_wifi.lockForWrite();
                        data_from_wifi_decode.append(r4);//将QBytearray转换成double存入队列
                        lock_data_from_wifi.unlock();
                        QByteArray tmp_data = QByteArray::number(r4,'f',2);
                        tmp_data.append(' ');
                        p_processed_file_decode->write(tmp_data);
                        //qDebug()<<"writedata glazer_time"<<glazer_time;

                        /*if(50<=glazer_time&&glazer_time<=110)
                        {
                            preRest->write(tmp_data);
                        }
                        if(glazer_time==115)
                        {
                            preRest->close();
                        }
                        if(135<=glazer_time&&glazer_time<=208)
                        {

                            Rapid->write(tmp_data);
                        }
                        if(glazer_time==215)
                        {
                            Rapid->close();
                        }
                        if(225<=glazer_time&&glazer_time<=345)
                        {

                            Tonic->write(tmp_data);
                        }
                        if(glazer_time==350)
                        {
                            Tonic->close();
                        }
                        if(355<=glazer_time&&glazer_time<=445)
                        {

                            Endur->write(tmp_data);
                        }
                        if(glazer_time==448)
                        {
                            Endur->close();
                        }
                        if(450<=glazer_time&&glazer_time<=512)
                        {

                            postRest->write(tmp_data);
                        }
                        if(glazer_time==513)
                        {
                            postRest->close();
                        }*/


                    }
                    else
                    {
                        double r4 = static_cast<double>(perchannel_data)/24.0/10.0;//24倍增益
                        lock_data_from_wifi.lockForWrite();
                        data_from_wifi_decode.append(r4);//将QBytearray转换成double存入队列
                        lock_data_from_wifi.unlock();
                        QByteArray tmp_data = QByteArray::number(r4,'f',2);
                        tmp_data.append(' ');
                        p_processed_file_decode->write(tmp_data);
                        /*if(50<=glazer_time&&glazer_time<=110)
                        {
                            preRest->write(tmp_data);
                        }
                        if(glazer_time==115)
                        {
                            preRest->close();
                        }
                        if(135<=glazer_time&&glazer_time<=208)
                        {

                            Rapid->write(tmp_data);
                        }
                        if(glazer_time==215)
                        {
                            Rapid->close();
                        }
                        if(225<=glazer_time&&glazer_time<=345)
                        {

                            Tonic->write(tmp_data);
                        }
                        if(glazer_time==350)
                        {
                            Tonic->close();
                        }
                        if(355<=glazer_time&&glazer_time<=445)
                        {

                            Endur->write(tmp_data);
                        }
                        if(glazer_time==448)
                        {
                            Endur->close();
                        }
                        if(450<=glazer_time&&glazer_time<=512)
                        {

                            postRest->write(tmp_data);
                        }*/

                    }

                }
                //读取8字节电极脱落数据,每字节8bit ,含8通道 p或n状态
                //如果通道数小于8，则电极脱落数据只保存2字节，否则保存8字节
                //elect_lead_off_decode[64] 为：ch1p,ch2p,ch3p,...,ch32p,ch1n,ch2n,...,ch32n
                if (m_channel_number_decode<=8){
                    QByteArray _2byte = m_buffer_decode.left(2);
                    lock_m_buffer.lockForWrite();
                    m_buffer_decode.remove(0,2);
                    lock_m_buffer.unlock();
                    lock_elect_lead_off.lockForWrite();
                    for (int i=0; i<m_channel_number_decode*2; ++i){
                        elect_lead_off_decode.append(_2byte[i/m_channel_number_decode] & (1<<i));
                    }
                    lock_elect_lead_off.unlock();
                }
                else{
                    QByteArray _8byte =  m_buffer_decode.left(8);
                    lock_m_buffer.lockForWrite();
                    m_buffer_decode.remove(0,8);
                    lock_m_buffer.unlock();
                    lock_elect_lead_off.lockForWrite();
                    for (int i=0; i<m_channel_number_decode*2; ++i){
                        elect_lead_off_decode.append(_8byte[i/m_channel_number_decode] & (1<<i));
                    }
                    lock_elect_lead_off.unlock();
                }
            }
            // 通道数大于等于32时的数据处理
            else{
                bool prerest_flag=false;
                bool rapid_flag=false;
                bool tonic_flag=false;
                bool endur_flag=false;
                bool postrest_flag=false;
                bool glazer_whole_flag=false;
                if(glazer_time!=0){glazer_whole_flag=true;}
                if(glazer_time==0){glazer_whole_flag=false;}
                if(50<=glazer_time&&glazer_time<=110)
                {
                    prerest_flag = true;
                    rapid_flag=false;
                    tonic_flag=false;
                    endur_flag=false;
                    postrest_flag=false;
                    //qDebug("data saved");
                }
                else
                {
                    prerest_flag = false;
                }

                if(glazer_time==115)
                {
                    preRest->close();
                }
                if(137<=glazer_time&&glazer_time<=217)
                {

                    prerest_flag = false;
                    rapid_flag=true;
                    tonic_flag=false;
                    endur_flag=false;
                    postrest_flag=false;
                }
                else
                {
                    rapid_flag=false;
                }

                if(glazer_time==220)
                {
                    Rapid->close();
                }
                if(230<=glazer_time&&glazer_time<=352)
                {

                    prerest_flag = false;
                    rapid_flag=false;
                    tonic_flag=true;
                    endur_flag=false;
                    postrest_flag=false;
                }
                else
                {
                    tonic_flag=false;
                }
                if(glazer_time==353)
                {
                    Tonic->close();
                }
                if(357<=glazer_time&&glazer_time<=449)
                {

                    prerest_flag = false;
                    rapid_flag=false;
                    tonic_flag=false;
                    endur_flag=true;
                    postrest_flag=false;
                }
                else
                {
                    endur_flag=false;
                }
                if(glazer_time==452)
                {
                    Endur->close();
                }
                if(454<=glazer_time&&glazer_time<=518)
                {

                    prerest_flag = false;
                    rapid_flag=false;
                    tonic_flag=false;
                    endur_flag=false;
                    postrest_flag=true;
                }
                else
                {
                    postrest_flag=false;
                }
                if(glazer_time==519)
                {
                    postRest->close();
                }
                int times_32channel = m_channel_number_decode/32;
                for(int channel32count = 0; channel32count<times_32channel; ++channel32count){
                    //填充通道数据   
                    for(int channel = 0 ; channel<32; ++channel){
                        QByteArray _4byte =  m_buffer_decode.left(4);//取4个字节
                        lock_m_buffer.lockForWrite();
                        m_buffer_decode.remove(0,4);//从buffer中删去读取的4个字节
                        lock_m_buffer.unlock();
                        int perchannel_data = (_4byte[0]&0x000000FF)|((_4byte[1]&0x000000FF)<<8)|((_4byte[2]&0x000000FF)<<16)|((_4byte[3]&0x000000FF)<<24);
                        if(channel<31)
                        {
                            double r4 = static_cast<double>(perchannel_data)/24.0;//24倍增益
                            lock_data_from_wifi.lockForWrite();
                            data_from_wifi_decode.append(r4);//将QBytearray转换成double存入队列
                            lock_data_from_wifi.unlock();
                            QByteArray tmp_data = QByteArray::number(r4,'f',2);
                            tmp_data.append(' ');
                            //p_processed_file_decode->write(tmp_data);
                            if(glazer_whole_flag){glazer_whole->write(tmp_data);}
                            if(prerest_flag){preRest->write(tmp_data);}
                            if(rapid_flag){Rapid->write(tmp_data);}
                            if(tonic_flag){Tonic->write(tmp_data);}
                            if(endur_flag){Endur->write(tmp_data);}
                            if(postrest_flag){postRest->write(tmp_data);}
                        }
                        else
                        {
                            double r4 = static_cast<double>(perchannel_data)/24.0/10.0;//24倍增益
                            lock_data_from_wifi.lockForWrite();
                            data_from_wifi_decode.append(r4);//将QBytearray转换成double存入队列
                            lock_data_from_wifi.unlock();
                            QByteArray tmp_data = QByteArray::number(r4,'f',2);
                            tmp_data.append(' ');
                            //p_processed_file_decode->write(tmp_data);
                            //glazer_whole->write(tmp_data);
                            if(glazer_whole_flag){glazer_whole->write(tmp_data);}
                            if(prerest_flag){preRest->write(tmp_data);}
                            if(rapid_flag){Rapid->write(tmp_data);}
                            if(tonic_flag){Tonic->write(tmp_data);}
                            if(endur_flag){Endur->write(tmp_data);}
                            if(postrest_flag){postRest->write(tmp_data);}
                        }


                    }
                    //读取8字节电极脱落数据,每字节8bit ,含8通道 p或n状态
                    //elect_lead_off_decode[64] 为：ch1p,ch2p,ch3p,...,ch32p,ch1n,ch2n,...,ch32n
                    for (int i = 0; i<8; ++i){
                        bool ok;
                        qint8 _1byte =static_cast<qint8>( m_buffer_decode.left(1).toHex().toInt(&ok,16));
                        lock_m_buffer.lockForWrite();
                        m_buffer_decode.remove(0,1);
                        lock_m_buffer.unlock();
                        if(!ok){
                            qDebug("can not convert lead off data");
                        }
                        else{
                            lock_elect_lead_off.lockForWrite();
                            elect_lead_off_decode.append(_1byte&0x01);
                            elect_lead_off_decode.append(_1byte&0x02);
                            elect_lead_off_decode.append(_1byte&0x04);
                            elect_lead_off_decode.append(_1byte&0x08);
                            elect_lead_off_decode.append(_1byte&0x10);
                            elect_lead_off_decode.append(_1byte&0x20);
                            elect_lead_off_decode.append(_1byte&0x40);
                            elect_lead_off_decode.append(_1byte&0x80);
                            lock_elect_lead_off.unlock();
                        }
                    }
                }
            }
            //qDebug()<<"4";
            //移除校验
            lock_m_buffer.lockForWrite();
            m_buffer_decode.remove(0,1);
            lock_m_buffer.unlock();
        } //while decode end
    }//while 1 end
}

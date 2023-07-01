#ifndef COMMUNICATEBOARD_H
#define COMMUNICATEBOARD_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QDialog>
#include <QQueue>
#include <QFile>
#include <QVector>
#include <QLabel>
#include <QObject>
#include <QThread>
#include <windows.h>
#include <QSerialPort>
#include <QThread>
#include <QTime>
#include <QReadWriteLock>
#include <QCoreApplication>

#include "debugwidget.h"

using namespace std;
static QReadWriteLock lock_m_buffer;
extern QReadWriteLock lock_debug_msg_queue;
extern QReadWriteLock lock_mark;
extern QReadWriteLock lock_data_from_wifi;
extern QReadWriteLock lock_elect_lead_off;

enum TcpType{
    Tcp_server,
    Tcp_client,
};

enum ConnectType{
    _serial_com,
    _wifi,
    _no_connect
};
class DebugShow;
class Decode;
class ReadSavedFile;

class CommnicateBoard:public QDialog
{    
    Q_OBJECT
public:
     explicit CommnicateBoard( QString ip_in, quint16 port_in,TcpType tcp_type, int N_channel, int sample_rate, QLabel* label);
     ~CommnicateBoard();

     void wifi_client_connect_board();
     void wifi_server_connect_board();
     void set_store_path(QString );
     void wifi_update_port(quint16);
     void wifi_update_ip(QString);
     void set_channel_Arg(int ch_number, int samplerate);
     void flush();
     void send_to_board(QByteArray);
     void com_start(QSerialPort* _serial_port);
     void com_stop();
     void set_debug_on();
     void set_debug_off();
     void file_read_data(int size, QFile* fd);
     bool isReadDone();
     QString set_glazer_on(bool);

     QTcpSocket *p_tcp_new_connection= nullptr;
     QTcpSocket *p_tcp_client= nullptr;
     QTcpServer *p_tcp_server= nullptr;
     QSerialPort *p_com= nullptr;
     QLabel* p_command_return_label= nullptr;
     QFile* p_datafile= nullptr;   //原始数据，存储一切
     QFile* p_glazerfile= nullptr;  //glazer数据
     QFile* p_debugfile=nullptr;    //调试数据
     QFile* p_processed_file= nullptr; //仅有用数据
     QFile* p_mark_file = nullptr;//用于记录mark
     QThread *p_debug_thread = nullptr;
     DebugShow *p_debug_process = nullptr;
     QThread *p_decode_thread = nullptr;
     Decode *p_decode_process = nullptr;
     ReadSavedFile *p_readfile = nullptr;

     QQueue<qint8> mark;
     QQueue<double> data_from_wifi;
     QQueue<bool> elect_lead_off;
     QQueue<QByteArray> debug_msg_queue;

     int m_channel_number;
     int m_sample_rate;
     bool m_has_start_board;
     bool m_command_return_mode;
     bool m_has_setup_newfile;
     bool m_glazer_on;
     bool m_debug_on;
     bool m_read_done;
     bool m_answer_mode;
     //bool m_find_head;
     int m_packet_size;
     //unsigned int m_packet_number_last;
     QByteArray m_buffer;
     QString m_storePath;
     ConnectType m_connect_type;
     //QString glazer_path;



signals:
     void signal_board_start();
     void signal_tcp_abort();
     void signal_start_decode_data();

private:    
     TcpType m_tcp_type;
     QString m_ip;
     quint16 m_port;
     bool m_check_command_send_mode;
     char m_check_command_type;     //即AA xx中的xx ,1字节
     bool m_check_command_done;

     void find_head();

private slots:
     void slot_wifi_tcp_client_connect_success();
     void slot_wifi_tcp_client_connect_failed();
     void slot_wifi_tcp_client_find_host();
     void slot_wifi_tcp_client_read_data();
     void slot_wifi_tcp_server_new_connect();
     void slot_wifi_server_connect_error(QAbstractSocket::SocketError);
     void slot_read_data();
     //void slot_read_data_com();
     void slot_set_debug_off();
};

//Debug窗口需要与波形同时显示，需要多线程。这里采用movetoThread的方法。新建一个需要在子线程中运行的类。
class DebugShow: public QObject
{
    Q_OBJECT
public:
    explicit DebugShow(QQueue<QByteArray>& msg_queue):
        debug_msg_queue(msg_queue){}
    ~DebugShow(){
        if(p_debug_widget) delete p_debug_widget;
    }
    void destory_widget(){
        if(p_debug_widget!=nullptr){
            delete p_debug_widget;
            p_debug_widget = nullptr;
        }
    }
signals:
    void signal_need_exit();
public slots:
    void run(){
        p_debug_widget =new DebugWidget(debug_msg_queue);
        p_debug_widget->show();
        //槽函数链接，debug窗口关闭时，需让线程退出。
        connect(p_debug_widget,SIGNAL(signal_debug_widget_close()),this,SLOT(slot_exit_widget()));
    }
    void slot_exit_widget(){
        emit signal_need_exit();
    }
private:
    DebugWidget *p_debug_widget=nullptr;
    QQueue<QByteArray>& debug_msg_queue;
};

class Decode: public QObject
{
    Q_OBJECT
public:
    explicit Decode(int& m_channel_number,
                    int& m_packet_size,
                    bool &m_debug_on,
                    QByteArray& m_buffer,
                    QQueue<qint8>& mark,
                    QFile* & p_mark_file,
                    QQueue<double>& data_from_wifi,
                    QQueue<bool>& elect_lead_off,
                    QFile* & p_processed_file,
                    QFile* &p_debugfile,
                    QQueue<QByteArray>& debug_msg_queue):
        m_channel_number_decode(m_channel_number),
        m_packet_size_decode(m_packet_size),
        m_debug_on_decode(m_debug_on),
        m_buffer_decode(m_buffer),
        mark_decode(mark),
        p_mark_file_decode(p_mark_file),
        data_from_wifi_decode(data_from_wifi),
        elect_lead_off_decode(elect_lead_off),
        p_processed_file_decode(p_processed_file),
        p_debugfile_decode(p_debugfile),
        debug_msg_queue_decode(debug_msg_queue)
    {
        m_find_head = false;
        m_stop_flag = false;
        m_packet_number_last = 0;
    }
    ~Decode(){}
    bool m_stop_flag;
    int glazer_time = 0;
    QString glazer_store_path;
    QFile* preRest;
    QFile* Rapid;
    QFile* Tonic;
    QFile* Endur;
    QFile* postRest;
    QFile* glazer_whole;
    bool glazer_running = false;


public slots:
    void slot_start_decode_data();
private:
    bool m_find_head;
    unsigned int m_packet_number_last;
    int& m_channel_number_decode;
    int& m_packet_size_decode;
    bool &m_debug_on_decode;
    QByteArray& m_buffer_decode;
    QQueue<qint8>& mark_decode;
    QFile* & p_mark_file_decode;
    QQueue<double>& data_from_wifi_decode;
    QQueue<bool>& elect_lead_off_decode;
    QFile* & p_processed_file_decode;
    QFile* &p_debugfile_decode;
    QQueue<QByteArray>& debug_msg_queue_decode;
};

class ReadSavedFile: public QThread
{
    Q_OBJECT
    public:
    ReadSavedFile(QByteArray& m_buffer, bool m_read_done):m_buffer_readfile(m_buffer),m_read_done_readfile(m_read_done)
    {file_fd = nullptr; readsize =0;}
    void run();
    void set(int _size, QFile* _fd){readsize = _size; file_fd = _fd;}

    QFile *file_fd;
    int readsize;
    QByteArray& m_buffer_readfile;
    bool m_read_done_readfile;
};

#endif // CommnicateBoard_H

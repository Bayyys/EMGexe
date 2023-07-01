#include "debugwidget.h"
#include "ui_debugwidget.h"

QReadWriteLock lock_debug_msg_queue;

DebugWidget::DebugWidget(QQueue<QByteArray>& _msg_queue, QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::DebugWidget),
    msg_queue(_msg_queue)
{
    ui->setupUi(this);
    this->setWindowTitle("调试消息");

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_show_message()));
    timer->setInterval(100);
    timer->start();
}

DebugWidget::~DebugWidget()
{
    delete ui;
    delete timer;
}
void DebugWidget::closeEvent(QCloseEvent*){
    emit signal_debug_widget_close();
}
void DebugWidget::slot_show_message(){
    //ui->textBrowser->append("tmp_msg");
    //lock_debug_msg_queue.lockForWrite();
    int size = msg_queue.size();
    //lock_debug_msg_queue.unlock();
    //ui->textBrowser->append(QString::number(size));
    for(int i=0; i<size; ++i){
        lock_debug_msg_queue.lockForWrite();
        QByteArray tmp_msg = msg_queue.front();//front 需要判空， 判空比较头、尾指针
        msg_queue.pop_front();
        lock_debug_msg_queue.unlock();
        ui->textBrowser->append(tmp_msg);
    }
}
void DebugWidget::slot_clear_widget(){
    ui->textBrowser->clear();
}

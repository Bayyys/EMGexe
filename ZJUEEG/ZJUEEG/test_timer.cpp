#include "test_timer.h"
#include "ui_test_timer.h"
#include "QTimer"
#include "QMediaPlayer"

test_timer::test_timer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test_timer)
{
    ui->setupUi(this);
}


test_timer::~test_timer()
{
    delete ui;
}

void test_timer::on_pushButton_clicked()
{
    QTimer *timer;
    timer = new  QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(torest()));
    //timer->start( 1000 );
    QMediaPlayer *player;
    player = new QMediaPlayer;
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromEncoded("qrc://Glazer.mp3"));
    player->setVolume(50);
    player->play();

    qDebug() << "main: tid = " << player->state(); //打印main函数所在的线程ID


}

void test_timer::torest()
{
    ui->pushButton->setEnabled(false);
    count++;
    ui->label->setNum(count);
}

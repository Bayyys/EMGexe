#include "portset.h"
#include "ui_portset.h"
#include <QDebug>

QString selected_port_name;

PortSet::PortSet(QVector<QString> &port_name, QSerialPort *port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSet)
{
    ui->setupUi(this);
    this->setWindowTitle("串口配置");

    QString config_file_name = "config.ini";
    QSettings *p_ini = new QSettings(config_file_name,QSettings::IniFormat);
    ui->bandrate->setText(p_ini->value("band_rate").toString());
    ui->data_bit->setCurrentIndex(p_ini->value("data_bit_index").toInt());
    ui->stop_bit->setCurrentIndex(p_ini->value("stop_bit_index").toInt());

    serial_port = port;
    for(QVector<QString>::iterator it= port_name.begin(); it!= port_name.end(); ++it){
        ui->port_name->addItem(*it);
    }
    connect(this,SIGNAL(accepted()),this,SLOT(update_arg()));
}

PortSet::~PortSet()
{
    delete ui;
}

void PortSet::update_arg(){
    updateIniFile();

    serial_port->close();
    serial_port->setPortName(ui->port_name->currentText());
    selected_port_name = ui->port_name->currentText();
    qDebug() << selected_port_name;
    serial_port->setBaudRate(qint32(ui->bandrate->text().toInt()));
    switch (ui->data_bit->currentIndex()) {
    case 0:
        serial_port->setDataBits(QSerialPort::Data8);
        break;
    case 1:
        serial_port->setDataBits(QSerialPort::Data7);
        break;
    case 2:
        serial_port->setDataBits(QSerialPort::Data6);
        break;
    case 3:
        serial_port->setDataBits(QSerialPort::Data5);
        break;
    default:
        serial_port->setDataBits(QSerialPort::Data8);
        break;
    }
    switch (ui->stop_bit->currentIndex()) {
    case 0:
        serial_port->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        serial_port->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serial_port->setStopBits(QSerialPort::TwoStop);
        break;
    }
    serial_port->setParity(QSerialPort::NoParity);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);

    emit portSetDone();
}
void PortSet::updateIniFile(){
    QString config_file_name = "config.ini";
    QSettings *p_ini = new QSettings(config_file_name,QSettings::IniFormat);
    p_ini->setValue("band_rate", ui->bandrate->text().toInt());
    p_ini->setValue("data_bit_index", ui->data_bit->currentIndex());
    p_ini->setValue("stop_bit_index", ui->stop_bit->currentIndex());
    delete p_ini;
}

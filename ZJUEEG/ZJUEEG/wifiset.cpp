#include "wifiset.h"
#include "ui_wifiset.h"

WifiSet::WifiSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WifiSet)
{   
    ui->setupUi(this);
    this->setWindowTitle("配置Wi-Fi");

    QSettings *p_ini = new QSettings("config.ini",QSettings::IniFormat);
    ui->ssid_lineEdit->setText(p_ini->value("wifi_ssid").toString());
    ui->ip_lineEdit->setText(p_ini->value("wifi_ip").toString());
    ui->port_lineEdit->setText(p_ini->value("wifi_port").toString());
    ui->password_lineEdit->setText(p_ini->value("wifi_password").toString());
    delete p_ini;

    connect(this,SIGNAL(accepted()),this,SLOT(update_arg()));
}

WifiSet::~WifiSet()
{
    delete ui;
}

void WifiSet::update_arg(){
    if(ui->ssid_lineEdit->text()==""||ui->ip_lineEdit->text()==""||ui->port_lineEdit->text()==""){
        QMessageBox::critical(this,"error","Wi-Fi配置信息输入不全");
        return;
    }
    QSettings *p_ini = new QSettings("config.ini",QSettings::IniFormat);
    p_ini->setValue("wifi_ssid",ui->ssid_lineEdit->text());
    p_ini->setValue("wifi_ip",ui->ip_lineEdit->text());
    p_ini->setValue("wifi_port",ui->port_lineEdit->text());
    p_ini->setValue("wifi_password",ui->password_lineEdit->text());
    delete p_ini;
    emit wifi_arg_change(ui->ssid_lineEdit->text(),ui->ip_lineEdit->text(),ui->port_lineEdit->text(),ui->password_lineEdit->text());
}

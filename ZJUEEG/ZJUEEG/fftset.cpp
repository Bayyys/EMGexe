/*
 * 菜单栏中FFT对话框实现
 * 可选择自动坐标系或手动输入
 */

#include "fftset.h"
#include "ui_fftset.h"

FFTSet::FFTSet(bool self_control,double xmin,double xmax,double ymin,double ymax,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FFTSet)
{    
    ui->setupUi(this);
    this->setWindowTitle("FFT坐标配置");

    if(self_control){
        ui->selfControl->setChecked(true);
        ui->Ymax->setEnabled(false);
        ui->Ymin->setEnabled(false);
        ui->Xmax->setEnabled(false);
        ui->Xmin->setEnabled(false);
        selfcontrol = true;
    }
    else{
        ui->selfControl->setChecked(false);
        ui->Ymax->setEnabled(true);
        ui->Ymin->setEnabled(true);
        ui->Xmax->setEnabled(true);
        ui->Xmin->setEnabled(true);
        ui->Ymax->setText(QString::number(ymax,'f',2));
        ui->Ymin->setText(QString::number(ymin,'f',2));
        ui->Xmax->setText(QString::number(xmax,'f',2));
        ui->Xmin->setText(QString::number(xmin,'f',2));
        selfcontrol = false;
    }
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(changeFFTSet()));
}

FFTSet::~FFTSet()
{
    delete ui;
}

void FFTSet::changeSelfControl(){
    if(Qt::Checked == ui->selfControl->checkState()){
        ui->Ymax->setEnabled(false);
        ui->Ymin->setEnabled(false);
        ui->Xmax->setEnabled(false);
        ui->Xmin->setEnabled(false);
        selfcontrol = true;
    }
    else if(Qt::Unchecked == ui->selfControl->checkState()){
        ui->Ymax->setEnabled(true);
        ui->Ymin->setEnabled(true);
        ui->Xmax->setEnabled(true);
        ui->Xmin->setEnabled(true);
        selfcontrol = false;
    }
}

void FFTSet::changeFFTSet(){
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
}

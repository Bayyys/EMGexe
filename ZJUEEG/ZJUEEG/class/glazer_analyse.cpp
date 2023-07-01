#include "glazer_analyse.h"
#include <QDir>
#include <QTime>
#include <QTextStream>
#include <QMessageBox>
#include <QObject>
#include "wordengine.h"
#include <qdebug.h>

#include <iostream>
using namespace std;



Glazer_analyse::Glazer_analyse()
{
    //新建文件夹，确定存储路径
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_time = current_date_time.toString("yyyy-MM-dd[hh-mm-ss]");
    m_storePath = QDir::currentPath()+"/ZJUEEGDATA"+"/" +current_time;

    QDir dir(m_storePath);
    if(!dir.exists()){
        bool ok =dir.mkdir(m_storePath);
        if(!ok)
            qDebug("save path mkdir failed");
    }
    QLibrary PreRestlib(QDir::currentPath()+"/libs/preRest.dll");   //声明所用到的dll文件
    PreRestlib.load();
    RunPreRest=(Funprerest)PreRestlib.resolve("RunPreRest");    //援引 RunPreRest() 函数
    QLibrary Rapidlib(QDir::currentPath()+"/libs/Rapid.dll");   //声明所用到的dll文件
    Rapidlib.load();
    RunRapid=(Funprapid)Rapidlib.resolve("RunRapid");    //援引 RunRapid() 函数
    QLibrary Toniclib(QDir::currentPath()+"/libs/Tonic.dll");   //声明所用到的dll文件
    Toniclib.load();
    RunTonic=(FunTonic)Toniclib.resolve("RunTonic");    //援引 RunTonic() 函数
    QLibrary Endurlib(QDir::currentPath()+"/libs/Endur.dll");   //声明所用到的dll文件
    Endurlib.load();
    RunEndur=(FunEndur)Endurlib.resolve("RunEndur");    //援引 RunEndur() 函数
    QLibrary PostRestlib(QDir::currentPath()+"/libs/PostRest.dll");   //声明所用到的dll文件
    PostRestlib.load();
    RunPostRest=(FunPostRest)PostRestlib.resolve("RunPostRest");    //援引 RunPostRest() 函数
    QLibrary Reportlib(QDir::currentPath()+"/libs/SaveReport.dll");   //声明所用到的dll文件
    Reportlib.load();
    SaveReportData=(Report)Reportlib.resolve("SaveReportData");    //援引 SaveReportData() 函数
    running = true;
    glazer_done_state = false;

}

void Glazer_analyse::PreRest(double*x,int len)
{
    qDebug("PreRest start");
    RunPreRest(x,len,smoothdegree,smoothlength,RMSlength,fs,PreRest_Mean_RMS,PreRest_Mean_CV,PreRest_WL,PreRest_MF_data,&PreRest_MF_size);
    qDebug("PreRest end");
        return;
}

void Glazer_analyse::Rapid(double*x,int len)
{
    qDebug("Rapid start");
    RunRapid(x,len,smoothdegree,smoothlength,RMSlength,fs,Rapid_Peak_RMS_Mean,
           Rapid_Peak_Var,Rapid_Raisetime_Mean, Rapid_Raisetime_Var, Rapid_MF_List);
    qDebug("Rapid end");
        return;
}
void Glazer_analyse::Tonic(double*x,int len)
{
    qDebug("Tonic start");
    RunTonic(PreRest_Mean_RMS,x,len,smoothdegree,smoothlength,RMSlength,fs,
                 Tonic_RMS_Mean, Tonic_Norm_Mean, Tonic_CV_Mean,
                 Tonic_Norm_Var, Tonic_CV_Var, Tonic_RMS_Var, Tonic_MF_List);
    qDebug("Tonic end");
        return;
}
void Glazer_analyse::Endur(double *x, int len)
{
    qDebug("Endur start");
    RunEndur(PreRest_Mean_RMS, x,len, smoothdegree, smoothlength, RMSlength,
            fs,Endur_RMS_Mean, Endur_Norm, Endur_CV,
            Endur_prepost10_Rate, Endur_MF, Endur_Slope);
    qDebug("Endur end");
        return;
}
void Glazer_analyse::PostRest(double*x,int len)
{
    qDebug("PostRest start");
    RunPostRest(PreRest_Mean_RMS,PreRest_Mean_CV,PreRest_WL,PreRest_MF_data, x,len, smoothdegree, smoothlength, RMSlength,fs,
         PostRest_Mean_RMS, PostRest_Mean_CV, PostRest_WL, PostRest_MF_data,
               &MF_size, Rest_RMS_Rate, Rest_CV_Rate,
               Rest_MF_Rate, Rest_WL_Rate);
    qDebug("PostRest end");
    save_report_data();
        return;
}

void Glazer_analyse::save_report_data()
{
    SaveReportData(
          Rapid_Peak_RMS_Mean, Rapid_Raisetime_Mean, Tonic_RMS_Mean,
          Tonic_Norm_Mean, Endur_RMS_Mean, Endur_Norm,
          PreRest_Mean_RMS, PostRest_Mean_RMS, Rest_RMS_Rate,
          Rest_CV_Rate, Rest_MF_Rate, Endur_prepost10_Rate,
          PreRest_Mean_CV, PostRest_Mean_CV, PreRest_WL,
          PostRest_WL, Rest_WL_Rate, Rapid_Peak_Var,
          Rapid_Raisetime_Var, Tonic_CV_Mean, Tonic_Norm_Var,
          Tonic_RMS_Var, Tonic_CV_Var, Endur_CV,
          Rapid_MF_List, Tonic_MF_List, Endur_Slope, Endur_MF,
          AA_FB_Simplicity, AA_FB_Full, AA_FB_Full_List);
    return;
}

QString Glazer_analyse::return_path()
{
    return m_storePath;
}

void Glazer_analyse::run()
{
    QString file_name;
    int stage=0;
    while(running)
    {
        if(glazer_time==150)
        {
           file_name = "preRest";
           stage = 1;
        }
        if(glazer_time==250)
        {
           file_name = "Rapid";
           stage = 2;
        }
        if(glazer_time==360)
        {
           stage = 3;
           file_name = "Tonic";
        }
        if(glazer_time==460)
        {
           stage = 4;
           file_name = "Endur";
        }
        if(glazer_time==520)
        {
           stage = 5;
           glazer_time=0;
           file_name = "postRest";
        }
        QVariantList dataList;
        int len = 0;
        double *x = nullptr;
QFile file(m_storePath+"/"+file_name+".txt");
if(stage!=0)
{


    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
            QString line = file.readLine();
            //qDebug()<<line<<endl;

            QStringList list = line.split(' ');
            //qDebug()<<list<<endl;
            QVariant var;
            //double var;
            for(const QString &data : list) {
                bool ok = false;
                var = data.toInt(&ok);
                if(ok) {
                    dataList <<var;
                    continue;
                }
                var = data.toDouble(&ok);
                if(ok) {
                    dataList <<var;
                    continue;
                }
            }
   len = dataList.length();
   x=new double [len];
   for(int i = 0;i<len ; i++)
   {
       x[i] =dataList.value(i).toDouble();
       //qDebug() << sizeof(x);
   }
}

       switch(stage)
       {
            case 0:
                break;
            case 1:
            {
                stage = 0;
                PreRest(x, len);
                file.close();
                if(running == false)
                    emit mid_stopped();
                //for (int idx0 = 0; idx0 < 32; idx0++) {
                //       qDebug()<< QString::number(PreRest_MF_data[idx0], 'f', 2);
                //   }
                delete  x;
                break;
            }
            case 2:
            {
                stage = 0;
                Rapid(x, len);
                file.close();
                if(running == false)
                    emit mid_stopped();
                delete  x;
                break;
            }
            case 3:
            {
                stage = 0;
                Tonic(x, len);
                file.close();
                if(running == false)
                    emit mid_stopped();
                delete  x;
                break;
            }
            case 4:
            {
                stage = 0;
                Endur(x, len);
                file.close();
                if(running == false)
                    emit mid_stopped();
                delete  x;
                break;
            }
            case 5:
            {
                stage = 0;
                PostRest(x, len);
                //QMessageBox::information(NULL,"OK","Glazer评估已完成，请查看报告!");
                file.close();
                glazer_done_state = true;
                emit glazer_done();
                //save_word();
                delete  x;
                break;
            }
       default:
           break;

       }
    }


}

void Glazer_analyse:: save_word()
{
        qDebug("file save start");
        WordEngine word;
        word.open(":/libs/template2021.dot");
        QString tag="label1_1";
        QString replaced = "2021";
        for (int idx0 = 0; idx0 < 32; idx0++) {
           for (int idx1 = 0; idx1 < 24; idx1++) {
             /* Set the value of the array element.
       Change this value to the value that the application requires. */
               tag="label"+QString(idx0)+"_"+QString(idx1);
               replaced = QString::number(AA_FB_Simplicity[idx0 + 32 * idx1], 'f', 2);
               word.replaceText(tag,replaced);
           }
         }
        word.save(m_storePath+"_glazer_report.doc");
        qDebug("file saved");
}

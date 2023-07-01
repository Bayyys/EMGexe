#ifndef GLAZER_ANALYSE_H
#define GLAZER_ANALYSE_H
#include <QString>
#include <QLibrary>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <qwidget.h>

typedef void (*Funprerest)(double*,int,double,double,double,double,double*,double*,double*,double*,int*); //定义函数指针，以备调用
typedef void (*Funprapid)(double*,int,double,double,double,double,double*,double*,double*,double*,double*);
typedef void (*FunTonic)(double*,double*,int,double,double,double,double,double*,double*,double*,double*,double*,double*,double*);
typedef void (*FunEndur)(double*,double*,int,double,double,double,double,double*,double*,double*,double*,double*,double*);
typedef void (*FunPostRest)(double*,double*,double*,double*,double*,int,double,double,double,double,double*,double*,double*,double*,int*,double*,double*,double*,double*);
typedef void (*Report)(double*,double*,double*,double*,double*,double*,
                       double*,double*,double*,double*,double*,double*,
                       double*,double*,double*,double*,double*,double*,
                       double*,double*,double*,double*,double*,double*,
                       double*,double*,double*,double*,
                       double*,double*,double*);

class Glazer_analyse:public QThread
{
    Q_OBJECT
public:
    explicit Glazer_analyse();
    //~Glazer_analyse();
    void PreRest(double*x,int len);
    void Rapid(double*x,int len);
    void Tonic(double*x,int len);
    void Endur(double*x,int len);
    void PostRest(double*x,int len);
    void save_report_data();
    double AA_FB_Simplicity[32*12];
    double AA_FB_Full[32*24];
    double AA_FB_Full_List[32*130];
    int glazer_time = 0;
    QString return_path();
    bool running;
    bool glazer_done_state =false;
    void run();
    void stopRun(){running =false;}
    void save_word();
signals:
    void glazer_done();
    void mid_stopped();
private:
    QString m_storePath;
    Funprerest RunPreRest;
    Funprapid RunRapid;
    FunTonic RunTonic;
    FunEndur RunEndur;
    FunPostRest RunPostRest;
    Report SaveReportData;



private:
    double smoothdegree =  29;
    double smoothlength =  33;
    double RMSlength = 1000;
    double fs = 1000;
    //PreRest_stage//
    double PreRest_Mean_RMS[32];
    double PreRest_Mean_CV[32];
    double PreRest_WL[32];
    double PreRest_MF_data[32];
    int PreRest_MF_size;
    //Rapid_stage//
    double Rapid_Peak_RMS_Mean[32];
    double Rapid_Peak_Var[32];
    double Rapid_Raisetime_Mean[32];
    double Rapid_Raisetime_Var[32];
    double Rapid_MF_List[32*5];
    //Tonic_stage//
    double Tonic_RMS_Mean[32];
    double Tonic_Norm_Mean[32];
    double Tonic_CV_Mean[32];
    double Tonic_Norm_Var[32];
    double Tonic_CV_Var[32];
    double Tonic_RMS_Var[32];
    double Tonic_MF_List[32*5];
    //Endur_stage//
    double Endur_RMS_Mean[32];
    double Endur_Norm[32];
    double Endur_CV[32];
    double Endur_prepost10_Rate[32];
    double Endur_MF[32*60];
    double Endur_Slope[32*60];
    //PostRest_stage//
    double PostRest_Mean_RMS[32];
    double PostRest_Mean_CV[32];
    double PostRest_WL[32];
    double PostRest_MF_data[32];
    double Rest_RMS_Rate[32];
    double Rest_CV_Rate[32];
    double Rest_MF_Rate[32];
    double Rest_WL_Rate[32];
    int MF_size;
};

#endif // GLAZER_ANALYSE_H

#ifndef GLAZER_H
#define GLAZER_H

#include <QWidget>
#include <QMainWindow>
#include <QVector>
#include <QThread>
#include <QProgressDialog>

const int higher_order = 36;
const int window_size = 200;
const int overlap = 30;

namespace Ui {
class Glazer;
}

class DataProcess;
class Glazer : public QMainWindow
{
    Q_OBJECT
public:
    explicit Glazer(QString filename,double sample_rate,QWidget *parent = 0);
    ~Glazer(); 
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void drawGlazer();
    void runGlazer();
    void dataProcessDone(double maxValue,int size_dataAfterRMS,QVector<double>* dataAfterRMS);
    void abortRun();
private:
    Ui::Glazer *ui;

    QString des_file;
    double sampleRate;
    unsigned int channel;
    bool draw_flag;
    double max_data;
    int size_data;

    QPointF* polyline;
    QThread *processThread;
    QVector<double>* dataDraw;
    DataProcess *process;
    QProgressDialog *progressDialog;
};


class DataProcess:public QObject
{
    Q_OBJECT
public:
    DataProcess(QString filename,double sample_rate, unsigned int channelNumber,Glazer *glazer_ui);

    QVector<double> dataAfterRMS;
    double maxValue;
    int size_dataAfterRMS;
public slots:
    void runProcess();
signals:
    void resultReady(double maxValue,int size_dataAfterRMS,QVector<double>* dataAfterRMS);
private:
    QString des_file;
    double sampleRate;
    unsigned int channel;

    Glazer* parent_ui;
};

#endif // GLAZER_H

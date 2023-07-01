#ifndef FFTSET_H
#define FFTSET_H

#include <QDialog>

namespace Ui {
class FFTSet;
}

class FFTSet : public QDialog
{
    Q_OBJECT

public:
    explicit FFTSet(bool self_control,double xmin,double xmax,double ymin,double ymax,QWidget *parent = 0);
    ~FFTSet();

    bool selfcontrol;
signals:
    void changeFFtWidget(bool self_control,double xmin,double xmax,double ymin,double ymax);
private slots:
    void changeSelfControl();
    void changeFFTSet();

private:
    Ui::FFTSet *ui;
};

#endif // FFTSET_H

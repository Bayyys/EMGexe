#ifndef STFT_H
#define STFT_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include "sp++/include/wft.h"
#include "sp++/include/vectormath.h"
#include "sp++/include/timing.h"
#include "sp++/include/window.h"

const int eeg_order = 8;

namespace Ui {
class STFT;
}
using namespace splab;
using namespace std;

class STFT : public QMainWindow
{
    Q_OBJECT

public:
    explicit STFT(QWidget *parent = 0);
    ~STFT();

private:
    Ui::STFT *ui;

    QString filePath;
    double sampleRate;
    unsigned int window_size;
    unsigned int overlap;
    unsigned int channel;
    Vector<double> *data;
    Matrix<double> abs_result;


    void decodeFile(unsigned int channel_number);
    void dostft();
    void drawSTFT(int nx, int ny);

private slots:
    void openFileDialog();
    void run_m();
};

#endif // STFT_H

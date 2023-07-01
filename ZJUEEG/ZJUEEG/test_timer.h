#ifndef TEST_TIMER_H
#define TEST_TIMER_H

#include <QMainWindow>

namespace Ui {
class test_timer;
}

class test_timer : public QMainWindow
{
    Q_OBJECT

public:
    explicit test_timer(QWidget *parent = nullptr);
    ~test_timer();

private slots:
    void on_pushButton_clicked();
    void torest();

private:
    Ui::test_timer *ui;
    int count=0;
};

#endif // TEST_TIMER_H

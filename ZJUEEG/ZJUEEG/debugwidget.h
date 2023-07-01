#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QMainWindow>
#include <QQueue>
#include <QTimer>
#include <QReadWriteLock>

extern QReadWriteLock lock_debug_msg_queue;

namespace Ui {
class DebugWidget;
}

class DebugWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWidget(QQueue<QByteArray>& _msg_queue,QWidget *parent = nullptr);
    ~DebugWidget();
protected:
    void closeEvent(QCloseEvent*);
signals:
    void signal_debug_widget_close();
private:
    Ui::DebugWidget *ui;
    QQueue<QByteArray>& msg_queue;
    QTimer *timer;
private slots:
    void slot_show_message();
    void slot_clear_widget();
};

#endif // DEBUGWIDGET_H

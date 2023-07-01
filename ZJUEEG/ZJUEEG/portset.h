#ifndef PORTSET_H
#define PORTSET_H

#include <QDialog>
#include <QSerialPort>
#include <QSettings>



namespace Ui {
class PortSet;
}

class PortSet : public QDialog
{
    Q_OBJECT

public:

    explicit PortSet(QVector<QString> &port_name, QSerialPort *port, QWidget *parent = 0);
    ~PortSet();
signals:
    void portSetDone();
private slots:
    void update_arg();
    void updateIniFile();
private:
    Ui::PortSet *ui;
    QSerialPort *serial_port;
//    QString selected_port_name;
};

#endif // PORTSET_H

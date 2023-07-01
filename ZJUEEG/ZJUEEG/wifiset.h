#ifndef WIFISET_H
#define WIFISET_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class WifiSet;
}

class WifiSet : public QDialog
{
    Q_OBJECT

public:
    explicit WifiSet(QWidget *parent = nullptr);
    ~WifiSet();
signals:
    void wifi_arg_change(QString ssid, QString ip, QString port, QString password);
private:
    Ui::WifiSet *ui;
private slots:
    void update_arg();
};

#endif // WIFISET_H

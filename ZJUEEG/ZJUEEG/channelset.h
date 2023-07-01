#ifndef CHANNELSET_H
#define CHANNELSET_H

#include <QDialog>
#include <QVector>
#include <QCheckBox>

namespace Ui {
class ChannelSet;
}

class ChannelSet : public QDialog
{
    Q_OBJECT

public:
    explicit ChannelSet(QVector<QCheckBox *> &checkbox, int c_Number,QWidget *parent = 0);
    ~ChannelSet();

private slots:
    void chooseAll();
    void chooseNone();
    void changeChannelSet();

private:
    Ui::ChannelSet *ui;

    QVector<QCheckBox*> bu;
    QVector<QCheckBox *> &des_obj;

    int channelNumber;
};

#endif // CHANNELSET_H

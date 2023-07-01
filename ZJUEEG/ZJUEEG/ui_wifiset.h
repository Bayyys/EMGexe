/********************************************************************************
** Form generated from reading UI file 'wifiset.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIFISET_H
#define UI_WIFISET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WifiSet
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *ssid_lineEdit;
    QLineEdit *port_lineEdit;
    QLineEdit *ip_lineEdit;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *password_lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WifiSet)
    {
        if (WifiSet->objectName().isEmpty())
            WifiSet->setObjectName(QString::fromUtf8("WifiSet"));
        WifiSet->resize(547, 353);
        verticalLayout = new QVBoxLayout(WifiSet);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(WifiSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(WifiSet);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        ssid_lineEdit = new QLineEdit(WifiSet);
        ssid_lineEdit->setObjectName(QString::fromUtf8("ssid_lineEdit"));

        gridLayout->addWidget(ssid_lineEdit, 0, 1, 1, 1);

        port_lineEdit = new QLineEdit(WifiSet);
        port_lineEdit->setObjectName(QString::fromUtf8("port_lineEdit"));

        gridLayout->addWidget(port_lineEdit, 3, 1, 1, 1);

        ip_lineEdit = new QLineEdit(WifiSet);
        ip_lineEdit->setObjectName(QString::fromUtf8("ip_lineEdit"));

        gridLayout->addWidget(ip_lineEdit, 2, 1, 1, 1);

        label = new QLabel(WifiSet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFocusPolicy(Qt::NoFocus);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(WifiSet);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        password_lineEdit = new QLineEdit(WifiSet);
        password_lineEdit->setObjectName(QString::fromUtf8("password_lineEdit"));

        gridLayout->addWidget(password_lineEdit, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);

        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(WifiSet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(WifiSet);
        QObject::connect(buttonBox, SIGNAL(accepted()), WifiSet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WifiSet, SLOT(reject()));

        QMetaObject::connectSlotsByName(WifiSet);
    } // setupUi

    void retranslateUi(QDialog *WifiSet)
    {
        WifiSet->setWindowTitle(QCoreApplication::translate("WifiSet", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("WifiSet", "IP", nullptr));
        label_3->setText(QCoreApplication::translate("WifiSet", "PORT", nullptr));
        ssid_lineEdit->setText(QCoreApplication::translate("WifiSet", "OpenBCI", nullptr));
        label->setText(QCoreApplication::translate("WifiSet", "SSID", nullptr));
        label_4->setText(QCoreApplication::translate("WifiSet", "PassWord", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WifiSet: public Ui_WifiSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIFISET_H

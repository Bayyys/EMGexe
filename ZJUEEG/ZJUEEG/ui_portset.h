/********************************************************************************
** Form generated from reading UI file 'portset.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTSET_H
#define UI_PORTSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PortSet
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *port_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *bandrate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *data_bit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *stop_bit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *flow_control;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PortSet)
    {
        if (PortSet->objectName().isEmpty())
            PortSet->setObjectName(QString::fromUtf8("PortSet"));
        PortSet->resize(412, 400);
        verticalLayout_2 = new QVBoxLayout(PortSet);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(PortSet);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        port_name = new QComboBox(PortSet);
        port_name->setObjectName(QString::fromUtf8("port_name"));

        horizontalLayout->addWidget(port_name);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(PortSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        bandrate = new QLineEdit(PortSet);
        bandrate->setObjectName(QString::fromUtf8("bandrate"));

        horizontalLayout_2->addWidget(bandrate);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(PortSet);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        data_bit = new QComboBox(PortSet);
        data_bit->addItem(QString());
        data_bit->addItem(QString());
        data_bit->addItem(QString());
        data_bit->addItem(QString());
        data_bit->setObjectName(QString::fromUtf8("data_bit"));

        horizontalLayout_3->addWidget(data_bit);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(PortSet);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        stop_bit = new QComboBox(PortSet);
        stop_bit->addItem(QString());
        stop_bit->addItem(QString());
        stop_bit->setObjectName(QString::fromUtf8("stop_bit"));

        horizontalLayout_4->addWidget(stop_bit);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(PortSet);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        flow_control = new QComboBox(PortSet);
        flow_control->addItem(QString());
        flow_control->setObjectName(QString::fromUtf8("flow_control"));

        horizontalLayout_5->addWidget(flow_control);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_5);

        buttonBox = new QDialogButtonBox(PortSet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);
        verticalLayout_2->setStretch(4, 1);
        verticalLayout_2->setStretch(5, 1);

        retranslateUi(PortSet);
        QObject::connect(buttonBox, SIGNAL(accepted()), PortSet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PortSet, SLOT(reject()));

        QMetaObject::connectSlotsByName(PortSet);
    } // setupUi

    void retranslateUi(QDialog *PortSet)
    {
        PortSet->setWindowTitle(QCoreApplication::translate("PortSet", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("PortSet", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("PortSet", "\346\263\242\347\211\271\347\216\207", nullptr));
        bandrate->setText(QCoreApplication::translate("PortSet", "2304000", nullptr));
        label_3->setText(QCoreApplication::translate("PortSet", "\346\225\260\346\215\256\344\275\215", nullptr));
        data_bit->setItemText(0, QCoreApplication::translate("PortSet", "8", nullptr));
        data_bit->setItemText(1, QCoreApplication::translate("PortSet", "7", nullptr));
        data_bit->setItemText(2, QCoreApplication::translate("PortSet", "6", nullptr));
        data_bit->setItemText(3, QCoreApplication::translate("PortSet", "5", nullptr));

        label_4->setText(QCoreApplication::translate("PortSet", "\345\201\234\346\255\242\344\275\215", nullptr));
        stop_bit->setItemText(0, QCoreApplication::translate("PortSet", "1", nullptr));
        stop_bit->setItemText(1, QCoreApplication::translate("PortSet", "2", nullptr));

        label_5->setText(QCoreApplication::translate("PortSet", "\346\265\201\346\216\247\345\210\266", nullptr));
        flow_control->setItemText(0, QCoreApplication::translate("PortSet", "\346\227\240", nullptr));

    } // retranslateUi

};

namespace Ui {
    class PortSet: public Ui_PortSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTSET_H

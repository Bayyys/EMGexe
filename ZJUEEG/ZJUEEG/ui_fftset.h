/********************************************************************************
** Form generated from reading UI file 'fftset.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFTSET_H
#define UI_FFTSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FFTSet
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *selfControl;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Xmax;
    QLabel *label_2;
    QLineEdit *Xmin;
    QLabel *label_3;
    QLineEdit *Ymax;
    QLabel *label_4;
    QLineEdit *Ymin;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FFTSet)
    {
        if (FFTSet->objectName().isEmpty())
            FFTSet->setObjectName(QString::fromUtf8("FFTSet"));
        FFTSet->resize(535, 133);
        verticalLayout = new QVBoxLayout(FFTSet);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        selfControl = new QCheckBox(FFTSet);
        selfControl->setObjectName(QString::fromUtf8("selfControl"));

        verticalLayout->addWidget(selfControl);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FFTSet);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        Xmax = new QLineEdit(FFTSet);
        Xmax->setObjectName(QString::fromUtf8("Xmax"));
        Xmax->setEnabled(false);

        horizontalLayout->addWidget(Xmax);

        label_2 = new QLabel(FFTSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        Xmin = new QLineEdit(FFTSet);
        Xmin->setObjectName(QString::fromUtf8("Xmin"));
        Xmin->setEnabled(false);

        horizontalLayout->addWidget(Xmin);

        label_3 = new QLabel(FFTSet);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        Ymax = new QLineEdit(FFTSet);
        Ymax->setObjectName(QString::fromUtf8("Ymax"));
        Ymax->setEnabled(false);

        horizontalLayout->addWidget(Ymax);

        label_4 = new QLabel(FFTSet);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        Ymin = new QLineEdit(FFTSet);
        Ymin->setObjectName(QString::fromUtf8("Ymin"));
        Ymin->setEnabled(false);

        horizontalLayout->addWidget(Ymin);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(FFTSet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FFTSet);
        QObject::connect(buttonBox, SIGNAL(accepted()), FFTSet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FFTSet, SLOT(reject()));
        QObject::connect(selfControl, SIGNAL(clicked()), FFTSet, SLOT(changeSelfControl()));

        QMetaObject::connectSlotsByName(FFTSet);
    } // setupUi

    void retranslateUi(QDialog *FFTSet)
    {
        FFTSet->setWindowTitle(QCoreApplication::translate("FFTSet", "Dialog", nullptr));
        selfControl->setText(QCoreApplication::translate("FFTSet", "\350\207\252\345\212\250\350\260\203\350\212\202\345\235\220\346\240\207\346\230\276\347\244\272\350\214\203\345\233\264", nullptr));
        label->setText(QCoreApplication::translate("FFTSet", "Xmax", nullptr));
        label_2->setText(QCoreApplication::translate("FFTSet", "Xmin", nullptr));
        label_3->setText(QCoreApplication::translate("FFTSet", "Ymax", nullptr));
        label_4->setText(QCoreApplication::translate("FFTSet", "Ymin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FFTSet: public Ui_FFTSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFTSET_H

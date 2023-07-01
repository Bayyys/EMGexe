/********************************************************************************
** Form generated from reading UI file 'stft.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STFT_H
#define UI_STFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot/qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_STFT
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *channelChoose_Combo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *sampleRate_Edit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *win_len_Edit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *overlap_Edit;
    QPushButton *run_Button;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *STFT)
    {
        if (STFT->objectName().isEmpty())
            STFT->setObjectName(QString::fromUtf8("STFT"));
        STFT->resize(1015, 673);
        centralwidget = new QWidget(STFT);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout_2->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        channelChoose_Combo = new QComboBox(centralwidget);
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->addItem(QString());
        channelChoose_Combo->setObjectName(QString::fromUtf8("channelChoose_Combo"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(channelChoose_Combo->sizePolicy().hasHeightForWidth());
        channelChoose_Combo->setSizePolicy(sizePolicy);
        channelChoose_Combo->setMinimumSize(QSize(45, 25));
        channelChoose_Combo->setMaximumSize(QSize(45, 25));

        horizontalLayout->addWidget(channelChoose_Combo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        sampleRate_Edit = new QLineEdit(centralwidget);
        sampleRate_Edit->setObjectName(QString::fromUtf8("sampleRate_Edit"));

        horizontalLayout_3->addWidget(sampleRate_Edit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        win_len_Edit = new QLineEdit(centralwidget);
        win_len_Edit->setObjectName(QString::fromUtf8("win_len_Edit"));

        horizontalLayout_5->addWidget(win_len_Edit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        overlap_Edit = new QLineEdit(centralwidget);
        overlap_Edit->setObjectName(QString::fromUtf8("overlap_Edit"));

        horizontalLayout_4->addWidget(overlap_Edit);


        verticalLayout->addLayout(horizontalLayout_4);

        run_Button = new QPushButton(centralwidget);
        run_Button->setObjectName(QString::fromUtf8("run_Button"));

        verticalLayout->addWidget(run_Button);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 9);
        horizontalLayout_2->setStretch(1, 1);
        STFT->setCentralWidget(centralwidget);
        menubar = new QMenuBar(STFT);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1015, 25));
        STFT->setMenuBar(menubar);
        statusbar = new QStatusBar(STFT);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        STFT->setStatusBar(statusbar);

        retranslateUi(STFT);
        QObject::connect(run_Button, SIGNAL(clicked()), STFT, SLOT(run_m()));
        QObject::connect(pushButton, SIGNAL(clicked()), STFT, SLOT(openFileDialog()));

        QMetaObject::connectSlotsByName(STFT);
    } // setupUi

    void retranslateUi(QMainWindow *STFT)
    {
        STFT->setWindowTitle(QCoreApplication::translate("STFT", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("STFT", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("STFT", "\351\200\232\351\201\223", nullptr));
        channelChoose_Combo->setItemText(0, QCoreApplication::translate("STFT", "1", nullptr));
        channelChoose_Combo->setItemText(1, QCoreApplication::translate("STFT", "2", nullptr));
        channelChoose_Combo->setItemText(2, QCoreApplication::translate("STFT", "3", nullptr));
        channelChoose_Combo->setItemText(3, QCoreApplication::translate("STFT", "4", nullptr));
        channelChoose_Combo->setItemText(4, QCoreApplication::translate("STFT", "5", nullptr));
        channelChoose_Combo->setItemText(5, QCoreApplication::translate("STFT", "6", nullptr));
        channelChoose_Combo->setItemText(6, QCoreApplication::translate("STFT", "7", nullptr));
        channelChoose_Combo->setItemText(7, QCoreApplication::translate("STFT", "8", nullptr));
        channelChoose_Combo->setItemText(8, QCoreApplication::translate("STFT", "9", nullptr));
        channelChoose_Combo->setItemText(9, QCoreApplication::translate("STFT", "10", nullptr));
        channelChoose_Combo->setItemText(10, QCoreApplication::translate("STFT", "11", nullptr));
        channelChoose_Combo->setItemText(11, QCoreApplication::translate("STFT", "12", nullptr));
        channelChoose_Combo->setItemText(12, QCoreApplication::translate("STFT", "13", nullptr));
        channelChoose_Combo->setItemText(13, QCoreApplication::translate("STFT", "14", nullptr));
        channelChoose_Combo->setItemText(14, QCoreApplication::translate("STFT", "15", nullptr));
        channelChoose_Combo->setItemText(15, QCoreApplication::translate("STFT", "16", nullptr));
        channelChoose_Combo->setItemText(16, QCoreApplication::translate("STFT", "17", nullptr));
        channelChoose_Combo->setItemText(17, QCoreApplication::translate("STFT", "18", nullptr));
        channelChoose_Combo->setItemText(18, QCoreApplication::translate("STFT", "19", nullptr));
        channelChoose_Combo->setItemText(19, QCoreApplication::translate("STFT", "20", nullptr));
        channelChoose_Combo->setItemText(20, QCoreApplication::translate("STFT", "21", nullptr));
        channelChoose_Combo->setItemText(21, QCoreApplication::translate("STFT", "22", nullptr));
        channelChoose_Combo->setItemText(22, QCoreApplication::translate("STFT", "23", nullptr));
        channelChoose_Combo->setItemText(23, QCoreApplication::translate("STFT", "24", nullptr));
        channelChoose_Combo->setItemText(24, QCoreApplication::translate("STFT", "25", nullptr));
        channelChoose_Combo->setItemText(25, QCoreApplication::translate("STFT", "26", nullptr));
        channelChoose_Combo->setItemText(26, QCoreApplication::translate("STFT", "27", nullptr));
        channelChoose_Combo->setItemText(27, QCoreApplication::translate("STFT", "28", nullptr));
        channelChoose_Combo->setItemText(28, QCoreApplication::translate("STFT", "29", nullptr));
        channelChoose_Combo->setItemText(29, QCoreApplication::translate("STFT", "30", nullptr));
        channelChoose_Combo->setItemText(30, QCoreApplication::translate("STFT", "31", nullptr));
        channelChoose_Combo->setItemText(31, QCoreApplication::translate("STFT", "32", nullptr));

        label_2->setText(QCoreApplication::translate("STFT", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("STFT", "\347\252\227\351\225\277", nullptr));
        label_3->setText(QCoreApplication::translate("STFT", "overlap", nullptr));
        run_Button->setText(QCoreApplication::translate("STFT", "\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class STFT: public Ui_STFT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STFT_H

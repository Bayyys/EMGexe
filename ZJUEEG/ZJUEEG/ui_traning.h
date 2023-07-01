/********************************************************************************
** Form generated from reading UI file 'traning.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANING_H
#define UI_TRANING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_traning
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QCheckBox *checkBox_ch1;
    QCheckBox *checkBox_ch2;
    QCheckBox *checkBox_ch3;
    QCheckBox *checkBox_ch4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *spinBox_pw_ch1;
    QSpinBox *spinBox_pw_ch2;
    QSpinBox *spinBox_pw_ch3;
    QSpinBox *spinBox_pw_ch4;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLineEdit *ele_time;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *rest_time;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *spinBox_freq;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QSpinBox *total_time;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_8;
    QTableView *tableView;
    QSpacerItem *verticalSpacer_5;
    QPushButton *ele_start;
    QPushButton *ele_stop;
    QLabel *label_9;
    QLabel *timer_label;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_ch1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_ch2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_ch3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_ch4;
    QLabel *ele_down;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *traning)
    {
        if (traning->objectName().isEmpty())
            traning->setObjectName(QString::fromUtf8("traning"));
        traning->resize(800, 600);
        centralwidget = new QWidget(traning);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 541, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        checkBox_ch1 = new QCheckBox(verticalLayoutWidget);
        checkBox_ch1->setObjectName(QString::fromUtf8("checkBox_ch1"));

        horizontalLayout_3->addWidget(checkBox_ch1);

        checkBox_ch2 = new QCheckBox(verticalLayoutWidget);
        checkBox_ch2->setObjectName(QString::fromUtf8("checkBox_ch2"));

        horizontalLayout_3->addWidget(checkBox_ch2);

        checkBox_ch3 = new QCheckBox(verticalLayoutWidget);
        checkBox_ch3->setObjectName(QString::fromUtf8("checkBox_ch3"));

        horizontalLayout_3->addWidget(checkBox_ch3);

        checkBox_ch4 = new QCheckBox(verticalLayoutWidget);
        checkBox_ch4->setObjectName(QString::fromUtf8("checkBox_ch4"));

        horizontalLayout_3->addWidget(checkBox_ch4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        spinBox_pw_ch1 = new QSpinBox(verticalLayoutWidget);
        spinBox_pw_ch1->setObjectName(QString::fromUtf8("spinBox_pw_ch1"));
        spinBox_pw_ch1->setMinimum(50);
        spinBox_pw_ch1->setMaximum(400);

        horizontalLayout_4->addWidget(spinBox_pw_ch1);

        spinBox_pw_ch2 = new QSpinBox(verticalLayoutWidget);
        spinBox_pw_ch2->setObjectName(QString::fromUtf8("spinBox_pw_ch2"));
        spinBox_pw_ch2->setMinimum(50);
        spinBox_pw_ch2->setMaximum(400);

        horizontalLayout_4->addWidget(spinBox_pw_ch2);

        spinBox_pw_ch3 = new QSpinBox(verticalLayoutWidget);
        spinBox_pw_ch3->setObjectName(QString::fromUtf8("spinBox_pw_ch3"));
        spinBox_pw_ch3->setMinimum(50);
        spinBox_pw_ch3->setMaximum(400);

        horizontalLayout_4->addWidget(spinBox_pw_ch3);

        spinBox_pw_ch4 = new QSpinBox(verticalLayoutWidget);
        spinBox_pw_ch4->setObjectName(QString::fromUtf8("spinBox_pw_ch4"));
        spinBox_pw_ch4->setMinimum(50);
        spinBox_pw_ch4->setMaximum(400);

        horizontalLayout_4->addWidget(spinBox_pw_ch4);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        ele_time = new QLineEdit(verticalLayoutWidget);
        ele_time->setObjectName(QString::fromUtf8("ele_time"));

        horizontalLayout_5->addWidget(ele_time);

        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_7 = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        rest_time = new QLineEdit(verticalLayoutWidget);
        rest_time->setObjectName(QString::fromUtf8("rest_time"));

        horizontalLayout_5->addWidget(rest_time);

        horizontalSpacer_3 = new QSpacerItem(116, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_4 = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        spinBox_freq = new QSpinBox(verticalLayoutWidget);
        spinBox_freq->setObjectName(QString::fromUtf8("spinBox_freq"));
        spinBox_freq->setMinimum(2);
        spinBox_freq->setMaximum(500);

        horizontalLayout_6->addWidget(spinBox_freq);

        horizontalSpacer_5 = new QSpacerItem(124, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        total_time = new QSpinBox(verticalLayoutWidget);
        total_time->setObjectName(QString::fromUtf8("total_time"));
        total_time->setMinimum(5);
        total_time->setMaximum(30);

        horizontalLayout_6->addWidget(total_time);

        horizontalSpacer_6 = new QSpacerItem(123, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer_6 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        ele_start = new QPushButton(centralwidget);
        ele_start->setObjectName(QString::fromUtf8("ele_start"));
        ele_start->setGeometry(QRect(640, 50, 101, 51));
        ele_stop = new QPushButton(centralwidget);
        ele_stop->setObjectName(QString::fromUtf8("ele_stop"));
        ele_stop->setGeometry(QRect(640, 130, 101, 51));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(590, 260, 54, 12));
        timer_label = new QLabel(centralwidget);
        timer_label->setObjectName(QString::fromUtf8("timer_label"));
        timer_label->setGeometry(QRect(660, 260, 54, 12));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(590, 290, 181, 251));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_10 = new QLabel(verticalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_7->addWidget(label_10);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_11 = new QLabel(verticalLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_8->addWidget(label_11);

        doubleSpinBox_ch1 = new QDoubleSpinBox(verticalLayoutWidget_2);
        doubleSpinBox_ch1->setObjectName(QString::fromUtf8("doubleSpinBox_ch1"));
        doubleSpinBox_ch1->setDecimals(1);
        doubleSpinBox_ch1->setSingleStep(0.200000000000000);

        horizontalLayout_8->addWidget(doubleSpinBox_ch1);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_12 = new QLabel(verticalLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_9->addWidget(label_12);

        doubleSpinBox_ch2 = new QDoubleSpinBox(verticalLayoutWidget_2);
        doubleSpinBox_ch2->setObjectName(QString::fromUtf8("doubleSpinBox_ch2"));
        doubleSpinBox_ch2->setDecimals(1);
        doubleSpinBox_ch2->setSingleStep(0.200000000000000);

        horizontalLayout_9->addWidget(doubleSpinBox_ch2);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_13 = new QLabel(verticalLayoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_10->addWidget(label_13);

        doubleSpinBox_ch3 = new QDoubleSpinBox(verticalLayoutWidget_2);
        doubleSpinBox_ch3->setObjectName(QString::fromUtf8("doubleSpinBox_ch3"));
        doubleSpinBox_ch3->setDecimals(1);
        doubleSpinBox_ch3->setSingleStep(0.200000000000000);

        horizontalLayout_10->addWidget(doubleSpinBox_ch3);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_14 = new QLabel(verticalLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_11->addWidget(label_14);

        doubleSpinBox_ch4 = new QDoubleSpinBox(verticalLayoutWidget_2);
        doubleSpinBox_ch4->setObjectName(QString::fromUtf8("doubleSpinBox_ch4"));
        doubleSpinBox_ch4->setDecimals(1);
        doubleSpinBox_ch4->setMaximum(100.000000000000000);
        doubleSpinBox_ch4->setSingleStep(0.200000000000000);

        horizontalLayout_11->addWidget(doubleSpinBox_ch4);


        verticalLayout_2->addLayout(horizontalLayout_11);

        ele_down = new QLabel(centralwidget);
        ele_down->setObjectName(QString::fromUtf8("ele_down"));
        ele_down->setGeometry(QRect(590, 210, 54, 12));
        traning->setCentralWidget(centralwidget);
        menubar = new QMenuBar(traning);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        traning->setMenuBar(menubar);
        statusbar = new QStatusBar(traning);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        traning->setStatusBar(statusbar);

        retranslateUi(traning);

        QMetaObject::connectSlotsByName(traning);
    } // setupUi

    void retranslateUi(QMainWindow *traning)
    {
        traning->setWindowTitle(QCoreApplication::translate("traning", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("traning", "\347\224\265\345\210\272\346\277\200\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("traning", "\345\210\272\346\277\200\351\200\232\351\201\223\357\274\232", nullptr));
        checkBox_ch1->setText(QCoreApplication::translate("traning", "1", nullptr));
        checkBox_ch2->setText(QCoreApplication::translate("traning", "2", nullptr));
        checkBox_ch3->setText(QCoreApplication::translate("traning", "3", nullptr));
        checkBox_ch4->setText(QCoreApplication::translate("traning", "4", nullptr));
        label_3->setText(QCoreApplication::translate("traning", "\350\204\211\345\206\262\345\256\275\345\272\246(us)\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("traning", "\345\210\272\346\277\200\346\227\266\351\227\264(s)\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("traning", "\344\274\221\346\201\257\346\227\266\351\227\264(s)\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("traning", "\345\210\272\346\277\200\351\242\221\347\216\207(Hz)\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("traning", "\346\262\273\347\226\227\346\227\266\351\225\277(min)\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("traning", "\345\216\206\345\217\262\350\207\252\345\256\232\344\271\211\346\226\271\346\241\210", nullptr));
        ele_start->setText(QCoreApplication::translate("traning", "\347\224\265\345\210\272\346\277\200\350\247\246\345\217\221", nullptr));
        ele_stop->setText(QCoreApplication::translate("traning", "\345\201\234\346\255\242", nullptr));
        label_9->setText(QCoreApplication::translate("traning", "\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        timer_label->setText(QString());
        label_10->setText(QCoreApplication::translate("traning", "\347\224\265\346\265\201\345\274\272\345\272\246\350\260\203\350\212\202(mA)\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("traning", "\351\200\232\351\201\2231\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("traning", "\351\200\232\351\201\2232\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("traning", "\351\200\232\351\201\2233\357\274\232", nullptr));
        label_14->setText(QCoreApplication::translate("traning", "\351\200\232\351\201\2234\357\274\232", nullptr));
        ele_down->setText(QCoreApplication::translate("traning", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class traning: public Ui_traning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANING_H

/********************************************************************************
** Form generated from reading UI file 'test_timer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_TIMER_H
#define UI_TEST_TIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test_timer
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *test_timer)
    {
        if (test_timer->objectName().isEmpty())
            test_timer->setObjectName(QString::fromUtf8("test_timer"));
        test_timer->resize(800, 600);
        centralwidget = new QWidget(test_timer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(310, 200, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        test_timer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(test_timer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        test_timer->setMenuBar(menubar);
        statusbar = new QStatusBar(test_timer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        test_timer->setStatusBar(statusbar);

        retranslateUi(test_timer);

        QMetaObject::connectSlotsByName(test_timer);
    } // setupUi

    void retranslateUi(QMainWindow *test_timer)
    {
        test_timer->setWindowTitle(QCoreApplication::translate("test_timer", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("test_timer", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("test_timer", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test_timer: public Ui_test_timer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_TIMER_H

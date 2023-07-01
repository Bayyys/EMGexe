/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QAction *action_connect;
    QAction *action_reconnect;
    QAction *action_linktest;
    QAction *action_reporttest;
    QWidget *centralwidget;
    QPushButton *eval;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(800, 600);
        action_connect = new QAction(login);
        action_connect->setObjectName(QString::fromUtf8("action_connect"));
        action_reconnect = new QAction(login);
        action_reconnect->setObjectName(QString::fromUtf8("action_reconnect"));
        action_linktest = new QAction(login);
        action_linktest->setObjectName(QString::fromUtf8("action_linktest"));
        action_reporttest = new QAction(login);
        action_reporttest->setObjectName(QString::fromUtf8("action_reporttest"));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        eval = new QPushButton(centralwidget);
        eval->setObjectName(QString::fromUtf8("eval"));
        eval->setGeometry(QRect(110, 220, 201, 121));
        QFont font;
        font.setPointSize(27);
        font.setBold(true);
        font.setWeight(75);
        eval->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 220, 201, 121));
        pushButton_2->setFont(font);
        login->setCentralWidget(centralwidget);
        menubar = new QMenuBar(login);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        login->setMenuBar(menubar);
        statusbar = new QStatusBar(login);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        login->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(action_connect);
        menu->addAction(action_reconnect);
        menu_2->addAction(action_linktest);
        menu_2->addAction(action_reporttest);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "MainWindow", nullptr));
        action_connect->setText(QCoreApplication::translate("login", "\350\277\236\346\216\245\344\270\262\345\217\243", nullptr));
#if QT_CONFIG(tooltip)
        action_connect->setToolTip(QCoreApplication::translate("login", "connect", nullptr));
#endif // QT_CONFIG(tooltip)
        action_reconnect->setText(QCoreApplication::translate("login", "\351\207\215\347\275\256\350\277\236\346\216\245", nullptr));
        action_linktest->setText(QCoreApplication::translate("login", "\345\212\250\346\200\201\345\272\223\351\223\276\346\216\245\346\265\213\350\257\225", nullptr));
#if QT_CONFIG(tooltip)
        action_linktest->setToolTip(QCoreApplication::translate("login", "linktest", nullptr));
#endif // QT_CONFIG(tooltip)
        action_reporttest->setText(QCoreApplication::translate("login", "\346\212\245\345\221\212\347\224\237\346\210\220\346\265\213\350\257\225", nullptr));
#if QT_CONFIG(tooltip)
        action_reporttest->setToolTip(QCoreApplication::translate("login", "reporttest", nullptr));
#endif // QT_CONFIG(tooltip)
        eval->setText(QCoreApplication::translate("login", "\350\257\204\344\274\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("login", "\350\256\255\347\273\203", nullptr));
        menu->setTitle(QCoreApplication::translate("login", "\350\277\236\346\216\245", nullptr));
        menu_2->setTitle(QCoreApplication::translate("login", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

/********************************************************************************
** Form generated from reading UI file 'debugwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGWIDGET_H
#define UI_DEBUGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugWidget
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_clear;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DebugWidget)
    {
        if (DebugWidget->objectName().isEmpty())
            DebugWidget->setObjectName(QString::fromUtf8("DebugWidget"));
        DebugWidget->resize(828, 600);
        centralwidget = new QWidget(DebugWidget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_clear = new QPushButton(centralwidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        verticalLayout_2->addWidget(pushButton_clear);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        verticalLayout_2->addLayout(verticalLayout);

        DebugWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DebugWidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 828, 26));
        DebugWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(DebugWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DebugWidget->setStatusBar(statusbar);

        retranslateUi(DebugWidget);
        QObject::connect(pushButton_clear, SIGNAL(clicked()), DebugWidget, SLOT(slot_clear_widget()));

        QMetaObject::connectSlotsByName(DebugWidget);
    } // setupUi

    void retranslateUi(QMainWindow *DebugWidget)
    {
        DebugWidget->setWindowTitle(QCoreApplication::translate("DebugWidget", "MainWindow", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("DebugWidget", "\346\270\205\345\261\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebugWidget: public Ui_DebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGWIDGET_H

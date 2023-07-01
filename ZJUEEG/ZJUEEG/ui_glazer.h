/********************************************************************************
** Form generated from reading UI file 'glazer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLAZER_H
#define UI_GLAZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Glazer
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QPushButton *runButtom;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Glazer)
    {
        if (Glazer->objectName().isEmpty())
            Glazer->setObjectName(QString::fromUtf8("Glazer"));
        Glazer->resize(948, 593);
        centralwidget = new QWidget(Glazer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        runButtom = new QPushButton(centralwidget);
        runButtom->setObjectName(QString::fromUtf8("runButtom"));

        verticalLayout->addWidget(runButtom);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 9);
        horizontalLayout->setStretch(2, 1);

        horizontalLayout_2->addLayout(horizontalLayout);

        Glazer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Glazer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 948, 25));
        Glazer->setMenuBar(menubar);
        statusbar = new QStatusBar(Glazer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Glazer->setStatusBar(statusbar);

        retranslateUi(Glazer);
        QObject::connect(runButtom, SIGNAL(clicked()), Glazer, SLOT(runGlazer()));

        QMetaObject::connectSlotsByName(Glazer);
    } // setupUi

    void retranslateUi(QMainWindow *Glazer)
    {
        Glazer->setWindowTitle(QCoreApplication::translate("Glazer", "MainWindow", nullptr));
        runButtom->setText(QCoreApplication::translate("Glazer", "\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Glazer: public Ui_Glazer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLAZER_H

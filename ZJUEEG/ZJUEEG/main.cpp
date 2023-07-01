#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test_timer.h"
#include <QLibrary>
#include "glazer_analyse.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    a.installNativeEventFilter(&w);
    w.show();


    return a.exec();


}

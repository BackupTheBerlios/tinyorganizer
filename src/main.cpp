#include "mainwindow.h"
#include "addevent.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();

//    AddEvent ad;
//    ad.show();
    return a.exec();
}

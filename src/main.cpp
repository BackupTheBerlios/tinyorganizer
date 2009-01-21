#include "mainwindow.h"
#include "addevent.h"

#include <QtGui>
#include <QApplication>

#include "main.h"

const QString APPNAME = "TinyOrganizer";
const QString APPVER = "0.0.9";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPNAME);
    a.setApplicationVersion(APPVER);
    MainWindow mw;
    mw.show();

//    AddEvent ad;
//    ad.show();
    return a.exec();
}

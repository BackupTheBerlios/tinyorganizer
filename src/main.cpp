#include "mainwindow.h"
#include "addevent.h"

#include <QtGui>
#include <QApplication>

const QString APPNAME = "TinyOrganizer";
const QString APPVENDOR = "TinyOrganizer Team";
const QString APPDOMAIN = "tinyorganizer.org";
const QString APPVER = "0.0.9";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(APPNAME);
    QCoreApplication::setApplicationVersion(APPVER);
    QCoreApplication::setOrganizationName(APPVENDOR);
    QCoreApplication::setOrganizationDomain(APPDOMAIN);
    MainWindow mw;
    mw.show();
    return a.exec();
}

#include "main.h"


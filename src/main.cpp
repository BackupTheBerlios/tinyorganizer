#include "mainwindow.h"
#include "addevent.h"

#include <QtGui>
#include <QApplication>

extern const QString APPNAME("TinyOrganizer");
extern const QString APPVENDOR("TinyOrganizer Team");
extern const QString APPDOMAIN("tinyorganizer.org");
extern const QString APPVER("0.0.9");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(APPNAME);
    QCoreApplication::setApplicationVersion(APPVER);
    QCoreApplication::setOrganizationName(APPVENDOR);
    QCoreApplication::setOrganizationDomain(APPDOMAIN);
    MainWindow mw;
//    mw.show();
    return a.exec();
}

#include "main.h"


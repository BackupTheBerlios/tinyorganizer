#include "launcher.h"
#include "mainwindow.h"

#include <QtGui>
#include <QApplication>

extern const QString APPNAME("TinyOrganizer");
extern const QString APPVENDOR("TinyOrganizer Team");
extern const QString APPDOMAIN("tinyorganizer.org");
extern const QString APPVER("0.0.9");
extern const QString APPWWW("http://www.tinyorganizer.org");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(APPNAME);
    QCoreApplication::setApplicationVersion(APPVER);
    QCoreApplication::setOrganizationName(APPVENDOR);
    QCoreApplication::setOrganizationDomain(APPDOMAIN);

//    MainWindow mw;
    Launcher l;
    l.start();

    return a.exec();
}

#include "main.h"


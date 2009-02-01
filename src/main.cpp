/*
 * main.cpp
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 2 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

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

    Launcher l;
    l.start();

    return a.exec();
}

#include "main.h"


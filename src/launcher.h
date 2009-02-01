/*
 * launcher.h
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

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QList>
#include <QString>
#include <QTranslator>

extern const QString TRANSLATORS_PATH;

class MainWindow;

class Launcher
{
public:
    Launcher();
    virtual ~Launcher();

    void start();

private:
    void setupTranslators();
    bool installTranslatorForLocaleSymbol(const QString & localeSymbol);

private:
    MainWindow * mMainWindow;
    QList<QTranslator*> mTranslators;
};

#endif // LAUNCHER_H

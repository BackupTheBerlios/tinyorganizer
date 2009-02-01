/*
 * launcher.cpp
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
#include "settingsmanager.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <QTranslator>

Launcher::Launcher():
        mMainWindow(0)
{

}

Launcher::~Launcher()
{
    foreach( QTranslator * t, mTranslators )
    {
        delete t;
    }
    mTranslators.clear();

    delete mMainWindow;
}

void Launcher::start()
{
    mMainWindow = new MainWindow;
    setupTranslators();
}

bool Launcher::installTranslatorForLocaleSymbol(const QString & localeSymbol)
{
    QString filename = QString(":/i18n/%1.qm").arg(localeSymbol);
    qDebug() << "installing translator for locale: " << localeSymbol << " from file " << filename;
    QTranslator * translator = new QTranslator;
    if( translator->load(filename) )
    {
        mTranslators.append(translator);
        QCoreApplication::installTranslator(translator);
        qDebug() << "load successful: " << localeSymbol << "[" << filename << "]";
        return true;
    }
    qDebug() << "load failed: " << localeSymbol << "[" << filename << "]";
    return false;
}

void Launcher::setupTranslators()
{
    qDebug() << "[setupTranslators]";
    bool installed = false;

    QLocale locale = QLocale::system();

    qDebug() << "system locale: " << locale.name();

    QTranslator * translator_en_EN = new QTranslator;
    bool loaded = translator_en_EN->load(":/i18n/en_EN.qm");
    qDebug() << "loading translator for en_EN: " << loaded;

    if( loaded )
    {
        qApp->installTranslator(translator_en_EN);
    }

    if( SettingsManager::getSingleton().containsValue("locale") )
    {
        QString localeSaved = SettingsManager::getSingleton().getValue("locale").value<QString>();
        qDebug() << "restoring saved locale: " << localeSaved;
        installed = installTranslatorForLocaleSymbol(localeSaved);
    }

    if( !installed )
    {
        installed = installTranslatorForLocaleSymbol(locale.name());
    }

    qDebug() << "~[setupTranslators]";
}


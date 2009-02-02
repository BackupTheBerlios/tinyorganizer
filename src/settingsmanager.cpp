/*
 *   settingsmanager.cpp
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

#include "settingsmanager.h"
#include "main.h"

#include <QDebug>

SettingsManager::SettingsManager()
{
    fillDefaultValues();
    fillCurrentValues();
}

SettingsManager::~SettingsManager()
{
    saveCurrentValues();
}

void SettingsManager::fillCurrentValues()
{
    qDebug() << "[fillCurrentValues]";
    QStringList list = mSettings.allKeys();
    for(int i=0; i<list.size(); ++i)
    {
        QString key = list[i];
        if( mSettings.contains(key) )
        {
            qDebug() << "loading: " << key << " --> " << mSettings.value(key).toString();
            mCurrentValues[key] = mSettings.value(key);
        }
    }
    qDebug() << "~[fillCurrentValues]";
}

void SettingsManager::saveCurrentValues()
{
    qDebug() << "[saveCurrentValues]";
    QStringList list = mCurrentValues.keys();

    for(int i=0; i<list.size(); ++i)
    {
        QString key = list[i];
        if( mCurrentValues.contains(key) )
        {
            qDebug() << "saving: " << key << " --> " << mCurrentValues[key].toString();
            mSettings.setValue(key, mCurrentValues[key]);
        }
    }
    qDebug() << "~[saveCurrentValues]";
}

bool SettingsManager::saveWindow(QWidget * window, const QString & title)
{
    qDebug() << "[saveWindow]";
    qDebug() << "saving window: " << window->windowTitle();
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->objectName();
    }

    setValue(windowTitle + "/position", window->pos());
    setValue(windowTitle + "/visible", window->isVisible());
    setValue(windowTitle + "/size", window->size());

    qDebug() << "end of saving window: " << window->windowTitle();

    qDebug() << "~[saveWindow]";
    return true;
}

bool SettingsManager::restoreWindow(QWidget * window, const QString & title) const
{
    qDebug() << "[restoreWindow]";
    qDebug() << "restoring window: " << window->windowTitle();
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->objectName();
    }

    if( containsValue(windowTitle + "/position") )
    {
        QVariant position = getValue(windowTitle + "/position");
        QPoint point = position.value<QPoint>();
        qDebug() << "x: " << point.x() << " y: " << point.y();
        window->move(point.x(), point.y());
    }

    if( containsValue(windowTitle + "/size") )
    {
        QVariant position = getValue(windowTitle + "/size");
        QSize size = position.value<QSize>();
        qDebug() << "width: " << size.width() << " height: " << size.height();
        window->resize(size);
    }

    if( containsValue(windowTitle + "/visible") )
    {
        QVariant visible = getValue(windowTitle + "/visible");
        window->setVisible(visible.value<bool>());
        qDebug() << "visible: " << visible.value<bool>();
    }

    qDebug() << "end of restoring window: " << window->windowTitle();

    qDebug() << "~[restoreWindow]";
    return true;
}

QVariant SettingsManager::getValue(const QString & key) const
{
    qDebug() << "[getValue] requesting for key: " << key;
    if( containsValue(key) )
    {
        return mCurrentValues[key];
    }
    else
    {
        if( mDefaultValues.contains(key) )
        {
            return mDefaultValues[key];
        }
        return QVariant();
    }
}

void SettingsManager::setValue(const QString & key, const QVariant & value)
{
    qDebug() << "[setValue]" << key << "-->" << value.toString();

    mCurrentValues[key] = value;

    qDebug() << "~[setValue]";
}

bool SettingsManager::containsValue(const QString & key) const
{
    return mCurrentValues.contains(key);
}

void SettingsManager::fillDefaultValues()
{
    qDebug() << "[fillDefaultValues]";

    mDefaultValues["MinimizeOnClose"] = QVariant(true);
    mDefaultValues["MinimizeToTray"] = QVariant(false);

    qDebug() << "~[fillDefaultValues]";
}

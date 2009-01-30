/*
 *   settingsmanager.h
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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "calendar-core/singleton.h"

#include <QMainWindow>
#include <QSettings>

class SettingsManager: public TinyOrganizer::Singleton<SettingsManager>
{
    friend class TinyOrganizer::Singleton<SettingsManager>;
public:
    bool saveWindow(QWidget * window, const QString & title = "");
    bool restoreWindow(QWidget * window, const QString & title = "") const;

    QVariant getValue(const QString & key) const;
    void setValue(const QString & key, const QVariant & value);
    bool containsValue(const QString & key) const;

private:
    SettingsManager();
    ~SettingsManager();
    SettingsManager(const SettingsManager &);
    SettingsManager & operator=(const SettingsManager &);

    void fillCurrentValues();
    void fillDefaultValues();
    void saveCurrentValues();

private:
    QSettings mSettings;
    QMap<QString, QVariant> mCurrentValues;
    QMap<QString, QVariant> mDefaultValues;
};

#endif // SETTINGSMANAGER_H

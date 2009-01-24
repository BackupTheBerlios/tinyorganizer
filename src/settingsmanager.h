#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "calendar-core/singleton.h"

#include <QMainWindow>
#include <QSettings>

class SettingsManager: public TinyOrganizer::Singleton<SettingsManager>
{
    friend class TinyOrganizer::Singleton<SettingsManager>;
public:
    bool saveWindow(QMainWindow * window, const QString & title = "");
    bool restoreWindow(QMainWindow * window, const QString & title = "") const;

    QVariant getValue(const QString & key) const;
    void setValue(const QString & key, const QVariant & value);

private:
    SettingsManager();
    ~SettingsManager();
    SettingsManager(const SettingsManager &);
    SettingsManager & operator=(const SettingsManager &);

    void fillDefaultValues();

private:
    QSettings mSettings;
    QMap<QString, QVariant> mDefaultValues;
};

#endif // SETTINGSMANAGER_H

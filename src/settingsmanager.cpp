#include "settingsmanager.h"

#include <QDebug>

SettingsManager::SettingsManager()
{
}

SettingsManager::~SettingsManager()
{
}

bool SettingsManager::saveWindow(QMainWindow * window, const QString & title)
{
    qDebug() << "saving window: " << window->windowTitle() << endl;
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->windowTitle();
    }

    mSettings.setValue(windowTitle + "/position", window->pos());
    mSettings.setValue(windowTitle + "/visible", window->isVisible());

    qDebug() << "end of saving window: " << window->windowTitle() << endl;

    return true;
}

bool SettingsManager::restoreWindow(QMainWindow * window, const QString & title)
{
    qDebug() << "restoring window: " << window->windowTitle() << endl;
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->windowTitle();
    }

    if( mSettings.contains(windowTitle + "/position") )
    {
        QVariant position = mSettings.value(windowTitle + "/position");
        QPoint point = position.value<QPoint>();
        qDebug() << "x: " << point.x() << " y: " << point.y() << endl;
        window->move(point.x(), point.y());
    }

    if( mSettings.contains(windowTitle + "/visible") )
    {
        QVariant visible = mSettings.value(windowTitle + "/visible");
        window->setVisible(visible.value<bool>());
    }

    qDebug() << "end of restoring window: " << window->windowTitle() << endl;

    return true;
}

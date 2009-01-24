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
    qDebug() << "saving window: " << window->windowTitle();
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->windowTitle();
    }

    mSettings.setValue(windowTitle + "/position", window->pos());
    mSettings.setValue(windowTitle + "/visible", window->isVisible());
    mSettings.setValue(windowTitle + "/size", window->size());

    qDebug() << "end of saving window: " << window->windowTitle();

    return true;
}

bool SettingsManager::restoreWindow(QMainWindow * window, const QString & title)
{
    qDebug() << "restoring window: " << window->windowTitle();
    QString windowTitle = title;

    if( title.size() == 0 )
    {
        windowTitle = window->windowTitle();
    }

    if( mSettings.contains(windowTitle + "/position") )
    {
        QVariant position = mSettings.value(windowTitle + "/position");
        QPoint point = position.value<QPoint>();
        qDebug() << "x: " << point.x() << " y: " << point.y();
        window->move(point.x(), point.y());
    }

    if( mSettings.contains(windowTitle + "/size") )
    {
        QVariant position = mSettings.value(windowTitle + "/size");
        QSize size = position.value<QSize>();
        qDebug() << "width: " << size.width() << " height: " << size.height();
        window->resize(size);
    }

    if( mSettings.contains(windowTitle + "/visible") )
    {
        QVariant visible = mSettings.value(windowTitle + "/visible");
        window->setVisible(visible.value<bool>());
        qDebug() << "visible: " << visible.value<bool>();
    }

    qDebug() << "end of restoring window: " << window->windowTitle();

    return true;
}

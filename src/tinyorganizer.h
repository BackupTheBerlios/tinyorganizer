#ifndef TINYORGANIZER_H
#define TINYORGANIZER_H

#include <QtGui/QMainWindow>
#include <QtGui/QSystemTrayIcon>
#include "ui_tinyorganizer.h"

class TinyOrganizer : public QMainWindow
{
    Q_OBJECT

public:
    TinyOrganizer(QWidget *parent = 0);
    ~TinyOrganizer();

public slots:
    void trayIconClicked(QSystemTrayIcon::ActivationReason);

private:
    Ui::TinyOrganizerClass ui;
    QSystemTrayIcon *trayIcon;
    QPoint position;
    void restoreWindowPosition();
    void saveWindowPosition();
    void setupTrayIcon();
};

#endif // TINYORGANIZER_H

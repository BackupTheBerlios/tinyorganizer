/*
 *   tinyorganizer.cpp
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
    void performActionSave();
    void performActionClose();
    void performActionAbout();

private:
	void connectSignals();

private:
    Ui::TinyOrganizerClass ui;
    QSystemTrayIcon *trayIcon;
    QPoint position;
    void restoreWindowPosition();
    void saveWindowPosition();
    void setupTrayIcon();
};

#endif // TINYORGANIZER_H

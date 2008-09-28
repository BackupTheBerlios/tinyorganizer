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

#include "tinyorganizer.h"
#include <QtCore/QDateTime>
#include <QDebug>


namespace TinyOrganizer
{

void TinyOrganizer::connectSignals()
{
	connect(ui.actionSave, SIGNAL(triggered()), SLOT(performActionSave()));
	connect(ui.actionClose, SIGNAL(triggered()), SLOT(performActionClose()));
	connect(ui.actionAbout, SIGNAL(triggered()), SLOT(performActionAbout()));
}

void TinyOrganizer::performActionSave()
{
}

void TinyOrganizer::performActionClose()
{
	qDebug() << "closing TinyOrganizer...";
	close();
}

void TinyOrganizer::performActionAbout()
{
}

void TinyOrganizer::setupTrayIcon()
{
    QIcon icon(":/gfx/icons/calendar.png");
    trayIcon->setIcon(icon);
    trayIcon->setVisible(true);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        		this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
}

TinyOrganizer::TinyOrganizer(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	trayIcon = new QSystemTrayIcon();
	setStatusBar(0);
    setupTrayIcon();
    connectSignals();
}

void TinyOrganizer::saveWindowPosition()
{
    position = pos();
}

void TinyOrganizer::restoreWindowPosition()
{
    move(position);
}

void TinyOrganizer::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
	if( reason == QSystemTrayIcon::Trigger)
	{
		if( isHidden() )
		{
			setVisible(true);
			restoreWindowPosition();
		}
		else
		{
			saveWindowPosition();
			setVisible(false);
		}
	}
	else if( reason == QSystemTrayIcon::Context )
	{
	}
}


TinyOrganizer::~TinyOrganizer()
{
	delete trayIcon;
}

}

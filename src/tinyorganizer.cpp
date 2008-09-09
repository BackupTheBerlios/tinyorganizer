#include "tinyorganizer.h"
#include <QtCore/QDateTime>


void TinyOrganizer::setupTrayIcon()
{
    QIcon icon(":/gfx/icons/calendar.png");
    trayIcon->setIcon(icon);
    trayIcon->setVisible(true);
}

TinyOrganizer::TinyOrganizer(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	trayIcon = new QSystemTrayIcon();
    setupTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    		this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
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

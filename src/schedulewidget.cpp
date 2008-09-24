/*
 *   schedulewidget.cpp
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

#include <QDebug>

#include "schedulewidget.h"
#include "addeventdialog.h"

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connectSignals();
}

ScheduleWidget::~ScheduleWidget()
{
}

void ScheduleWidget::connectSignals()
{
	connect(ui.buttonAddEvent, SIGNAL(clicked()), this, SLOT(performAddEvent()));
	connect(ui.buttonDeleteEvent, SIGNAL(clicked()), this, SLOT(performDeleteEvent()));
	connect(ui.tableEvents, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(eventActivated(QTableWidgetItem*)));
	connect(ui.calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(dateChanged(QDate)));
	connect(ui.calendarWidget, SIGNAL(currentPageChanged(int,int)), this, SLOT(calendarPageChanged(int,int)));
}

void ScheduleWidget::performAddEvent()
{
	AddEventDialog aed(this);
	aed.setCurrentDate(ui.calendarWidget->selectedDate());
	if( aed.exec() == QDialog::Accepted )
	{

		// colect data from dialog to create an event
	}
}

void ScheduleWidget::performDeleteEvent()
{
	if( ui.tableEvents->selectedItems().count() > 0 )
	{

	}
}

void ScheduleWidget::eventActivated(QTableWidgetItem*)
{
	ui.buttonDeleteEvent->setEnabled(true);
}

void ScheduleWidget::dateChanged(QDate date)
{
	qDebug() << "dateChanged: " << date.toString();
	refreshEventListForDate(date);
}

void ScheduleWidget::calendarPageChanged(int year, int month)
{
	refreshCalendarWidget(year, month);
}

void ScheduleWidget::refreshCalendarWidget(int, int)
{

}

void ScheduleWidget::refreshEventListForDate(QDate)
{

}

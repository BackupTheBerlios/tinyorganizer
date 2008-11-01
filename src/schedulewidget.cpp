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
#include <QHeaderView>
#include <QTextCharFormat>

#include "schedulewidget.h"
#include "addeventdialog.h"

#include "calendar-core/eventmanager.h"
#include "calendar-core/event.h"

namespace TinyOrganizer
{

void ScheduleWidget::setupTableEvents()
{
    ui.tableEvents->setModel(&mEventsModel);
    ui.tableEvents->resizeColumnsToContents();

    ui.tableEvents->verticalHeader()->hide();
}

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connectSignals();
    setupTableEvents();

    setupTableForToday();
}

void ScheduleWidget::setupTableForToday()
{
	QDate currentDate(QDate::currentDate());
	dateChanged(currentDate);
	calendarPageChanged(currentDate.year(), currentDate.month());
}

ScheduleWidget::~ScheduleWidget()
{
	EventManager::getSingleton().saveEventsToFile("/home/darek/events.xml");
}

void ScheduleWidget::connectSignals()
{
	connect(ui.buttonAddEvent, SIGNAL(clicked()), this, SLOT(performAddEvent()));
	connect(ui.buttonDeleteEvent, SIGNAL(clicked()), this, SLOT(performDeleteEvent()));
	connect(ui.tableEvents, SIGNAL(clicked(const QModelIndex &)), this, SLOT(eventActivated(const QModelIndex &)));
	connect(ui.calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(dateChanged(QDate)));
	connect(ui.calendarWidget, SIGNAL(currentPageChanged(int,int)), this, SLOT(calendarPageChanged(int,int)));
}

void ScheduleWidget::performAddEvent()
{
	AddEventDialog aed(this);
	QDateTime currentDate;
	currentDate.setDate(ui.calendarWidget->selectedDate());
	currentDate.setTime(QDateTime::currentDateTime().time());
	aed.setCurrentDate(currentDate);
	if( aed.exec() == QDialog::Accepted )
	{
		// colect data from dialog to create an event
		QDateTime startDate;
		QDateTime endDate;
		Event * e = new Event;
		e->setStartDateTime(aed.startDate());
		e->setEndDateTime(aed.endDate());
		e->setSummary(aed.summary());
		e->setLocation(aed.location());

		if( aed.allDayEvent() )
		{
			e->setAllDay(true);
		}

		if( aed.recurrenceType() != Recurrence::None )
		{
			QDateTime recurrenceUntil(aed.repeatUntil());
			Recurrence recurrence;
			recurrence.setRecurrenceType(aed.recurrenceType());
			recurrence.setUntilDate(recurrenceUntil);
			e->setRecurrence(recurrence);
		}

		EventManager::getSingleton().addEvent(e);

		// refresh calendar
		refreshCalendarWidget(ui.calendarWidget->yearShown(), ui.calendarWidget->monthShown());
		// refresh event list
		refreshEventListForDate(ui.calendarWidget->selectedDate());
	}
}

void ScheduleWidget::performDeleteEvent()
{
	if( ui.tableEvents->selectionModel()->selectedRows().count() )
	{

	}
}

void ScheduleWidget::eventActivated(const QModelIndex & modelIndex)
{
	modelIndex.column();
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

void ScheduleWidget::refreshCalendarWidget(int year, int month)
{
	qDebug() << "calendar page changed: " << year << "/" << month;
	QDate date(year, month, 1);

	QList<Event*> events = EventManager::getSingleton().getEventsForMonth(year, month);

	QTextCharFormat charFormat;
	charFormat.setFontWeight(QFont::Bold);
	charFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);

	for(int i=1; i<=date.daysInMonth(); ++i)
	{
		date.setDate(year, month, i);
		QList<Event*>::iterator it = events.begin();
		QList<Event*>::iterator end = events.end();
		while( it != end )
		{
			if( (*it)->recursOn(date) )
			{
				ui.calendarWidget->setDateTextFormat(date, charFormat);
			}
			++it;
		}
	}
}

void ScheduleWidget::refreshEventListForDate(QDate date)
{
	mEventsModel.setEvents(EventManager::getSingleton().getEventsForDate(date));
	ui.tableEvents->resizeColumnsToContents();
    ui.tableEvents->horizontalHeader()->setStretchLastSection(true);
}

}

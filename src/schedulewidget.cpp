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

#include "calendar-core/eventmanager.h"
#include "calendar-core/event.h"

#include "schedulewidget.h"
#include "addevent.h"
#include "ui_schedulewidget.h"

#include <algorithm>

#include <QCalendarWidget>
#include <QtGui/QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QHeaderView>
#include <QtGui/QTableView>
#include <QTextCharFormat>

using namespace TinyOrganizer;

ScheduleWidget::ScheduleWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ScheduleWidget)
{
    m_ui->setupUi(this);

    EventManager::getSingleton().loadEventsFromHome();

    setupTableEvents();

    setupTableForToday();
}

ScheduleWidget::~ScheduleWidget()
{
    delete m_ui;
    qDebug() << EventManager::getSingleton().getEventsFilePath() << endl;
    EventManager::getSingleton().saveEventsToHome();
}

void ScheduleWidget::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        m_ui->tableEvents->resizeColumnsToContents();
        break;
    default:
        break;
    }
}

void ScheduleWidget::on_calendarWidget_customContextMenuRequested(QPoint pos)
{
    QDate selectedDate = m_ui->calendarWidget->selectedDate();
    QMenu menu;
    menu.setTitle(selectedDate.toString());
    menu.addAction(m_ui->actionAddEvent);
    if( EventManager::getSingleton().getEventsForDate(selectedDate).size() > 0 )
    {
        menu.addAction(m_ui->actionDelete_all_events);
    }
    menu.addSeparator();
    menu.addAction(m_ui->actionGo_to_today);
    menu.exec(mapToGlobal(pos));
}

void ScheduleWidget::on_tableEvents_customContextMenuRequested(QPoint pos)
{

    QMenu menu;
    menu.addAction(m_ui->actionAddEvent);
    if( m_ui->tableEvents->rowAt(pos.y()) != -1 )
    {
        menu.addAction(m_ui->actionEdit_event);
        menu.addAction(m_ui->actionDelete_event);
    }

    if( mEventsModel.rowCount() > 0 )
    {
        menu.addAction(m_ui->actionDelete_all_events);
    }

    menu.addSeparator();
    menu.exec(m_ui->tableEvents->mapToGlobal(pos));
}

void ScheduleWidget::on_actionEdit_event_triggered()
{
    QModelIndexList selectedIndices = m_ui->tableEvents->selectionModel()->selectedIndexes();
    QModelIndex index;
    QList<int> rows;
    for(int i=0; i<selectedIndices.size(); ++i)
    {
        index = selectedIndices[i];
        int row = index.row();
        if( !rows.contains(row) )
        {
            rows.append(row);
        }
    }
    if( rows.size() == 1 )
    {
        Event * eSrc = mEventsModel.getEventForRow(rows[0]);
        AddEvent aed(this);
        aed.setWindowTitle(tr("@Edit event"));
        aed.setEvent(eSrc);
        Event * eDst = getEventFromDialog(aed);
        if( eDst )
        {
            EventManager::getSingleton().removeEvent(eSrc);
            EventManager::getSingleton().addEvent(eDst);

            // refresh calendar
            refreshCalendarWidget(m_ui->calendarWidget->yearShown(), m_ui->calendarWidget->monthShown());
            // refresh event list
            refreshEventListForDate(m_ui->calendarWidget->selectedDate());
        }
    }
}

void ScheduleWidget::on_actionGo_to_today_triggered()
{
    m_ui->calendarWidget->showToday();
    m_ui->calendarWidget->setSelectedDate(QDate::currentDate());
}

void ScheduleWidget::on_actionAddEvent_triggered()
{
    performAddEvent();
}

void ScheduleWidget::setupTableEvents()
{
    m_ui->tableEvents->setModel(&mEventsModel);
    m_ui->tableEvents->resizeColumnsToContents();
}

void ScheduleWidget::setupTableForToday()
{
        QDate currentDate(QDate::currentDate());
        refreshEventListForDate(currentDate);
        refreshCalendarWidget(currentDate.year(), currentDate.month());
}

void ScheduleWidget::performAddEvent()
{
        AddEvent aed(this);
        QDateTime currentDate;
        currentDate.setDate(m_ui->calendarWidget->selectedDate());
        // round current time up
        QTime currentTime(QTime::currentTime().hour(), QTime::currentTime().minute() + 1);
        currentDate.setTime(currentTime);
        aed.setCurrentDate(currentDate);

        Event * e = getEventFromDialog(aed);

        if( e )
        {
            EventManager::getSingleton().addEvent(e);

            // refresh calendar
            refreshCalendarWidget(m_ui->calendarWidget->yearShown(), m_ui->calendarWidget->monthShown());
            // refresh event list
            refreshEventListForDate(m_ui->calendarWidget->selectedDate());
        }
}

Event * ScheduleWidget::getEventFromDialog(AddEvent & aed)
{
    if( aed.exec() == QDialog::Accepted )
    {
        // colect data from dialog to create an event
        QDateTime startDate;
        QDateTime endDate;
        Event * e = new Event;
        e->setStartDateTime(aed.startDate());
        e->setEndDateTime(aed.endDate());
        e->setSummary(aed.description());
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
        return e;
    }
    return 0;
}

void ScheduleWidget::performDeleteEvent()
{
}

void ScheduleWidget::eventActivated(const QModelIndex & modelIndex)
{
        modelIndex.column();
}

void ScheduleWidget::refreshCalendarWidget(int year, int month)
{
        qDebug() << "calendar page changed: " << year << "/" << month;
        QDate date(year, month, 1);
        QDate prevMonth = date.addMonths(-1);
        QDate nextMonth = date.addMonths(1);

        QList<Event*> events = EventManager::getSingleton().getEventsForMonth(year, month);
        // there are some days visible on the calendar from the previous and the next months
        // it is needed to collect events for that days and mark them if there are events planned on them
        // collect events for previous month and append them to list
        QList<Event*> eventsPrev = EventManager::getSingleton().getEventsForMonth(prevMonth.year(), prevMonth.month());
        foreach( Event * e, eventsPrev )
        {
            events.append(e);
        }
        // collect events for next month and append them to list
        QList<Event*> eventsNext = EventManager::getSingleton().getEventsForMonth(nextMonth.year(), nextMonth.month());
        foreach( Event * e, eventsNext )
        {
            events.append(e);
        }

        QTextCharFormat normalCharFormat;

        QTextCharFormat charFormat;
        charFormat.setFontWeight(QFont::Bold);
        charFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);

        // check the last week of the previous month
        QDate start = date.addDays(-7);
        // check also the first week of the next month
        QDate end = date.addMonths(1).addDays(7);
        while(start <= end)
        {
            qDebug() << "checking: " << start.toString();
                date = start;
                m_ui->calendarWidget->setDateTextFormat(date, normalCharFormat);
                foreach( Event * e, events )
                {
                    if( e->recursOn(date) )
                    {
                        qDebug() << "marking: " << start.toString();
                        m_ui->calendarWidget->setDateTextFormat(date, charFormat);
                    }
                }
                start = date.addDays(1);
        }
}

void ScheduleWidget::refreshEventListForDate(QDate date)
{
    mEventsModel.setEvents(EventManager::getSingleton().getEventsForDate(date));
    m_ui->tableEvents->resizeColumnsToContents();
    m_ui->tableEvents->horizontalHeader()->setStretchLastSection(true);
}

void ScheduleWidget::on_calendarWidget_currentPageChanged(int year, int month)
{
    refreshCalendarWidget(year, month);
}

void ScheduleWidget::on_calendarWidget_clicked(QDate date)
{
    qDebug() << "dateChanged: " << date.toString();
    refreshEventListForDate(date);
}

void ScheduleWidget::on_calendarWidget_selectionChanged()
{
    on_calendarWidget_clicked(m_ui->calendarWidget->selectedDate());
}

void ScheduleWidget::on_actionDelete_event_triggered()
{
    if( QMessageBox::question(this, tr("@Confirm deletion"),
                              tr("@Do you really want to delete this event?"),
                              QMessageBox::Yes|QMessageBox::No)
        == QMessageBox::Yes )
    {
        QModelIndexList selectedIndices = m_ui->tableEvents->selectionModel()->selectedIndexes();
        QModelIndex index;
        QList<int> rows;
        for(int i=0; i<selectedIndices.size(); ++i)
        {
            index = selectedIndices[i];
            int row = index.row();
            if( !rows.contains(row) )
            {
                rows.append(row);
            }
        }

        int rowToDelete = 0;
        foreach(rowToDelete, rows)
        {
            mEventsModel.removeEventFromRow(rowToDelete);
        }

        refreshCalendarWidget(m_ui->calendarWidget->yearShown(), m_ui->calendarWidget->monthShown());
    }
}

void ScheduleWidget::on_actionDelete_all_events_triggered()
{
    if( QMessageBox::question(this, tr("@Confirm deletion"),
                              tr("@Do you really want to delete all events on %1?").arg(m_ui->calendarWidget->selectedDate().toString()),
                              QMessageBox::Yes|QMessageBox::No)
        == QMessageBox::Yes )
    {
        mEventsModel.removeAllEvents();
        refreshCalendarWidget(m_ui->calendarWidget->yearShown(), m_ui->calendarWidget->monthShown());
    }
}

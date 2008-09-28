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

#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QtGui/QWidget>
#include <QModelIndex>
#include <QDate>
#include <ui_schedulewidget.h>

#include "eventtablemodel.h"

namespace TinyOrganizer
{

class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    ScheduleWidget(QWidget *parent = 0);
    ~ScheduleWidget();

public slots:
    void performAddEvent();
    void performDeleteEvent();
    void eventActivated(const QModelIndex & modelIndex);
    void dateChanged(QDate currentDate);
    void calendarPageChanged(int year, int month);
private:
    void connectSignals();
    void refreshCalendarWidget(int year, int month);
    void refreshEventListForDate(QDate date);
    void setupTableEvents();
    void setupTableForToday();

private:
    Ui::ScheduleWidgetClass ui;
    EventTableModel mEventsModel;
};

}

#endif // SCHEDULEWIDGET_H

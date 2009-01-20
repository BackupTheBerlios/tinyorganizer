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

#include "eventtablemodel.h"

#include <QtGui/QWidget>
#include <QDate>

namespace Ui {
    class ScheduleWidget;
}

class ScheduleWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(ScheduleWidget)
public:
    explicit ScheduleWidget(QWidget *parent = 0);
    virtual ~ScheduleWidget();

public slots:
    void performAddEvent();
    void performDeleteEvent();
    void eventActivated(const QModelIndex & modelIndex);

protected:
    virtual void changeEvent(QEvent *e);

private:
    void refreshCalendarWidget(int year, int month);
    void refreshEventListForDate(QDate date);
    void setupTableEvents();
    void setupTableForToday();

private:
    Ui::ScheduleWidget *m_ui;
    TinyOrganizer::EventTableModel mEventsModel;

private slots:
    void on_calendarWidget_customContextMenuRequested(QPoint pos);
    void on_tableEvents_customContextMenuRequested(QPoint pos);
    void on_calendarWidget_currentPageChanged(int, int);
    void on_calendarWidget_clicked(QDate);
    void on_actionGo_to_today_triggered();
    void on_actionAddEvent_triggered();
};

#endif // SCHEDULEWIDGET_H

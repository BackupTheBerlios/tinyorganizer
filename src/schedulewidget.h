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
#include "ui_schedulewidget.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    ScheduleWidget(QWidget *parent = 0);
    ~ScheduleWidget();

private:
    Ui::ScheduleWidgetClass ui;
};

#endif // SCHEDULEWIDGET_H

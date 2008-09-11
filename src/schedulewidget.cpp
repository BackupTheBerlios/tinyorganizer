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

#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
}

ScheduleWidget::~ScheduleWidget()
{
	int a = 5;
	a++;
}

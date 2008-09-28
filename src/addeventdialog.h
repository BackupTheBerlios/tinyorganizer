/*
 *   addeventdialog.cpp
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

#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QtGui/QDialog>
#include <QDate>

#include <ui_addeventdialog.h>

#include "calendar-core/recurrence.h"

namespace TinyOrganizer
{

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    AddEventDialog(QWidget *parent = 0);
    ~AddEventDialog();

    void setCurrentDate(QDateTime dateTime);

    bool allDayEvent() const;
    QDateTime startDate() const;
    QDateTime endDate() const;

    Recurrence::RecurrenceType recurrenceType() const;
    QDate repeatUntil() const;

    QString summary() const;
    QString location() const;

public slots:
    void performOkClicked();
    void recurrenceComboChanged(int index);

private:
    void connectSignals();
    void reportError(const QString & msg);
    bool checkDates();
    bool checkDescription();
    bool checkRecurrence();
    bool checkReminder();


private:
    Ui::AddEventDialogClass ui;
};

}

#endif // ADDEVENTDIALOG_H

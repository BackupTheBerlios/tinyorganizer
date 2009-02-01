/*
 *   addevent.cpp
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

#ifndef ADDEVENT_H
#define ADDEVENT_H

#include "calendar-core/recurrence.h"

#include <QtGui/QDialog>
#include <QDateTime>

namespace Ui {
    class AddEvent;
}

namespace TinyOrganizer
{
    class Event;
}

class AddEvent : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AddEvent)
public:
    explicit AddEvent(QWidget *parent = 0);
    virtual ~AddEvent();

    void setCurrentDate(QDateTime dateTime);
    void setEvent(TinyOrganizer::Event * e);

    QDateTime startDate() const;
    QDateTime endDate() const;
    QString description() const;
    QString location() const;
    TinyOrganizer::Recurrence::RecurrenceType recurrenceType() const;
    bool allDayEvent() const;
    QDate repeatUntil() const;

protected:
    virtual void changeEvent(QEvent *e);

private slots:
    void on_comboRecurrence_currentIndexChanged(int);
    void on_comboRemind_currentIndexChanged(int);
    void on_editEventStart_dateTimeChanged(const QDateTime & datetime);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    bool checkDates();
    bool checkDescription();
    bool checkRecurrence();
    bool checkReminder();
    QDate calculateHitCount() const;
    void reportError(const QString & msg);

private:
    Ui::AddEvent *m_ui;
};

#endif // ADDEVENT_H

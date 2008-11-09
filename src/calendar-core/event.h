/*
 *   event.h
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
 *   Created on: 2008-09-11
 *   Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <QDateTime>
#include <QDate>
#include <QString>

#include "recurrence.h"


namespace TinyOrganizer {

/*
 *
 */
class Recurrence;

class Event {
public:
	Event();
	virtual ~Event();

	void setAllDay(bool allDay);
	bool allDay() const;

	void setStartDateTime(const QDateTime& startTime);
	QDateTime startDateTime() const;

	void setEndDateTime(const QDateTime& endTime);
	QDateTime endDateTime() const;

	void setSummary(const QString& summary);
	QString summary() const;

	void setLocation(const QString& location);
	QString location() const;

	void setRecurrence(const Recurrence& recurrence);
        const Recurrence & recurrence() const;

	bool recursOn(const QDate & date) const;
    bool RecursOn(const QDateTime & dateTime) const;

    bool isValid() const;

private:
	bool mAllDay;
	QString mLocation;
	QString mSummary;
	QDateTime mStartDateTime;
	QDateTime mEndDateTime;
	Recurrence mRecurrence;
};

}

#endif /* EVENT_H_ */

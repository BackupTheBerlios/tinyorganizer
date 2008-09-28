/*
 *   event.cpp
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

#include "event.h"

#include <QDateTime>
#include <QString>

namespace TinyOrganizer {

Event::Event():
	mAllDay(false)
{

}

Event::~Event()
{
}

void Event::setStartDateTime(const QDateTime & startTime)
{
	mStartDateTime = startTime;
}

QDateTime Event::startDateTime() const
{
	return mStartDateTime;
}

void Event::setEndDateTime(const QDateTime & endTime)
{
	mEndDateTime = endTime;
}

QDateTime Event::endDateTime() const
{
	return mEndDateTime;
}

void Event::setSummary(const QString & summary)
{
	mSummary = summary;
}

QString Event::summary() const
{
	return mSummary;
}

void Event::setLocation(const QString & location)
{
	mLocation = location;
}

QString Event::location() const
{
	return mLocation;
}

void Event::setRecurrence(const Recurrence & recurrence)
{
	mRecurrence = recurrence;
	mRecurrence.setStartDateTime(mStartDateTime);
}

void Event::setAllDay(bool allDay)
{
	mAllDay = allDay;
}

bool Event::allDay() const
{
	return mAllDay;
}

Recurrence & Event::recurrence()
{
	return mRecurrence;
}

bool Event::recursOn(const QDate & date) const
{
	if( date == mStartDateTime.date() )
	{
		return true;
	}
	else if( date > mStartDateTime.date() )
	{
		if( mRecurrence.recurrenceType() != Recurrence::None )
		{
			return mRecurrence.recursOn(date);
		}
	}
	return false;
}

bool Event::RecursOn(const QDateTime & dateTime) const
{
	if( dateTime == mStartDateTime )
	{
		return true;
	}
	else
	{
		if( mRecurrence.recurrenceType() != Recurrence::None )
		{
			return mRecurrence.recursOn(dateTime);
		}
	}
	return false;
}

}

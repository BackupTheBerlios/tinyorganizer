/*
 *   recurrence.cpp
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

#include "recurrence.h"

namespace TinyOrganizer
{

Recurrence::Recurrence():
        mRecurrenceType(None)
{
}

Recurrence::~Recurrence()
{
        // TODO Auto-generated destructor stub
}

void Recurrence::setUntilDate(const QDateTime & untilDate)
{
        mUntilDate = untilDate;
}

void Recurrence::setStartDateTime(QDateTime stDate)
{
        mStartDate = stDate;
}

QDateTime Recurrence::startDateTime() const
{
        return mStartDate;
}

void Recurrence::addMinute(int minute)
{
        if( !mMinutes.contains(minute) )
                mMinutes.append(minute);
}

void Recurrence::removeMinute(int minute)
{
        mMinutes.removeOne(minute);
}

QList<int> Recurrence::minute() const
{
        return mMinutes;
}

void Recurrence::addHour(int hour)
{
        if( !mHours.contains(hour) )
                mHours.append(hour);
}

void Recurrence::removeHour(int hour)
{
        mHours.removeOne(hour);
}

QList<int> Recurrence::hour() const
{
        return mHours;
}

void Recurrence::addDay(int day)
{
        mDays.append(day);
}

void Recurrence::removeDay(int day)
{
        mDays.removeOne(day);
}

QList<int> Recurrence::day() const
{
        return mDays;
}

void Recurrence::addWeekday(int weekday)
{
        if( !mWeekdays.contains(weekday) )
                mWeekdays.append(weekday);
}

void Recurrence::removeWeekday(int weekday)
{
        mWeekdays.removeOne(weekday);
}

QList<int> Recurrence::weekday() const
{
        return mWeekdays;
}

void Recurrence::addMonth(int month)
{
        if( !mMonths.contains(month) )
                mMonths.append(month);
}

void Recurrence::removeMonth(int month)
{
        mMonths.removeOne(month);
}

QList<int> Recurrence::month() const
{
        return mMonths;
}

void Recurrence::addYear(int year)
{
        if( !mYears.contains(year) )
                mYears.append(year);
}

void Recurrence::removeYear(int year)
{
        mYears.removeOne(year);
}

QList<int> Recurrence::year() const
{
        return mYears;
}

QDateTime Recurrence::untilDate() const
{
        return mUntilDate;
}

bool Recurrence::recursOn(const QDateTime & recurrDate) const
{
        if( mUntilDate.isValid() )
        {
                if( recurrDate > mUntilDate )
                {
                        return false;
                }
        }

        if( recurrDate < mStartDate )
        {
                return false;
        }

        if( mRecurrenceType == None )
        {
                return false;
        }
        else if( mRecurrenceType == Hourly )
        {
                return (matchesHour(recurrDate) && matchesMinute(recurrDate));
        }
        else if( mRecurrenceType == Minutely )
        {
                return matchesMinute(recurrDate);
        }
        else
        {
                if( recursOn(recurrDate.date()) )
                {
                        if( matchesHour(recurrDate) && matchesMinute(recurrDate) )
                        {
                                return true;
                        }
                }
        }
        return false;
}

bool Recurrence::recursOn(const QDate & recurrDate) const
{
        if( mUntilDate.isValid() )
        {
                if( recurrDate > mUntilDate.date() )
                {
                        return false;
                }
        }

        if( recurrDate < mStartDate.date() )
        {
                return false;
        }

        if( mRecurrenceType != None )
        {
                QDateTime dateTime(recurrDate);

                if( mRecurrenceType == Yearly )
                {
                        return matchesMonth(dateTime) && matchesDay(dateTime);
                }
                else if( mRecurrenceType == Monthly )
                {
                        return matchesDay(dateTime);
                }
                else if( mRecurrenceType == Weekly )
                {
                        return matchesWeekday(dateTime);
                }
                else if( mRecurrenceType == Daily )
                {
                        return true;
                }
        }
        return false;
}

int Recurrence::TimesRecursOn(const QDate & recurrDate) const
{
        recurrDate.isValid();
        return false;
}

bool Recurrence::matchesMonth(const QDateTime & recurrDate) const
{
        int month = recurrDate.date().month();
        if( mMonths.contains(month))
                return true;
        if( month == mStartDate.date().month() )
                return true;
        return false;
}

bool Recurrence::matchesDay(const QDateTime & recurrDate) const
{
        int day = recurrDate.date().day();
        if( mDays.contains(day))
                return true;
        if( day == mStartDate.date().day() )
                return true;
        return false;
}

bool Recurrence::matchesWeekday(const QDateTime & recurrDate) const
{
        int weekday = recurrDate.date().dayOfWeek();
        if( mWeekdays.contains(weekday))
                return true;
        if( weekday == mStartDate.date().dayOfWeek() )
                return true;
        return false;
}

bool Recurrence::matchesHour(const QDateTime & recurrDate) const
{
        int hour = recurrDate.time().hour();
        if( mHours.contains(hour))
                return true;
        if( hour == mStartDate.time().hour() )
                return true;
        return false;
}

bool Recurrence::matchesMinute(const QDateTime & recurrDate) const
{
        int minute = recurrDate.time().minute();
        if( mMonths.contains(minute))
                return true;
        if( minute == mStartDate.time().minute() )
                return true;
        return false;
}

void Recurrence::setRecurrenceType(RecurrenceType recurrenceType)
{
        mRecurrenceType = recurrenceType;
}

Recurrence::RecurrenceType Recurrence::recurrenceType() const
{
        return mRecurrenceType;
}

bool Recurrence::matchesYear(const QDateTime & recurrDate) const
{
        int month = recurrDate.date().month();
        if( mMonths.contains(month))
                return true;
        if( month == mStartDate.date().month() )
                return true;
        return false;
}

}


























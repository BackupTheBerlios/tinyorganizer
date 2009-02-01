/*
 *   recurrence.h
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

#ifndef RECURRENCE_H_
#define RECURRENCE_H_

#include <QDateTime>
#include <QDate>
#include <QList>

namespace TinyOrganizer
{

class Recurrence {
public:
        enum RecurrenceType
        {
                None = 0x00,
                Minutely = 0x01,
                Hourly = 0x02,
                Daily = 0x04,
                Weekly = 0x08,
                Monthly = 0x10,
                Yearly = 0x11
        };

        Recurrence();
        virtual ~Recurrence();

        QDateTime startDateTime() const;
        void setStartDateTime(QDateTime stDate);

        void addMinute(int minute);
        void removeMinute(int minute);
        QList<int> minute() const;

        void addHour(int hour);
        void removeHour(int hour);
        QList<int> hour() const;

        void addDay(int day);
        void removeDay(int day);
        QList<int> day() const;

        void addWeekday(int weekday);
        void removeWeekday(int weekday);
        QList<int> weekday() const;

        void addMonth(int month);
        void removeMonth(int month);
        QList<int> month() const;

        void addYear(int year);
        void removeYear(int year);
        QList<int> year() const;

        void setUntilDate(const QDateTime& untilDate);
        QDateTime untilDate() const;

        bool recursOn(const QDateTime& recurrDate) const;
        bool recursOn(const QDate& recurrDate) const;

        int TimesRecursOn(const QDate& recurrDate) const;

        void setRecurrenceType(RecurrenceType recurrenceType);
        RecurrenceType recurrenceType() const;
private:
        bool matchesMonth(const QDateTime& recurrDate) const;
        bool matchesDay(const QDateTime& recurrDate) const;
        bool matchesWeekday(const QDateTime& recurrDate) const;
        bool matchesHour(const QDateTime& recurrDate) const;
        bool matchesMinute(const QDateTime& recurrDate) const;
        bool matchesYear(const QDateTime& recurrDate) const;
private:
        QList<int> mMinutes;
        QList<int> mHours;
        QList<int> mDays;
        QList<int> mWeekdays;
        QList<int> mMonths;
        QList<int> mYears;

        QDateTime mStartDate;

        QDateTime mUntilDate;

        RecurrenceType mRecurrenceType;
};

}
#endif /* RECURRENCE_H_ */

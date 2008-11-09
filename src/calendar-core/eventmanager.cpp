/*
 *   eventmanager.cpp
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

#include "eventmanager.h"
#include "eventstore.h"
#include "event.h"

#include <QDebug>


namespace TinyOrganizer
{

QList<Event*> EventManager::getEventsBetweenDates(const QDate & dateFirst, const QDate & dateLast) const
{
	QList<Event*> result;

	QDate date(dateFirst);

#ifdef QDEBUG_H
        qDebug() << "dateFirst: " << dateFirst.toString() << " dateLast: " << dateLast.toString();
#endif

	while(date <= dateLast )
	{
		QList<Event*> eventsForDate = getEventsForDate(date);
		if( eventsForDate.count() > 0 )
		{
			QList<Event*>::iterator it = eventsForDate.begin();
			QList<Event*>::iterator end = eventsForDate.end();
			while( it != end )
			{
				if( (*it)->recursOn(date) )
				{
					result.append((*it));
				}
				++it;
			}
		}
		date = date.addDays(1);
	}
	return result;
}

QList<Event*> EventManager::getEventsForMonth(int year, int month) const
{
	QList<Event*> result;

	QDate date;

	for( int i=1; i<= 31; ++i)
	{
		if( date.isValid(year, month, i))
		{
			date.setDate(year, month, i);
			QList<Event*> eventsForDate = getEventsForDate(date);
			if( eventsForDate.count() > 0 )
			{
				QList<Event*>::iterator it = eventsForDate.begin();
				QList<Event*>::iterator end = eventsForDate.end();
				while( it != end )
				{
					result.append((*it));
					++it;
				}
			}
		}
	}
	return result;
}

QList<Event*> EventManager::getEventsForDate(const QDate & date) const
{
	QList<Event*>::const_iterator it = mEvents.begin();
	QList<Event*>::const_iterator end = mEvents.end();
	QList<Event*> result;

	while( it != end )
	{
		if( (*it)->recursOn(date) )
		{
			result.append((*it));
		}
		++it;
	}
	return result;
}

void EventManager::addEvent(Event *e)
{
	mEvents.append(e);
}

void EventManager::removeEvent(Event *e)
{
	mEvents.removeOne(e);
}



bool EventManager::saveEventsToFile(const QString & filename)
{
	EventStore es(filename);
	return es.saveEventsToFile(mEvents);
}

bool EventManager::loadEventsFromFile(const QString & filename)
{
	EventStore es(filename);
	QList<Event*> events;

	if( es.loadEventsFromFile(events) )
	{
		mEvents = events;
		return true;
	}
	return false;
}

EventManager::EventManager()
{
//	QDateTime date(QDateTime::currentDateTime());
//	date = date.addYears(-1);
//
//	for(int i=0; i<35000; ++i)
//	{
//		Event * e = new Event();
//		date = date.addSecs(3600);
//		e->setStartDateTime(date);
//		e->setEndDateTime(date.addSecs(3600));
//		e->setLocation("Twoja stara");
//		e->setSummary("Twoja stara!");
//		mEvents.append(e);
//	}
}

EventManager::~EventManager()
{
	// TODO Auto-generated destructor stub
}

}

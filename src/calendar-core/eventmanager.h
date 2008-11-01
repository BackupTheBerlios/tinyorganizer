/*
 *   eventmanager.h
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

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <QList>
#include <QMap>
#include <QDate>
#include <QDomDocument>

#include "singleton.h"

/*
 *
 */
namespace TinyOrganizer {

class Event;

class EventManager: public Singleton<EventManager>
{
	friend class Singleton<EventManager>;
public:
	virtual ~EventManager();

	void addEvent(Event *e);
	void removeEvent(Event *e);

	QList<Event*> getEvents() const;

	QList<Event*> getEventsForMonth(int year, int month) const;
	QList<Event*> getEventsBetweenDates(const QDate & dateFirst, const QDate & dateLast) const;
	QList<Event*> getEventsForDate(const QDate & date) const;

	bool saveEventsToFile(const QString & filename);
	bool loadEventsFromFile(const QString & filename);
private:
	EventManager();
	EventManager(const EventManager &);
	const EventManager & operator =(const EventManager &);
private:
	QList<Event*> mEvents;
};

}

#endif /* EVENTMANAGER_H_ */

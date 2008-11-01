/*
 * EventStore.h
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
 *   Created on: 2008-10-12
 *   Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

#ifndef EVENTSTORE_H_
#define EVENTSTORE_H_

#include <QList>
#include <QDomElement>
#include <QString>

namespace TinyOrganizer {

class Event;

class EventStore {
public:
	EventStore(const QString & filename);
	virtual ~EventStore();

	bool saveEventsToFile(QList<Event*> events);
	bool loadEventsFromFile(QList<Event*> & events);

private:
	void appendEvent(QDomElement & eventsList, Event *event);
	void serializeEvents(QDomDocument & doc, QList<Event*> events);

private:
	QString mFilename;
};

}

#endif /* EVENTSTORE_H_ */

/*
 * eventstore.cpp
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

#include "eventstore.h"
#include "event.h"

#include <QString>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

namespace TinyOrganizer {

EventStore::EventStore(const QString & filename):
	mFilename(filename)
{

}

EventStore::~EventStore()
{
}

bool EventStore::saveEventsToFile(QList<Event*> events)
{
	QDomDocument doc;
	QFile file(mFilename);
	if( !file.open(QIODevice::WriteOnly) )
		return false;

	serializeEvents(doc, events);

	QTextStream out(&file);
	doc.save(out, 4);
	return true;
}

bool EventStore::loadEventsFromFile(QList<Event*> & events)
{
	 QDomDocument doc;
	 QFile file(mFilename);
	 if (!file.open(QIODevice::ReadOnly))
	     return false;
	 if (!doc.setContent(&file)) {
	     file.close();
	     return false;
	 }
	 file.close();
	 return true;
}

void EventStore::serializeEvents(QDomDocument & doc, QList<Event*> events)
{
	QList<Event*>::iterator it = events.begin();
	QList<Event*>::iterator end = events.end();

	QDomElement eventsList(doc.createElement("event-list"));


	while( it != end )
	{
		appendEvent(eventsList, (*it));
		++it;
	}

	doc.appendChild(eventsList);
}

void EventStore::appendEvent(QDomElement & eventsList, Event *event)
{
	QDomElement eventEl = eventsList.ownerDocument().createElement("event");
	QDomElement startDate = eventsList.ownerDocument().createElement("start-date");
	QDomElement endDate = eventsList.ownerDocument().createElement("end-date");
	QDomElement description = eventsList.ownerDocument().createElement("description");
	QDomElement location = eventsList.ownerDocument().createElement("location");
	QDomElement recurrence = eventsList.ownerDocument().createElement("recurrence");

	QDomText textStart = eventsList.ownerDocument().createTextNode("");
	QDomText textEnd = eventsList.ownerDocument().createTextNode("");
	QDomText textDescription = eventsList.ownerDocument().createTextNode("");
	QDomText textLocation = eventsList.ownerDocument().createTextNode("");

	if( event->allDay() )
	{
		eventEl.setAttribute("allday", "true");

		textStart.setNodeValue(QString("%1").arg(event->startDateTime().toTime_t()));
		startDate.appendChild(textStart);
		eventEl.appendChild(startDate);
	}
	else
	{
		textStart.setNodeValue((QString("%1").arg(event->startDateTime().toTime_t())));
		startDate.appendChild(textStart);
		eventEl.appendChild(startDate);

		textEnd.setNodeValue((QString("%1").arg(event->endDateTime().toTime_t())));
		endDate.appendChild(textEnd);
		eventEl.appendChild(endDate);
	}

	textDescription.setNodeValue(event->summary());
	description.appendChild(textDescription);
	eventEl.appendChild(description);

	textLocation.setNodeValue(event->location());
	location.appendChild(textLocation);
	eventEl.appendChild(location);

	if( event->recurrence().recurrenceType() != Recurrence::None )
	{
		Recurrence r = event->recurrence();
		QDomElement recurEl = eventsList.ownerDocument().createElement("recurrence");

		QString typeStr;

		if( r.recurrenceType() == Recurrence::Daily )
		{
			typeStr = "daily";
		}
		else if( r.recurrenceType() == Recurrence::Hourly )
		{
			typeStr = "hourly";
		}
		else if( r.recurrenceType()  == Recurrence::Minutely )
		{
			typeStr = "minutely";
		}
		else if( r.recurrenceType() == Recurrence::Monthly )
		{
			typeStr = "monthly";
		}
		else if( r.recurrenceType() == Recurrence::Weekly )
		{
			typeStr = "weekly";
		}
		else if( r.recurrenceType() == Recurrence::Yearly )
		{
			typeStr = "yearly";
		}

		recurEl.setAttribute("type", typeStr);

		QDomElement startEl = eventsList.ownerDocument().createElement("start-date");
		QDomText textStart = eventsList.ownerDocument().createTextNode("");
		textStart.setNodeValue(QString("%1").arg(r.startDateTime().toTime_t()));
		startEl.appendChild(textStart);
		recurEl.appendChild(startEl);

		QDomElement untilEl = eventsList.ownerDocument().createElement("until-date");
		QDomText textUntil = eventsList.ownerDocument().createTextNode("");
		textUntil.setNodeValue(QString("%1").arg(r.untilDate().toTime_t()));
		untilEl.appendChild(textUntil);
		recurEl.appendChild(untilEl);

		eventEl.appendChild(recurEl);
	}

	eventsList.appendChild(eventEl);
}

}

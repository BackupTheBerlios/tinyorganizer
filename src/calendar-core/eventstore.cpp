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

bool EventStore::saveEventsToFile(const QList<Event*> events)
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
//	     return false;
         }

     deserializeEvents(doc, events);
	 file.close();
	 return true;
}

void EventStore::deserializeEvents(const QDomDocument & doc, QList<Event*> & events)
{
    QDomNodeList eventNodes = doc.elementsByTagName("event");
    if( eventNodes.count() > 0 )
    {
        for(int i=0; i<eventNodes.count(); ++i)
        {
            if( eventNodes.at(i).isElement() )
            {
                QDomElement element = eventNodes.at(i).toElement();
                Event *event = createEventFromXml(element);
                events.append(event);
            }
        }
    }
}

Event * EventStore::createEventFromXml(const QDomElement & element)
{
    Event * event = new Event();
    if( element.hasAttribute("id") )
    {
        event->setId(element.attribute("id"));
    }
    if( EventStore::containsElement(element, "start-date") )
    {
        QDomElement startDateElement = getFirstElementFromList(element, "start-date");
        QString text = startDateElement.text();
        bool ok = false;
        uint timetValue = text.toUInt(&ok, 10);
        if( ok )
        {
            QDateTime startDateTime = QDateTime::fromTime_t(timetValue);
            event->setStartDateTime(startDateTime);
        }
    }
    if( EventStore::containsElement(element,"end-date") )
    {
        QDomElement endDateElement = getFirstElementFromList(element, "end-date");
        QString text = endDateElement.text();
        bool ok = false;
        uint timetValue = text.toUInt(&ok, 10);
        if( ok )
        {
            QDateTime endDateTime = QDateTime::fromTime_t(timetValue);
            event->setEndDateTime(endDateTime);
        }
    }
    if( EventStore::containsElement(element, "description" ) )
    {
        QDomElement descriptionElement = getFirstElementFromList(element, "description");
        QString text = descriptionElement.text();
        event->setSummary(text);
    }
    if( EventStore::containsElement(element, "location") )
    {
        QDomElement locationElement = getFirstElementFromList(element, "location");
        QString text = locationElement.text();
        event->setLocation(text);
    }
    if( EventStore::containsElement(element, "recurrence") )
    {
        QDomElement recurrenceElement = getFirstElementFromList(element, "recurrence");
        Recurrence r = parseRecurrence(recurrenceElement);
        event->setRecurrence(r);
    }

    if( !event->isValid() )
    {
        delete event;
        event = 0;
    }
    return event;
}

Recurrence EventStore::parseRecurrence(const QDomElement & recurElement)
{
    Recurrence r;
    if( recurElement.attributes().contains("type") )
    {
        QString typeText = recurElement.attribute("type");
        if( typeText == "minutely" )
        {
            r.setRecurrenceType(Recurrence::Minutely);
        }
        else if( typeText == "hourly" )
        {
            r.setRecurrenceType(Recurrence::Hourly);
        }
        else if( typeText == "daily" )
        {
            r.setRecurrenceType(Recurrence::Daily);
        }
        else if( typeText == "weekly" )
        {
            r.setRecurrenceType(Recurrence::Weekly);
        }
        else if( typeText == "monthly" )
        {
            r.setRecurrenceType(Recurrence::Monthly);
        }
        else if( typeText == "yearly" )
        {
            r.setRecurrenceType(Recurrence::Yearly);
        }
    }

    if( EventStore::containsElement(recurElement, "start-date") )
    {
        QDomElement startDateTimeElement = EventStore::getFirstElementFromList(recurElement, "start-date");
        bool ok = false;
        uint timetValue = startDateTimeElement.text().toUInt(&ok, 10);
        if( ok )
        {
            QDateTime startDateTime = QDateTime::fromTime_t(timetValue);
            r.setStartDateTime(startDateTime);
        }
    }

    if( EventStore::containsElement(recurElement, "until-date") )
    {
        QDomElement untilDateTimeElement = EventStore::getFirstElementFromList(recurElement, "until-date");
        bool ok = false;
        uint timetValue = untilDateTimeElement.text().toUInt(&ok, 10);
        if( ok )
        {
            QDateTime untilDateTime = QDateTime::fromTime_t(timetValue);
            r.setUntilDate(untilDateTime);
        }
    }

    return r;
}

bool EventStore::containsElement(const QDomElement & element, QString tagname)
{
    QDomNodeList nodeList = element.elementsByTagName(tagname);
    if( nodeList.size() > 0 )
    {
        return true;
    }
    return false;
}

QDomElement EventStore::getFirstElementFromList(const QDomElement & element, QString tagname)
{
    QDomNodeList nodeList = element.elementsByTagName(tagname);
    if( nodeList.size() > 0 )
    {
        return nodeList.at(0).toElement();
    }
    return QDomElement();
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

void EventStore::appendEvent(QDomElement & eventsList, const Event *event)
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
        eventEl.setAttribute("id", event->id());

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

/*
 * eventstore.h
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

#include "recurrence.h"

#include <QList>
#include <QString>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>

namespace TinyOrganizer {

    class Event;

    class EventStore {
    public:
        EventStore(const QString & filename);
        virtual ~EventStore();

        bool saveEventsToFile(QList<Event*> events);
        bool loadEventsFromFile(QList<Event*> & events);

    private:
        void appendEvent(QDomElement & eventsList, const Event *event);
        void serializeEvents(QDomDocument & doc, const QList<Event*> events);
        Event * createEventFromXml(const QDomElement & element);
        void deserializeEvents(const QDomDocument & doc, QList<Event*> & events);

        static bool containsElement(const QDomElement & element, QString tagname);
        static QDomElement getFirstElementFromList(const QDomElement & element, QString tagname);
        static Recurrence parseRecurrence(const QDomElement & recurElement);

    private:
        QString mFilename;
    };

}

#endif /* EVENTSTORE_H_ */

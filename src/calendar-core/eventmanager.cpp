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
 *   Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

#include "eventmanager.h"
#include "eventstore.h"
#include "event.h"

#include <QDebug>
#include <QDir>
#include <QApplication>
#include <QMessageBox>
#include <QtNetwork/QHostInfo>

#include <algorithm>


namespace TinyOrganizer
{

    QList<Event*> EventManager::getEventsBetweenDates(const QDate & dateFirst, const QDate & dateLast) const
    {
        qDebug() << "[getEventsBetweenDates]";
        QList<Event*> result;

        QDate date(dateFirst);
        qDebug() << "dateFirst: " << dateFirst.toString() << " dateLast: " << dateLast.toString();
        while(date <= dateLast){
            QList<Event*> eventsForDate = getEventsForDate(date);
            if(eventsForDate.count() > 0){
                QList<Event*>::iterator it = eventsForDate.begin();
                QList<Event*>::iterator end = eventsForDate.end();
                while(it != end){
                    if((*it)->recursOn(date)){
                        result.append((*it));
                    }
                    ++it;
                }

            }

            date = date.addDays(1);
        }

        qDebug() << "~[getEventsBetweenDates]";
        return result;
    }

    QList<Event*> EventManager::getEventsForMonth(int year, int month) const
    {
        qDebug() << "[getEventsForMonth]";
        QList<Event*> result;
        QDate date;
        for(int i = 1;i <= 31;++i){
            if(date.isValid(year, month, i)){
                date.setDate(year, month, i);
                QList<Event*> eventsForDate = getEventsForDate(date);
                if(eventsForDate.count() > 0){
                    QList<Event*>::iterator it = eventsForDate.begin();
                    QList<Event*>::iterator end = eventsForDate.end();
                    while(it != end){
                        result.append((*it));
                        ++it;
                    }
                }

            }

        }

        qDebug() << "~[getEventsForMonth]";
        return result;
    }

    QList<Event*> EventManager::getEventsForDate(const QDate & date) const
    {
        qDebug() << "[getEventsForDate]";

        QList<Event*> result;

        foreach( Event * e, mEvents )
        {
            if( e->recursOn(date) )
            {
                result.append(e);
            }
        }

        if( mRegularEvents.contains(date) )
        {
            QList<Event*> events = mRegularEvents[date];
            foreach( Event * e, events )
            {
                result.append(e);
            }
            // why the below does not work?
            // it does not work only with the QList iterator as destination
//            std::copy(events.begin(), events.end(), result.end());
        }

        qDebug() << "~[getEventsForDate]";
        return result;
    }

    QString EventManager::generateId()
    {
        qDebug() << "[generateId]";
        QString hostName = QHostInfo::localHostName();
        qsrand(QDateTime::currentDateTime().toTime_t());
        QString id;
        do
        {
            long randNum = qrand() % 0xffffff;
            id = QString("%1").arg(randNum) + "@" + hostName;
        } while( mUsedIds.contains(id) );

        mUsedIds.insert(id);

        qDebug() << "~[generateId]";
        return id;
    }

    void EventManager::addEvent(Event *e)
    {
        qDebug() << "[addEvent]";
        if( e->id().size() == 0 )
        {
            QString id = generateId();
            e->setId(id);
        }

        if( e->recurrence().recurrenceType() == Recurrence::None )
        {
            mRegularEvents[e->startDateTime().date()].append(e);
        }
        else
        {
            mEvents.append(e);
        }
        qDebug() << "~[addEvent]";
    }

    void EventManager::removeEvent(Event *e)
    {
        qDebug() << "[removeEvent]";
        if( e->recurrence().recurrenceType() == Recurrence::None )
        {
            QDate startDate(e->startDateTime().date());
            if( mRegularEvents.contains(startDate) )
            {
                mRegularEvents[startDate].removeOne(e);
                if( mRegularEvents[startDate].size() == 0 )
                {
                    mRegularEvents.remove(startDate);
                }
            }
        }
        else
        {
            mEvents.removeOne(e);
        }
        mUsedIds.remove(e->id());
        qDebug() << "~[removeEvent]";
    }

    bool EventManager::saveEventsToFile(const QString & filename)
    {
        qDebug() << "[saveEventsToFile]";

        EventStore es(filename);

        QList<Event*> eventsToSave;

        // copy all recurrent events
        foreach( Event * e, mEvents )
        {
            eventsToSave.append(e);
        }

        // copy all regular events
        QList<QList<Event*> > values = mRegularEvents.values();
        QList<Event *> list;
        foreach( list, values)
        {
            foreach( Event * e, list )
            {
                eventsToSave.append(e);
            }
        }

        qDebug() << "~[saveEventsToFile]";
        return es.saveEventsToFile(eventsToSave);
    }

    bool EventManager::loadEventsFromFile(const QString & filename)
    {
        qDebug() << "[loadEventsFromFile]";
        EventStore es(filename);
        QList<Event*> events;
        if(es.loadEventsFromFile(events)){
            for(int i=0; i<events.size(); ++i)
            {
                Event * e = events[i];
                if( e->recurrence().recurrenceType() == Recurrence::None )
                {
                    QDate startDate(e->startDateTime().date());
                    mRegularEvents[startDate].append(e);
                }
                else
                {
                    mEvents.append(e);
                }
            }
            qDebug() << "~[loadEventsFromFile]";
            return true;
        }
        qDebug() << "~[loadEventsFromFile]";
        return false;
    }

    QString TinyOrganizer::EventManager::getSettingsDir() const
    {
        qDebug() << "[getSettingsDir]";
        QString homeDirPath = QDir::homePath();
        QString dot;
        QString appname = QApplication::instance()->applicationName();

        // special behaviour for unix-like systems
#if defined (Q_OS_LINUX) || defined (Q_OS_UNIX)
        dot = ".";
        appname = appname.toLower();
#endif
        homeDirPath += QDir::separator() + dot + appname;
        qDebug() << "~[getSettingsDir]";
        return homeDirPath;
    }

    QString TinyOrganizer::EventManager::getEventsFilePath() const
    {
        return getSettingsDir() + QDir::separator() + "events.xml";
    }

    bool TinyOrganizer::EventManager::saveEventsToHome()
    {
        qDebug() << "[saveEventsToHome]";
        QString homeDirPath = getSettingsDir();
        QDir dir;
        if( !dir.exists(homeDirPath) )
        {
            if( !dir.mkpath(homeDirPath) )
            {
                // failed to create settings dir
                QMessageBox::critical(0, "Error saving data!",
                                      "There was an error while creating directory "
                                      + homeDirPath + " for application data.");
                qDebug() << "~[saveEventsToHome]";
                return false;
            }
        }
        // proceed with saving events
        if( !saveEventsToFile(getEventsFilePath()) )
        {
            QMessageBox::critical(0,
                                  "Error saving data!",
                                  "There was an error while saving the application data.");
        }

        qDebug() << "~[saveEventsToHome]";
        return true;
    }

    bool TinyOrganizer::EventManager::loadEventsFromHome()
    {
        return loadEventsFromFile(getEventsFilePath());
    }

    EventManager::EventManager()
    {
    }

    EventManager::~EventManager()
    {
    }

}

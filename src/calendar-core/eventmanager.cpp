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
#include <QDir>
#include <QApplication>
#include <QMessageBox>
#include <QtNetwork/QHostInfo>


namespace TinyOrganizer
{

QList<Event*> EventManager::getEventsBetweenDates(const QDate & dateFirst, const QDate & dateLast) const
{
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

	return result;
}

QList<Event*> EventManager::getEventsForMonth(int year, int month) const
{
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

	return result;
}

QList<Event*> EventManager::getEventsForDate(const QDate & date) const
{
	QList<Event*>::const_iterator it = mEvents.begin();
	QList<Event*>::const_iterator end = mEvents.end();
	QList<Event*> result;
	while(it != end){
		if((*it)->recursOn(date)){
			result.append((*it));
		}
		++it;
	}

	return result;
}

QString EventManager::generateId()
{
    QString hostName = QHostInfo::localHostName();
    qsrand(QDateTime::currentDateTime().toTime_t());
    QString id;
    do
    {
        int randNum = qrand() % 0xffffff;
        id = QString("%1").arg(randNum) + "@" + hostName;
    } while( mUsedIds.contains(id) );

    mUsedIds.insert(id);
    return id;
}

void EventManager::addEvent(Event *e)
{
    if( e->id().size() == 0 )
    {
        QString id = generateId();
        e->setId(id);
    }

    mEvents.append(e);
}

void EventManager::removeEvent(Event *e)
{
	mEvents.removeOne(e);
        mUsedIds.remove(e->id());
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
	if(es.loadEventsFromFile(events)){
		mEvents = events;
		return true;
	}
	return false;
}

QString TinyOrganizer::EventManager::getSettingsDir() const
{
    QString homeDirPath = QDir::homePath();
    QString dot;
#ifdef PLATFORM_UNIX
    dot = ".";
#endif
    homeDirPath += QDir::separator() + dot + QApplication::instance()->applicationName();
    return homeDirPath;
}

QString TinyOrganizer::EventManager::getEventsFilePath() const
{
    return getSettingsDir() + QDir::separator() + "events.xml";
}

bool TinyOrganizer::EventManager::saveEventsToHome()
{
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

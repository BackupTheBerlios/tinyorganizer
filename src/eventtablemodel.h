/*
 * eventtablemodel.h
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
 *   Created on: 2008-09-25
 *   Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

#ifndef EVENTTABLEMODEL_H_
#define EVENTTABLEMODEL_H_

#include <QAbstractTableModel>
#include <QList>

namespace TinyOrganizer
{

class Event;

class EventTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
        EventTableModel();
        virtual ~EventTableModel();

        int rowCount(const QModelIndex & parent = QModelIndex() ) const;
        int columnCount(const QModelIndex & parent = QModelIndex() ) const;
        QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
        QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        void setEvents(const QList<Event*> events);

        void removeEventFromRow(int row);
        void removeAllEvents();



private:
        QList<Event*> mEvents;
};

}

#endif /* EVENTTABLEMODEL_H_ */

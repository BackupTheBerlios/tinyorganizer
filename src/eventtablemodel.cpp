/*
 * eventtablemodel.cpp
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

#include <QDate>
#include <QDebug>

#include "eventtablemodel.h"
#include "calendar-core/event.h"

namespace TinyOrganizer
{

EventTableModel::EventTableModel()
{
	// TODO Auto-generated constructor stub
}

EventTableModel::~EventTableModel()
{
	// TODO Auto-generated destructor stub
}

int EventTableModel::rowCount(const QModelIndex &) const
{
	return mEvents.count();
}

int EventTableModel::columnCount(const QModelIndex &) const
{
	return 3;
}

QVariant EventTableModel::data(const QModelIndex & index, int role) const
{
//	qDebug() << "EventTableModel::data()";
	int row = index.row();
	int column = index.column();
	if( role ==  Qt::DisplayRole )
	{
		if( column == 0 )
		{
			return QVariant(mEvents[row]->startDateTime().time());
		}
		else if( column == 1 )
		{
			return QVariant(mEvents[row]->endDateTime().time());
		}
		else if( column == 2 )
		{
			return QVariant(mEvents[row]->summary());
		}
	}
	else if( role == Qt::ToolTipRole )
	{
		Event * e = mEvents[row];
		QString s = e->startDateTime().time().toString() + " - " + e->endDateTime().time().toString();
		s += "\n" + tr("Summary: ") + e->summary();
		s += "\n" + tr("Location: ") + e->location();
		return QVariant(s);
	}
	return QVariant();
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if( orientation == Qt::Horizontal)
	{
		if( role == Qt::DisplayRole )
		{
			if( section == 0 )
			{
                                return QVariant(tr("Start"));
			}
			else if( section == 1)
			{
				return QVariant(tr("End"));
			}
			else if( section == 2 )
			{
				return QVariant(tr("Summary"));
			}
		}
		return QVariant();
	}
	else
	{
//		return QAbstractTableModel::headerData(section, orientation, role);
		return QVariant();
	}
}

void EventTableModel::setEvents(const QList<Event*> events)
{
	mEvents = events;
	emit layoutChanged();
}

}

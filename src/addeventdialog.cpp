/*
 *   addeventdialog.cpp
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

#include "addeventdialog.h"

namespace TinyOrganizer
{

AddEventDialog::AddEventDialog(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	connectSignals();
}

AddEventDialog::~AddEventDialog()
{

}

void AddEventDialog::setCurrentDate(QDateTime dateTime)
{
	ui.editEventStart->setDateTime(dateTime);
	ui.editEventEnd->setDateTime(dateTime);
	ui.editAllDay->setDate(dateTime.date());
}

bool AddEventDialog::checkDescription()
{
    if(ui.editDescription->toPlainText().trimmed().length() == 0){
        reportError(tr("event description empty"));
        return false;
    }
    return true;
}

bool AddEventDialog::checkDates()
{
    // make the necessary checks
    if(ui.checkAllDay->isChecked()){
        if(ui.editAllDay->date() < QDate::currentDate()){
            reportError(tr("start date before current date."));
            ui.editAllDay->setFocus();
            return false;
        }
    }
    else{
        if(QDate::currentDate() > ui.editEventStart->date()){
            reportError(tr("start date before current date."));
            ui.editEventStart->setFocus();
            return false;
        }
        if(ui.editEventStart->dateTime() > ui.editEventEnd->dateTime()){
            reportError(tr("end date before start date."));
            ui.editEventEnd->setFocus();
            return false;
        }
    }


    return true;
}

void AddEventDialog::performOkClicked()
{
	if( !checkDates() )
	{
		return;
	}

	if( !checkDescription() )
	{
		return;
	}

	if( !this->checkRecurrence() )
	{
		return;
	}

	if( !this->checkReminder())
	{
		return;
	}

	accept();
}

bool AddEventDialog::checkRecurrence()
{
	return true;
}

bool AddEventDialog::allDayEvent() const
{
	return ui.checkAllDay->isChecked();
}

Recurrence::RecurrenceType AddEventDialog::recurrenceType() const
{
	int index = ui.comboRecurrence->currentIndex();

	if( index != 0 )
	{
		if( index == 1 )
		{
			return Recurrence::Daily;
		}
		else if( index == 2)
		{
			return Recurrence::Weekly;
		}
		else if( index == 3)
		{
			return Recurrence::Monthly;
		}
		else if( index == 4 )
		{
			return Recurrence::Yearly;
		}
	}
	return Recurrence::None;
}

QDate AddEventDialog::repeatUntil() const
{
	if( ui.comboRecurrence->currentIndex() != 0)
	{
		return ui.editUntil->date();
	}
	return QDate();
}

QDateTime AddEventDialog::startDate() const
{
	if( ui.checkAllDay->isChecked() )
	{
		QDateTime dateTime;
		dateTime.setDate(ui.editAllDay->date());
		return dateTime;
	}
	return ui.editEventStart->dateTime();
}

QDateTime AddEventDialog::endDate() const
{
	if( ui.checkAllDay->isChecked() )
	{
		QDateTime dateTime;
		dateTime.setDate(ui.editAllDay->date().addDays(1));
		dateTime = dateTime.addSecs(-1);
		return dateTime;
	}
	return ui.editEventEnd->dateTime();
}

QString AddEventDialog::summary() const
{
	return ui.editDescription->toPlainText();
}

QString AddEventDialog::location() const
{
	return ui.editLocatioon->toPlainText();
}

bool AddEventDialog::checkReminder()
{
	return true;
}

void AddEventDialog::connectSignals()
{
	connect(ui.buttonOk, SIGNAL(clicked()), this, SLOT(performOkClicked()));
	connect(ui.comboRecurrence, SIGNAL(currentIndexChanged(int)), this, SLOT(recurrenceComboChanged(int)));
}

void AddEventDialog::recurrenceComboChanged(int index)
{
	if( index > 0 )
	{
		ui.radioUntil->setChecked(true);
		ui.radioUntil->setEnabled(true);
		ui.radioHitCount->setEnabled(true);
		ui.radioAlways->setEnabled(true);
	}
	else
	{
		ui.radioUntil->setEnabled(false);
		ui.radioHitCount->setEnabled(false);
		ui.radioAlways->setEnabled(false);
	}
}

void AddEventDialog::reportError(const QString & msg)
{
	ui.labelError->setText(tr("Error: ") + msg);
}

}

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

AddEventDialog::AddEventDialog(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	connectSignals();
}

AddEventDialog::~AddEventDialog()
{

}

void AddEventDialog::setCurrentDate(QDate date)
{
	mCurrentDate = date;
	ui.editEventStart->setDate(date);
	ui.editEventEnd->setDate(date);
	ui.editAllDay->setDate(date);
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
        if(ui.editAllDay->date() < mCurrentDate){
            reportError(tr("start date before current date."));
            ui.editAllDay->setFocus();
            return false;
        }
    }
    else{
        if(mCurrentDate > ui.editEventStart->date()){
            reportError(tr("start date before current date."));
            ui.editEventStart->setFocus();
            return false;
        }
        if(ui.editEventStart->dateTime() > ui.editEventEnd->dateTime()){
            reportError(tr("end date before start date."));
            ui.editEventStart->setFocus();
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

bool AddEventDialog::checkReminder()
{
	return true;
}

void AddEventDialog::connectSignals()
{
	connect(ui.buttonOk, SIGNAL(clicked()), this, SLOT(performOkClicked()));
}

void AddEventDialog::reportError(const QString & msg)
{
	ui.labelError->setText(tr("Error: ") + msg);
}

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

#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QtGui/QDialog>
#include <QDate>

#include "ui_addeventdialog.h"

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    AddEventDialog(QWidget *parent = 0);
    ~AddEventDialog();

    void setCurrentDate(QDate date);

public slots:
    void performOkClicked();

private:
    void connectSignals();
    void reportError(const QString & msg);
    bool checkDates();
    bool checkDescription();
    bool checkRecurrence();
    bool checkReminder();


private:
    Ui::AddEventDialogClass ui;
    QDate mCurrentDate;
};

#endif // ADDEVENTDIALOG_H

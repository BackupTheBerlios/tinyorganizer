/*
 *   settingsdialog.h
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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SettingsDialog)
public:
    explicit SettingsDialog(QWidget *parent = 0);
    virtual ~SettingsDialog();

    void saveValues();

protected:
    virtual void changeEvent(QEvent *e);

private:
    void setupValues();

private:
    Ui::SettingsDialog *m_ui;
};

#endif // SETTINGSDIALOG_H

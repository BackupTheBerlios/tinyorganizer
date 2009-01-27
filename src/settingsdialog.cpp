/*
 *   settingsdialog.cpp
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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settingsmanager.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SettingsDialog)
{
    m_ui->setupUi(this);

    m_ui->buttonBox->setFocus();

    setupValues();

    SettingsManager::getSingleton().restoreWindow(this);
}

SettingsDialog::~SettingsDialog()
{
    SettingsManager::getSingleton().saveWindow(this);
    delete m_ui;
}

void SettingsDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SettingsDialog::saveValues()
{
    SettingsManager::getSingleton().setValue("MinimizeToTray", m_ui->checkBoxMinimizeToTray->isChecked());
    SettingsManager::getSingleton().setValue("MinimizeOnClose", m_ui->checkBoxCloseMinimizes->isChecked());
}

void SettingsDialog::setupValues()
{
    m_ui->checkBoxMinimizeToTray->setChecked(SettingsManager::getSingleton().getValue("MinimizeToTray").value<bool>());
    m_ui->checkBoxCloseMinimizes->setChecked(SettingsManager::getSingleton().getValue("MinimizeOnClose").value<bool>());
}

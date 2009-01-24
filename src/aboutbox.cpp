/*
 *   aboutbox.cpp
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

#include "aboutbox.h"
#include "ui_aboutbox.h"
#include "main.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutBox)
{
    m_ui->setupUi(this);

    setWindowTitle(QString(tr("About %1")).arg(APPNAME));

    m_ui->mLabelTitle->setText(APPNAME);
    m_ui->mLabelVersion->setText(QString(tr("version: %1")).arg(APPVER));

    // substitute occurence of %1 with address of the website
    m_ui->mLabelDescription->setText(m_ui->mLabelDescription->text().arg(APPWWW));
    if( parent )
    {
        move(parent->pos());
    }
}

AboutBox::~AboutBox()
{
    delete m_ui;
}

void AboutBox::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

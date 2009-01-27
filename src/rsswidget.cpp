/*
 *   rsswidget.cpp
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

#include "rsswidget.h"
#include "ui_rsswidget.h"

RSSWidget::RSSWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::RSSWidget)
{
    m_ui->setupUi(this);
}

RSSWidget::~RSSWidget()
{
    delete m_ui;
}

void RSSWidget::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/*
 *   rsswidget.h
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

#ifndef RSSWIDGET_H
#define RSSWIDGET_H

#include <QtGui/QWidget>

namespace Ui {
    class RSSWidget;
}

class RSSWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(RSSWidget)
public:
    explicit RSSWidget(QWidget *parent = 0);
    virtual ~RSSWidget();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::RSSWidget *m_ui;
};

#endif // RSSWIDGET_H

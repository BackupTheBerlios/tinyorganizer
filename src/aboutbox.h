/*
 *   aboutbox.h
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

#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QtGui/QDialog>

namespace Ui {
    class AboutBox;
}

class AboutBox : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AboutBox)
public:
    explicit AboutBox(QWidget *parent = 0);
    virtual ~AboutBox();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AboutBox *m_ui;
};

#endif // ABOUTBOX_H

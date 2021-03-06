/*
 *   mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void setVisible(bool visible);

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent * e);
    virtual void keyPressEvent(QKeyEvent * e);

signals:
    void hideRequested();

private:
    void setupTrayIcon();

private:
    Ui::MainWindow *m_ui;
    QSystemTrayIcon * trayIcon;
    QMenu menuTrayPopup;
    QPoint pointPrevPosition;
    QIcon iconShow;
    QIcon iconHide;

private slots:
    void on_actionShow_Hide_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_TinyOrganizer_triggered();
    void on_action_Settings_triggered();
    void on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H

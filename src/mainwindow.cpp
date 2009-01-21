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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainWindow),
        trayIcon(0)
{
    m_ui->setupUi(this);
    m_ui->scheduleWidget->setFocus();

    setupTrayIcon();

    // to repair buggy default focus on tab header
    m_ui->scheduleWidget->setFocus();
}

void MainWindow::setupTrayIcon()
{
    if( QSystemTrayIcon::isSystemTrayAvailable() )
    {
        QIcon icon(":/gfx/icons/calendar.png");
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(icon);
        trayIcon->setVisible(true);
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayIcon_activated(QSystemTrayIcon::ActivationReason)));

        menuTrayPopup.addAction(m_ui->actionShow_Hide);
        menuTrayPopup.addAction(m_ui->actionExit);
        trayIcon->setContextMenu(&menuTrayPopup);
    }
}

MainWindow::~MainWindow()
{

    if( trayIcon )
    {
        trayIcon->setVisible(false);
        delete trayIcon;
    }
    delete m_ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionShow_Hide_triggered()
{
    setVisible(!isVisible());
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionImport_triggered()
{

}

void MainWindow::on_actionExport_triggered()
{

}

void MainWindow::on_actionAdd_triggered()
{
    m_ui->scheduleWidget->performAddEvent();
}

void MainWindow::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    if( reason == QSystemTrayIcon::Trigger)
    {
        if( isHidden() )
        {
            setVisible(true);
        }
        else
        {
            setVisible(false);
        }
    }
    else if( reason == QSystemTrayIcon::Context )
    {
        trayIcon->contextMenu()->show();
    }
}

void MainWindow::setVisible(bool visible)
{
    if( visible )
    {
        m_ui->actionShow_Hide->setText(tr("&Hide"));
    }
    else
    {
        m_ui->actionShow_Hide->setText(tr("&Show"));
    }

    if( !visible )
    {
        saveWindowPosition();
    }

    QMainWindow::setVisible(visible);

    if( visible )
    {
        restoreWindowPosition();
    }
}

void MainWindow::saveWindowPosition()
{
    pointPrevPosition = pos();
}

void MainWindow::restoreWindowPosition()
{
    move(pointPrevPosition);
}

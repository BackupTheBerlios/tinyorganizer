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
#include "main.h"
#include "aboutbox.h"
#include "settingsmanager.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QCloseEvent>

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

    SettingsManager::getSingleton().restoreWindow(this);
    connect(this, SIGNAL(hideRequested()), SLOT(hide()), Qt::QueuedConnection);
}

void MainWindow::setupTrayIcon()
{
    if( QSystemTrayIcon::isSystemTrayAvailable() )
    {
        trayIcon = new QSystemTrayIcon();
        trayIcon->setIcon(windowIcon());
        trayIcon->setVisible(true);
        trayIcon->setToolTip(QDate::currentDate().toString(Qt::SystemLocaleLongDate));
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(on_trayIcon_activated(QSystemTrayIcon::ActivationReason)));

        menuTrayPopup.addAction(m_ui->actionShow_Hide);
        menuTrayPopup.addAction(m_ui->actionExit);
        trayIcon->setContextMenu(&menuTrayPopup);
    }
}

MainWindow::~MainWindow()
{
    SettingsManager::getSingleton().saveWindow(this);
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
    case QEvent::WindowStateChange:
        if( SettingsManager::getSingleton()
            .getValue("MinimizeToTray").value<bool>() )
        {
            if( isMinimized() )
            {
                emit hideRequested();
                e->ignore();
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if( SettingsManager::getSingleton().getValue("MinimizeOnClose").value<bool>() )
    {
        setVisible(false);
        e->ignore();
    }
    else
    {
        e->accept();
    }
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
    if( e->key() == Qt::Key_Escape )
    {
        setVisible(false);
    }
    else
    {
        QMainWindow::keyPressEvent(e);
    }
}

void MainWindow::on_actionShow_Hide_triggered()
{
    setVisible(!isVisible());
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit(0);
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

void MainWindow::on_actionAbout_TinyOrganizer_triggered()
{
    AboutBox ab(this);
    ab.exec();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog sd(this);
    if( sd.exec() == QDialog::Accepted )
    {
        sd.saveValues();
    }
}

void MainWindow::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    if( reason == QSystemTrayIcon::Trigger)
    {
        bool hidden = isHidden();
        if( isHidden() && isMinimized() )
        {
            showNormal();
        }
        setVisible(hidden);

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
        m_ui->actionShow_Hide->setIcon(QIcon(":/gfx/icons/minus.png"));
    }
    else
    {
        m_ui->actionShow_Hide->setText(tr("&Show"));
         m_ui->actionShow_Hide->setIcon(QIcon(":/gfx/icons/plus.png"));
    }
    QMainWindow::setVisible(visible);
    if( visible )
    {
        activateWindow();
    }
}


void MainWindow::on_hideRequested()
{
    setVisible(false);
}

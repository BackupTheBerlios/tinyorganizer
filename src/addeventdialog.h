#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QtGui/QDialog>
#include "ui_addeventdialog.h"

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    AddEventDialog(QWidget *parent = 0);
    ~AddEventDialog();

private:
    Ui::AddEventDialogClass ui;
};

#endif // ADDEVENTDIALOG_H

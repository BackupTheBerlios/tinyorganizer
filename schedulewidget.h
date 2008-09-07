#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QtGui/QWidget>
#include "ui_schedulewidget.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    ScheduleWidget(QWidget *parent = 0);
    ~ScheduleWidget();

private:
    Ui::ScheduleWidgetClass ui;
};

#endif // SCHEDULEWIDGET_H

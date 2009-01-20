#ifndef ADDEVENT_H
#define ADDEVENT_H

#include "calendar-core/recurrence.h"

#include <QtGui/QDialog>
#include <QDateTime>

namespace Ui {
    class AddEvent;
}

class AddEvent : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AddEvent)
public:
    explicit AddEvent(QWidget *parent = 0);
    virtual ~AddEvent();

    void setCurrentDate(QDateTime dateTime);

    QDateTime startDate() const;
    QDateTime endDate() const;
    QString description() const;
    QString location() const;
    TinyOrganizer::Recurrence::RecurrenceType recurrenceType() const;
    bool allDayEvent() const;
    QDate repeatUntil() const;

protected:
    virtual void changeEvent(QEvent *e);

private slots:
    void on_comboRecurrence_currentIndexChanged(int);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    bool checkDates();
    bool checkDescription();
    bool checkRecurrence();
    bool checkReminder();
    QDate calculateHitCount() const;
    void reportError(const QString & msg);

private:
    Ui::AddEvent *m_ui;
};

#endif // ADDEVENT_H

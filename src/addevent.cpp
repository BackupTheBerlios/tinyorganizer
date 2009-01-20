#include "addevent.h"
#include "ui_addevent.h"

using namespace TinyOrganizer;

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddEvent)
{
    m_ui->setupUi(this);
}

AddEvent::~AddEvent()
{
    delete m_ui;
}

void AddEvent::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AddEvent::on_comboRecurrence_currentIndexChanged(int index)
{
        if( index > 0 )
        {
                m_ui->radioUntil->setChecked(true);
                m_ui->radioUntil->setEnabled(true);
                m_ui->radioHitCount->setEnabled(true);
                m_ui->radioAlways->setEnabled(true);
        }
        else
        {
                m_ui->radioUntil->setEnabled(false);
                m_ui->radioHitCount->setEnabled(false);
                m_ui->radioAlways->setEnabled(false);
        }
}

void AddEvent::on_buttonBox_accepted()
{
    if( !checkDates() )
        {
                return;
        }

        if( !checkDescription() )
        {
                return;
        }

        if( !this->checkRecurrence() )
        {
                return;
        }

        if( !this->checkReminder())
        {
                return;
        }

        accept();
}

void AddEvent::on_buttonBox_rejected()
{
    reject();
}

void AddEvent::reportError(const QString & msg)
{
    m_ui->labelError->setText(tr("Error: %1").arg(msg));
}

void AddEvent::setCurrentDate(QDateTime dateTime)
{
        m_ui->editEventStart->setDateTime(dateTime);
        m_ui->editEventEnd->setDateTime(dateTime);
        m_ui->editAllDay->setDate(dateTime.date());
        m_ui->editUntil->setDate(dateTime.date());
}

bool AddEvent::checkDescription()
{
    if(m_ui->editDescription->toPlainText().trimmed().length() == 0){
        reportError(tr("event description empty"));
        return false;
    }
    return true;
}

bool AddEvent::checkDates()
{
    // make the necessary checks
    if(m_ui->checkAllDay->isChecked()){
        if(m_ui->editAllDay->date() < QDate::currentDate()){
            reportError(tr("start date before current date."));
            m_ui->editAllDay->setFocus();
            return false;
        }
    }
    else{
        if(QDate::currentDate() > m_ui->editEventStart->date()){
            reportError(tr("start date before current date."));
            m_ui->editEventStart->setFocus();
            return false;
        }
        if(m_ui->editEventStart->dateTime() > m_ui->editEventEnd->dateTime()){
            reportError(tr("end date before start date."));
            m_ui->editEventEnd->setFocus();
            return false;
        }
    }


    return true;
}

bool AddEvent::checkRecurrence()
{
        return true;
}

bool AddEvent::allDayEvent() const
{
        return m_ui->checkAllDay->isChecked();
}

Recurrence::RecurrenceType AddEvent::recurrenceType() const
{
        int index = m_ui->comboRecurrence->currentIndex();

        if( index != 0 )
        {
                if( index == 1 )
                {
                        return Recurrence::Daily;
                }
                else if( index == 2)
                {
                        return Recurrence::Weekly;
                }
                else if( index == 3)
                {
                        return Recurrence::Monthly;
                }
                else if( index == 4 )
                {
                        return Recurrence::Yearly;
                }
        }
        return Recurrence::None;
}

QDate AddEvent::repeatUntil() const
{
        if( m_ui->comboRecurrence->currentIndex() != 0)
        {
                if( m_ui->radioUntil->isChecked() )
                        return m_ui->editUntil->date();
                else if( m_ui->radioHitCount->isChecked() )
                        return calculateHitCount();
                else if( m_ui->radioAlways->isChecked() )
                        return QDate();
        }
        return QDate();
}

QDateTime AddEvent::startDate() const
{
        if( m_ui->checkAllDay->isChecked() )
        {
                QDateTime dateTime;
                dateTime.setDate(m_ui->editAllDay->date());
                return dateTime;
        }
        return m_ui->editEventStart->dateTime();
}

QDateTime AddEvent::endDate() const
{
        if( m_ui->checkAllDay->isChecked() )
        {
                QDateTime dateTime;
                dateTime.setDate(m_ui->editAllDay->date().addDays(1));
                dateTime = dateTime.addSecs(-1);
                return dateTime;
        }
        return m_ui->editEventEnd->dateTime();
}

QString AddEvent::description() const
{
        return m_ui->editDescription->toPlainText();
}

QString AddEvent::location() const
{
        return m_ui->editLocatioon->toPlainText();
}

bool AddEvent::checkReminder()
{
        return true;
}

QDate AddEvent::calculateHitCount() const
{
    // TODO: implement the method
    return QDate();
}

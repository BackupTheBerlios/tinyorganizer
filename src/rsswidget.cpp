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

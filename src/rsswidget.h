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

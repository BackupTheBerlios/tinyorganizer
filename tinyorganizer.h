#ifndef TINYORGANIZER_H
#define TINYORGANIZER_H

#include <QtGui/QMainWindow>
#include "ui_tinyorganizer.h"

class TinyOrganizer : public QMainWindow
{
    Q_OBJECT

public:
    TinyOrganizer(QWidget *parent = 0);
    ~TinyOrganizer();

private:
    Ui::TinyOrganizerClass ui;
};

#endif // TINYORGANIZER_H

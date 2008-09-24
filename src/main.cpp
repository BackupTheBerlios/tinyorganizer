#include "tinyorganizer.h"
#include "addeventdialog.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TinyOrganizer w;
    w.show();
    return a.exec();
}

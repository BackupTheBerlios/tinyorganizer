TEMPLATE = app
TARGET = ../TinyOrganizer
QT += core \
    gui \
    xml
HEADERS += addeventdialog.h \
    schedulewidget.h \
    tinyorganizer.h
SOURCES += addeventdialog.cpp \
    main.cpp \
    schedulewidget.cpp \
    tinyorganizer.cpp
FORMS += addeventdialog.ui \
    schedulewidget.ui \
    tinyorganizer.ui
RESOURCES += tinyorganizer.qrc

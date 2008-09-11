TEMPLATE = app
TARGET = ../TinyOrganizer
QT += core \
    gui \
    xml
HEADERS += calendar-core/reminder.h \
    calendar-core/eventmanager.h \
    calendar-core/event.h \
    addeventdialog.h \
    schedulewidget.h \
    tinyorganizer.h
SOURCES += calendar-core/reminder.cpp \
    calendar-core/eventmanager.cpp \
    calendar-core/event.cpp \
    addeventdialog.cpp \
    main.cpp \
    schedulewidget.cpp \
    tinyorganizer.cpp
FORMS += addeventdialog.ui \
    schedulewidget.ui \
    tinyorganizer.ui
RESOURCES += tinyorganizer.qrc

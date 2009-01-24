TEMPLATE = app
TARGET = ../TinyOrganizer

#DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
QT += core \
    gui \
    xml \
    network
HEADERS += calendar-core/eventstore.h \
    eventtablemodel.h \
    calendar-core/singleton.h \
    calendar-core/recurrence.h \
    calendar-core/event.h \
    calendar-core/eventmanager.h \
    calendar-core/reminder.h \
    mainwindow.h \
    schedulewidget.h \
    addevent.h \
    rsswidget.h \
    aboutbox.h \
    settingsmanager.h \
    main.h \
    settingsdialog.h
SOURCES += calendar-core/eventstore.cpp \
    eventtablemodel.cpp \
    calendar-core/recurrence.cpp \
    calendar-core/event.cpp \
    calendar-core/eventmanager.cpp \
    calendar-core/reminder.cpp \
    main.cpp \
    mainwindow.cpp \
    schedulewidget.cpp \
    addevent.cpp \
    rsswidget.cpp \
    aboutbox.cpp \
    settingsmanager.cpp \
    settingsdialog.cpp

# ../../../qtcreator-0.9.2/bin/gdbmacros/gdbmacros.cpp
FORMS += aboutbox.ui \
    addevent.ui \
    mainwindow.ui \
    rsswidget.ui \
    mainwindow.ui \
    schedulewidget.ui \
    addevent.ui \
    rsswidget.ui \
    aboutbox.ui \
    settingsdialog.ui
RESOURCES += tinyorganizer.qrc
TRANSLATIONS += en_EN.ts

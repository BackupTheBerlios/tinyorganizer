TEMPLATE = app
TARGET = TinyOrganizer
QT += core \
    gui \
    xml
HEADERS += schedulewidget.h \
    tinyorganizer.h
SOURCES += schedulewidget.cpp \
    main.cpp \
    tinyorganizer.cpp
FORMS += schedulewidget.ui \
    tinyorganizer.ui
RESOURCES += tinyorganizer.qrc

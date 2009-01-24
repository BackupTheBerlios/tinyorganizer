
find_package(Qt4 REQUIRED)

set(SRCS
    calendar-core/event.cpp
    calendar-core/eventstore.cpp
    calendar-core/reminder.cpp
    calendar-core/eventmanager.cpp
    calendar-core/recurrence.cpp
    eventtablemodel.cpp
    addevent.cpp
    schedulewidget.cpp
    mainwindow.cpp
    main.cpp
    settingsmanager.cpp
    )

set(MOC_HDRS 
    addevent.h
    schedulewidget.h
    mainwindow.h
    )
 
set(UIS
    addevent.ui
    schedulewidget.ui
    mainwindow.ui
    )

set(RCS
    tinyorganizer.qrc
    )
    
include( ${QT_USE_FILE} )
 
QT4_ADD_RESOURCES(RCS_SRCS ${RCS})
QT4_WRAP_UI(UI_HDRS ${UIS})
QT4_WRAP_CPP(MOC_SRCS ${MOC_HDRS})

add_definitions(-DQT_NO_DEBUG_OUTPUT)
 
include_directories(${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
 
add_executable(tinyorganizer ${SRCS} ${MOC_SRCS} ${RCS_SRCS} ${UI_HDRS})
 
install(TARGETS tinyorganizer DESTINATION bin)
 
target_link_libraries(tinyorganizer ${QT_LIBRARIES} QtXml QtNetwork)

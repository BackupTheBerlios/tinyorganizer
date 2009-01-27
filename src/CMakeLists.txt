
find_package(Qt4 REQUIRED)

set(SRCS
    calendar-core/event.cpp
    calendar-core/eventstore.cpp
    calendar-core/reminder.cpp
    calendar-core/eventmanager.cpp
    calendar-core/recurrence.cpp
    eventtablemodel.cpp
    aboutbox.cpp
    addevent.cpp
    schedulewidget.cpp
    mainwindow.cpp
    main.cpp
    settingsmanager.cpp
    settingsdialog.cpp
    )

set(MOC_HDRS 
    addevent.h
    aboutbox.h
    schedulewidget.h
    mainwindow.h
    settingsdialog.h
    )
 
set(UIS
    addevent.ui
    aboutbox.ui
    schedulewidget.ui
    mainwindow.ui
    settingsdialog.ui
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
 
install(TARGETS tinyorganizer 
        DESTINATION bin 
        PERMISSIONS 
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE)
 
target_link_libraries(tinyorganizer ${QT_LIBRARIES} QtXml QtNetwork)


find_package(Qt4 REQUIRED)

set(SRCS
    calendar-core/event.cpp
    calendar-core/reminder.cpp
    calendar-core/eventmanager.cpp
    calendar-core/recurrence.cpp
    addeventdialog.cpp
    schedulewidget.cpp
    tinyorganizer.cpp
    main.cpp
    )

set(MOC_HDRS 
    addeventdialog.h
    schedulewidget.h
    tinyorganizer.h
    )
 
set(UIS
    addeventdialog.ui
    schedulewidget.ui
    tinyorganizer.ui
    )

set(RCS
    tinyorganizer.qrc
    )
    
include( ${QT_USE_FILE} )
 
QT4_ADD_RESOURCES(RCS_SRCS ${RCS})
QT4_WRAP_UI(UI_HDRS ${UIS})
QT4_WRAP_CPP(MOC_SRCS ${MOC_HDRS})
 
include_directories(${CMAKE_BINARY_DIR})
 
add_executable(TinyOrganizer ${SRCS} ${MOC_SRCS} ${RCS_SRCS} ${UI_HDRS})
 
install(TARGETS TinyOrganizer DESTINATION bin)
 
target_link_libraries(TinyOrganizer ${QT_LIBRARIES})

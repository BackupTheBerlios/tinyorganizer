TEMPLATE = subdirs

win32 {
    DEFINES += PLATFORM_WIN32
}

unix {
    DEFINES += PLATFORM_UNIX
}

print($${DEFINES})

SUBDIRS += \
	src


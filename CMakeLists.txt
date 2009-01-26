cmake_minimum_required(VERSION 2.6)

project(tinyorganizer)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)


# configure CPack
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "tinyorganizer")
SET(CPACK_PACKAGE_VENDOR "Dariusz Gadomski <dgadomski@gmail.com>")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  #SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\TinyOrganizer.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} TinyOrganizer")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.tinyorganizer.org")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.tinyorganizer.org")
  SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/tinyorganizer")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)

# configure cpack deb generator
if( UNIX )
    set(CPACK_DEBIAN_PACKAGE_NAME "tinyorganizer")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dariusz Gadomski <dgadomski@gmail.com>")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Bla bla bla bla")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
endif( UNIX )
include(CPack)

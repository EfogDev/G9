cmake_minimum_required(VERSION 2.8.11)
project(G9)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5X11Extras REQUIRED)
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

IF (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Build/Windows)
ELSE()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Build/Linux)
ENDIF()

set(HEADER_FILES
    const.h
    init.h
    screenshoter.h
    popupwindow.h
    settingswindow.h
    qtransparentlabel.h

    qxt/qxtglobalshortcut.h
    qxt/qxtglobalshortcut_p.h)

set(SRC_LIST
        main.cpp
    	init.cpp
        screenshoter.cpp
        popupwindow.cpp
        settingswindow.cpp
        qtransparentlabel.cpp

        qxt/qxtglobalshortcut.cpp)

IF (WIN32)
    set(OS_SRC qxt/qxtglobalshortcut_win.cpp)
ELSE()
    set(OS_SRC qxt/qxtglobalshortcut_x11.cpp)
ENDIF()

set(RESOURCES resources.qrc)
QT5_ADD_RESOURCES(RESOURCES_RCC ${RESOURCES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(LIB_LIST
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::Network
	Qt5::X11Extras
	X11
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${OS_SRC} ${RESOURCES_RCC})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})

execute_process(
	COMMAND ${CMAKE_COMMAND} -E remove_directory bin/res
	COMMAND ${CMAKE_COMMAND} -E copy_directory res bin/res
)

IF (WIN32)

ELSE()
    include_directories(
        /usr/include/qt5/QtGui/5.2.1/QtGui
    )
ENDIF()
#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T11:23:35
#
#-------------------------------------------------

QT       += core gui multimedia network x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = G9
TEMPLATE = app

SOURCES += main.cpp\
        screenshoter.cpp \
        qtransparentlabel.cpp \
        popupwindow.cpp \
        settingswindow.cpp \
        init.cpp \
        qcustomkeysequenceedit.cpp

HEADERS  += \
            screenshoter.h \
            qtransparentlabel.h \
            popupwindow.h \
            settingswindow.h \
            const.h \
            init.h \
            qcustomkeysequenceedit.h

CONFIG += C++11

RESOURCES += \
    resources.qrc

DISTFILES += \
    popup.qss

unix:!macx {
    INCLUDEPATH += /usr/include/qt/QtGui/5.4.2/QtGui
    LIBS += -lX11
    SOURCES += qxt/qxtglobalshortcut.cpp
    SOURCES += qxt/qxtglobalshortcut_x11.cpp
    HEADERS += qxt/qxtglobalshortcut.h
}

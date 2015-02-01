#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T11:23:35
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = G9
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        screenshoter.cpp \
        qtransparentlabel.cpp \
    popupwindow.cpp

HEADERS  += mainwindow.h \
            screenshoter.h \
            qtransparentlabel.h \
    popupwindow.h

CONFIG += C++11

RESOURCES += \
    resources.qrc

DISTFILES += \
    popup.qss

#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T11:23:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gran
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        screenshoter.cpp \
        qtransparentlabel.cpp

HEADERS  += mainwindow.h \
            screenshoter.h \
            qtransparentlabel.h

CONFIG += C++11

RESOURCES += images.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2012-03-06T09:48:29
#
#-------------------------------------------------

QT       += core gui sql

TARGET = cannabis-qt
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/databasemanager.cpp \
    src/chooseoption.cpp

HEADERS  += src/mainwindow.h \
    src/databasemanager.h \
    src/chooseoption.h

FORMS    += src/mainwindow.ui

RESOURCES += \
    cannabis-qt.qrc
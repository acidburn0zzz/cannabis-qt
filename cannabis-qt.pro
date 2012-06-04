#-------------------------------------------------
#
# Project created by QtCreator 2012-03-06T09:48:29
#
#-------------------------------------------------

QT       += core gui sql svg

TARGET = cannabis-qt
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/databasemanager.cpp \
    src/chooseoption.cpp \
    src/members.cpp \
    src/cannabis.cpp \
    src/others.cpp \
    src/cashcontrol.cpp \
    src/cans.cpp \
    src/mycheckboxdelegate.cpp \
    src/mydateeditdelegate.cpp \
    src/cashcontrolmodel.cpp \
    src/cansmodel.cpp \
    src/addmember.cpp \
    src/about.cpp

HEADERS  += src/mainwindow.h \
    src/databasemanager.h \
    src/chooseoption.h \
    src/members.h \
    src/cannabis.h \
    src/others.h \
    src/cashcontrol.h \
    src/cans.h \
    src/mycheckboxdelegate.h \
    src/mydateeditdelegate.h \
    src/cashcontrolmodel.h \
    src/cansmodel.h \
    src/constants.h \
    src/addmember.h \
    src/about.h

RESOURCES += \
    cannabis-qt.qrc \
    elementary.qrc

config += console

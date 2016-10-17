#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T14:40:41
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AR600E_Shell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Transiver.cpp \
    SettingStorage.cpp \
    Dispatcher.cpp \
    Packet.cpp \
    PacketManager.cpp \
    Parameter.cpp \
    myTimer.cpp

HEADERS  += mainwindow.h \
    Transiver.h \
    SettingStorage.h \
    Dispatcher.h \
    Packet.h \
    PacketManager.h \
    Parameter.h \
    myTimer.h

FORMS    += mainwindow.ui

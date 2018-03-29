#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T14:40:41
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4):
{
    QT += widgets
    QT += serialport
}

TARGET = AR600E_Shell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        myTimer.cpp \
    audiosocket.cpp \
    audiocommandreceiver.cpp \
    pultreceiver.cpp \
    PackageBuilder.cpp

HEADERS  += mainwindow.h \
    myTimer.h \
    audiosocket.h \
    audiocommandreceiver.h \
    pultreceiver.h \
    PackageBuilder.h

FORMS    += mainwindow.ui

LIBS += -lws2_32

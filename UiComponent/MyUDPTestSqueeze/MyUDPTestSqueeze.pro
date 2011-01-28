#-------------------------------------------------
#
# Project created by QtCreator 2010-10-08T12:15:16
#
#-------------------------------------------------

QT       += core gui network

TARGET = MyUDPSqueeze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h  

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xed751897
    TARGET.CAPABILITY += NetworkServices LocalServices Location

}

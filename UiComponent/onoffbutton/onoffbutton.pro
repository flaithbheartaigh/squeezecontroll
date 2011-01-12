#-------------------------------------------------
#
# Project created by QtCreator 2011-01-03T16:55:18
#
#-------------------------------------------------

QT       += core gui

TARGET = onoffbutton
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    onoffbutton.cpp \
    buttonpanel.cpp
    volumecontrol.cpp

HEADERS  += widget.h \
    onoffbutton.h \
    buttonpanel.h
    volumecontrol.h

FORMS    += widget.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xe6d7e514
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    image.qrc

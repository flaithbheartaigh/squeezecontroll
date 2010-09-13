# -------------------------------------------------
# Project created by QtCreator 2010-01-08T21:41:48
# -------------------------------------------------
QT += network
QT += sql
TARGET = SqueezeRemote
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    databasehandler.cpp \
    squeezecli.cpp \
    squeezeboxhelper.cpp \
    squeezelistner.cpp \
    getalbumcover.cpp \
    flickable.cpp
HEADERS += mainwindow.h \
    databasehandler.h \
    database_struct.h \
    squeezecli.h \
    squeezeboxhelper.h \
    SqueezeStatus.h \
    squeezelistner.h \
    getalbumcover.h \
    sym_iap_util.h \
    SqueezePlayer.h \
    SqueezeSearch.h \
    flickable.h \
    kineticlist.h
FORMS += mainwindow.ui
RESOURCES += icon.qrc
symbian { 
    # TARGET.UID3 = 0xA000A638
    include(symbianpkgrules.pri)
    HEADERS += sym_iap_util.h
    INCLUDEPATH += $$APP_LAYER_SYSTEMINCLUDE
    TARGET.CAPABILITY = "NetworkServices ReadUserData WriteUserData"
    LIBS += -lesock \
        -lcommdb \
        -linsock \
        -lPlatformEnv # For IAP selection
}

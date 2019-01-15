QT -= gui

CONFIG += c++11
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    devicetype.cpp \
    smartdevice.cpp

HEADERS += \
    devicetype.h \
    smartdevice.h

! include( ../libs.pri ) {
    error( "Couldn't find the libs.pri file!" )
}

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

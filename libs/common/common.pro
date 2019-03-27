QT -= gui
QT += mqtt

CONFIG += c++11
CONFIG -= app_bundle debug_and_release debug_and_release_target

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    devicetype.cpp \
    smartdevice.cpp \
    mqttclient.cpp

HEADERS += \
    devicetype.h \
    smartdevice.h \
    mqttclient.h

! include( ../libs.pri ) {
    error( "Couldn't find the libs.pri file!" )
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

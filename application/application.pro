QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    smartdevice.h \
    smartdevicesmodel.h \
    globalproperties.h

SOURCES += \
        main.cpp \
    smartdevice.cpp \
    smartdevicesmodel.cpp \
    globalproperties.cpp

RESOURCES += \
        res/res.qrc

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

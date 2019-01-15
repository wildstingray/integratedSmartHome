QT += gui quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    smartdevicesmodel.cpp \
    globalproperties.cpp

HEADERS += \
    smartdevicesmodel.h \
    globalproperties.h

RESOURCES += \
        res/res.qrc

INCLUDEPATH += ../libs/common

LIBS += \
    -L../libs/common -lcommon

# Need to add the library path to "LD_LIBRARY_PATH" environment variable

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

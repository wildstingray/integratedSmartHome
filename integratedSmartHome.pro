TEMPLATE = subdirs

SUBDIRS += \
    libs \
    application

application.depends = libs

CONFIG += ordered

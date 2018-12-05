TEMPLATE = subdirs

SUBDIRS += \
    application \
    libs \

application.depends = libs

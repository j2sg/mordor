######################################################################
# Automatically generated by qmake (3.0) mi�. may. 25 23:03:13 2016
######################################################################

TEMPLATE = app
TARGET = bot
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

QT += network xml

DEPENDPATH += . include src
INCLUDEPATH += . include ../core/include

# Input
SOURCES += src/main.cpp \
    src/botmanager.cpp \
    src/storagemanager.cpp

HEADERS += \
    include/botmanager.h \
    include/storagemanager.h \
    include/global.h

LIBS += -L../core -lcore -lqxmpp

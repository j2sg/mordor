######################################################################
# Automatically generated by qmake (3.0) dom. jun. 19 18:28:57 2016
######################################################################

TEMPLATE = lib
CONFIG += staticlib
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

QT += network xml

DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += include/attack.h \
           include/bot.h \
           include/command.h \
           include/types.h \
           include/xmppclient.h

SOURCES += src/attack.cpp src/bot.cpp src/xmppclient.cpp

LIBS += -lqxmpp

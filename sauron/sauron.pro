######################################################################
# Automatically generated by qmake (2.01a) s�b jun 4 23:04:36 2016
######################################################################

TEMPLATE = app
TARGET = sauron
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

QT += widgets network xml

DEPENDPATH += . include src
win32: INCLUDEPATH += . include ../core/include ../qxmpp/include
else:unix: INCLUDEPATH += . include ../core/include

HEADERS += \
    include/mainwindow.h \
    include/connectdialog.h \
    include/centralwidget.h \
    include/global.h \
    include/botnetmodel.h

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/connectdialog.cpp \
    src/centralwidget.cpp \
    src/botnetmodel.cpp

RESOURCES += \
    resources/sauron.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../core/release/ -lmordorcore0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../core/debug/ -lmordorcore0
else:unix: LIBS += -L$$PWD/../core/ -lmordorcore

win32: LIBS += -L../qxmpp/lib -lqxmpp0
else:unix: LIBS += -lqxmpp

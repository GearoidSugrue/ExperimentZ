#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T20:15:55
#
#-------------------------------------------------

QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExperimentZ
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    setup.cpp \
    room.cpp \
    qtevent.cpp \
    item.cpp \
    endscreen.cpp \
    character.cpp \
    battlewindow.cpp \
    glwidget.cpp \
    glwidget2.cpp \
    winscreen.cpp

HEADERS  += \
    mainwindow.h \
    setup.h \
    room.h \
    qtevent.h \
    item.h \
    endscreen.h \
    character.h \
    battlewindow.h \
    glwidget.h \
    glwidget2.h \
    winscreen.h

FORMS    += \
    mainwindow.ui \
    qtevent.ui \
    endscreen.ui \
    battlewindow.ui \
    winscreen.ui

OTHER_FILES += \
    ExperimentZ.pro.user

RESOURCES += \
    textFiles.qrc

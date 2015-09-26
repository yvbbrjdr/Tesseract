#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T22:50:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tesseract
TEMPLATE = app


SOURCES += main.cpp\
    tesseractwidget.cpp \
    World.cpp \
    Coordinate.cpp \
    Block.cpp \
    Player.cpp \
    Sound.cpp \
    GameThread.cpp \
    PluginManager.cpp \
    Plugin.cpp

HEADERS  +=     World.h \
    tesseractwidget.h \
    Sound.h \
    PluginManager.h \
    Plugin.h \
    Player.h \
    GameThread.h \
    Coordinate.h \
    Block.h

FORMS    += tesseractwidget.ui

#-------------------------------------------------
#
# Additional Libraries added by yvbbrjdr
#
#-------------------------------------------------

QT += opengl

QT += network

LIBS += -lbass -lGL -lGLU

RC_FILE += Icon.rc

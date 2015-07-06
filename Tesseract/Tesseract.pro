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
        tesseractwidget.cpp

HEADERS  += tesseractwidget.h \
    World.h \
    Player.h \
    GLFuncs.h \
    Coordinate.h \
    Block.h \
    ALFuncs.h

FORMS    += tesseractwidget.ui

#-------------------------------------------------
#
# Additional Libraries added by yvbbrjdr
#
#-------------------------------------------------

QT += opengl

LIBS += -lopenal -lalut -lGLU

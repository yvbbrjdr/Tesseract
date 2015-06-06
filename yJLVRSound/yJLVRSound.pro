#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T13:22:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yJLVRSound
TEMPLATE = app


SOURCES += main.cpp\
        yjlvrsoundwidget.cpp

HEADERS  += yjlvrsoundwidget.h

FORMS    +=

#-------------------------------------------------
#
# Additional Libraries added by yvbbrjdr
#
#-------------------------------------------------

QT += opengl

LIBS += -lopenal -lalut

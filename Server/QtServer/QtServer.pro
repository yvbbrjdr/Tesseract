#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T11:46:35
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QtServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    listener.cpp \
    broadcast.cpp

HEADERS += \
    afx.h \
    listener.h \
    broadcast.h

#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T17:47:54
#
#-------------------------------------------------

QT += network

TARGET = UserControl

TEMPLATE = lib

CONFIG += plugin

SOURCES += UserControl.cpp \
    ../../Tesseract/Plugin.cpp \
    ../../Tesseract/Coordinate.cpp \
    ../../Tesseract/Player.cpp

HEADERS += UserControl.h \
    ../../Tesseract/Plugin.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/Player.h

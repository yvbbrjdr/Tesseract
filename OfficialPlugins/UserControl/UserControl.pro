#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T17:47:54
#
#-------------------------------------------------

QT += network widgets

TARGET = UserControl

TEMPLATE = lib

CONFIG += plugin

SOURCES += UserControl.cpp \
    ../../Tesseract/Plugin.cpp \
    ../../Tesseract/Coordinate.cpp \
    ../../Tesseract/Player.cpp \
    ../../Tesseract/World.cpp \
    ../../Tesseract/Socket.cpp \
    ../../Tesseract/Server.cpp \
    ../../Tesseract/Version.cpp

HEADERS += UserControl.h \
    ../../Tesseract/Plugin.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/Player.h \
    ../../Tesseract/World.h \
    ../../Tesseract/Socket.h \
    ../../Tesseract/Server.h \
    ../../Tesseract/Version.h

#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T07:12:03
#
#-------------------------------------------------
QT += network

TARGET += BasicDrawingElements

TEMPLATE = lib

CONFIG += plugin

SOURCES += BasicDrawingElements.cpp \
    ../../Tesseract/World.cpp \
    ../../Tesseract/Sound.cpp \
    ../../Tesseract/Plugin.cpp \
    ../../Tesseract/Player.cpp \
    ../../Tesseract/Coordinate.cpp \
    ../../Tesseract/Block.cpp

HEADERS += BasicDrawingElements.h \
    ../../Tesseract/World.h \
    ../../Tesseract/Sound.h \
    ../../Tesseract/Plugin.h \
    ../../Tesseract/Player.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/Block.h

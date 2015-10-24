#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T07:12:03
#
#-------------------------------------------------

QT += network

TARGET = BasicDrawingElements

TEMPLATE = lib

CONFIG += plugin

SOURCES += BasicDrawingElements.cpp \
    ../../Tesseract/Plugin.cpp \
    ../../Tesseract/Coordinate.cpp \
    ../../Tesseract/World.cpp

HEADERS += BasicDrawingElements.h \
    ../../Tesseract/Plugin.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/World.h

win32: LIBS += -lopengl32 -lglu32

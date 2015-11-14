#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T17:47:54
#
#-------------------------------------------------

QT += network

TARGET = VOIP

TEMPLATE = lib

CONFIG += plugin

SOURCES += VOIP.cpp \
    ../../Tesseract/Plugin.cpp \
    ../../Tesseract/Version.cpp

HEADERS += VOIP.h \
    ../../Tesseract/Plugin.h \
    ../../Tesseract/Version.h

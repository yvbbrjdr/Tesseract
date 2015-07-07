#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T13:01:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TesseractServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../../Tesseract/Block.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/Player.h \
    ../../Tesseract/World.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Additional Libraries added by yvbbrjdr
#
#-------------------------------------------------

QT += network

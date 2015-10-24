#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T07:12:03
#
#-------------------------------------------------

QT += network widgets

TARGET = MusicPlayer

TEMPLATE = lib

CONFIG += plugin

SOURCES += MusicPlayer.cpp \
    ../../Tesseract/Plugin.cpp \
    ControllerStatus.cpp \
    SpinnerStatus.cpp \
    ../../Tesseract/Coordinate.cpp \
    ../../Tesseract/Block.cpp \
    ../../Tesseract/Player.cpp \
    ../../Tesseract/Server.cpp \
    ../../Tesseract/Socket.cpp \
    ../../Tesseract/Sound.cpp \
    ../../Tesseract/World.cpp

HEADERS += MusicPlayer.h \
    ../../Tesseract/Plugin.h \
    ControllerStatus.h \
    SpinnerStatus.h \
    ../../Tesseract/Coordinate.h \
    ../../Tesseract/Block.h \
    ../../Tesseract/Player.h \
    ../../Tesseract/Server.h \
    ../../Tesseract/Socket.h \
    ../../Tesseract/Sound.h \
    ../../Tesseract/World.h

win32: LIBS += -lbass -lbassenc

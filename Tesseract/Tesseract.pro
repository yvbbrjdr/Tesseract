#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T22:50:59
#
#-------------------------------------------------

QT       += core gui

TARGET = Tesseract
TEMPLATE = app


SOURCES += main.cpp\
    tesseractwidget.cpp \
    World.cpp \
    Coordinate.cpp \
    Block.cpp \
    Player.cpp \
    Sound.cpp \
    PluginManager.cpp \
    Plugin.cpp \
    GameThread.cpp \
    Server.cpp \
    Socket.cpp \
    loginwidget.cpp \
    serverwidget.cpp \
    Version.cpp

HEADERS  +=     World.h \
    tesseractwidget.h \
    Sound.h \
    PluginManager.h \
    Plugin.h \
    Player.h \
    Coordinate.h \
    Block.h \
    GameThread.h \
    Server.h \
    Socket.h \
    loginwidget.h \
    serverwidget.h \
    Version.h

FORMS    += tesseractwidget.ui \
    loginwidget.ui \
    serverwidget.ui

#-------------------------------------------------
#
# Additional Libraries added by yvbbrjdr
#
#-------------------------------------------------

QT += opengl

QT += network

unix: LIBS += -lbass -lGL -lGLU -lbassenc

win32: LIBS += -lbass -lopengl32 -lglu32 -lbassenc

RC_FILE += Icon.rc

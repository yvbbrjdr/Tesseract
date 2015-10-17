/*
This file is part of the source code of Tesseract.
Tesseract is a block-based 3D VR Engine.

Copyright (C) 2015  yvbbrjdr

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef TESSERACTWIDGET_H
#define TESSERACTWIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <bass.h>
#include <QTimer>
#include <QWheelEvent>
#include "Coordinate.h"
#include "GameThread.h"
#include "Socket.h"
#include <cstdio>

class PluginManager;

namespace Ui {
    class TesseractWidget;
}

class TesseractWidget : public QGLWidget {
    Q_OBJECT

public:
    explicit TesseractWidget(Socket*,int,QString,QGLWidget *parent = 0);
    ~TesseractWidget();

public slots:
    void DrawScene();
    void Log(const QString &s);
    void releaseMouse();
    void trackMouse();
    void recvVariantMap(int,QString,quint16,const QVariantMap&);
    void sockDisconnect(int,QString,quint16);
    void renderText2D(Coordinate,const QString&);
    void renderText3D(Coordinate,const QString&,int);

public:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void resizeGL(int,int);
    void mousePressEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void DrawBlock(Bnode,int);
    void SetColor(Coordinate);
    void DrawPlayer(Player);
    World *TheWorld;
    bool KeyStatus[128],mousetracked;
    PluginManager *PM;
    Socket *TheSocket;

private:
    Ui::TesseractWidget *ui;
    GameThread *gt;
    QTimer *GLTimer;
    bool creatingblock;
    double aspect;
    Coordinate tempc;
    QString currentblocktype;
};

#include "PluginManager.h"

#endif // TESSERACTWIDGET_H

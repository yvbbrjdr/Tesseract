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

#ifndef WORLD_H
#define WORLD_H

#include "Block.h"
#include <QMap>
#include <QVector>
#include <QObject>
#include <QKeyEvent>
#include "Player.h"
#include "Socket.h"

class World : public QObject {
    Q_OBJECT
public:
    Coordinate Size;
    QMap<QString,Block>BlockTypes;
    QMap<int,Bnode>Blocks;
    QMap<int,Player>Players;
    QMap<int,Player>::iterator Myself;
    bool RegisterBlock(Block _BlockType);
    bool InBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position);
    QVector<QMap<int,Bnode>::iterator> InBlock(Coordinate Position);
    double ThroughBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position1,Coordinate Position2);
    QVector<QMap<int,Bnode>::iterator> ThroughBlock(Coordinate Position1, Coordinate Position2);

signals:
    void drawBlockSignal(Bnode&,bool&);
    void drawBeginSignal();
    void drawDoneSignal();
    void keyPressSignal(QKeyEvent&);
    void keyReleaseSignal(QKeyEvent&);
    void blockCreateSignal(Bnode&);
    void blockDestroySignal(Bnode&);
    void log(QString);
    void releaseMouse();
    void trackMouse();
    void helpSignal();
    void processSignal(QVector<QString>&);
    void sendCommand(QVector<QString>&);
    void renderText2D(Coordinate,const QString&);
    void renderText3D(Coordinate,const QString&,int);
};

#endif // WORLD_H

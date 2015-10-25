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

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "../../Tesseract/Plugin.h"
#include "../../Tesseract/Sound.h"
#include <cmath>
#include <QVector>
#include <QTimer>
#include <QFileDialog>
#include "SpeakerStatus.h"
#include "ControllerStatus.h"
#include "SpinnerStatus.h"
#include "FFTStatus.h"
#include <QByteArray>

class MusicPlayer:public QObject,public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MusicPlayer")
    Q_INTERFACES(Plugin)

private:
    int SelectedBlock;
    QVector<int>Spinners;
    QVector<int>Controllers;
    QVector<int>FFTs;
    QTimer *Timer;
    World *TheWorld;
    Socket *TheSocket;
    Server *TheServer;

public:
    MusicPlayer();
    void clientLoad(World*,Socket*);
    void serverLoad(World*,Server*);

public slots:
    void keyPressEvent(QKeyEvent&);
    void drawBlockEvent(QMap<int,Bnode>::iterator,bool&);
    void clientBlockCreateEvent(QMap<int,Bnode>::iterator);
    void blockDestroyEvent(QMap<int,Bnode>::iterator);
    void clientRecvVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void delta();
    void recvEncode(int,const void*,DWORD);

    void serverBlockCreateEvent(QMap<int,Bnode>::iterator);
    void serverRecvVariantMap(const int,const QString&,const quint16,const QVariantMap&);
};

#endif // MUSICPLAYER_H

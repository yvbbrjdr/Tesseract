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

#include "GameThread.h"

GameThread::GameThread(World *_TheWorld,bool *_KeyStatus,Socket *_TheSocket) {
    TheWorld=_TheWorld;
    KeyStatus=_KeyStatus;
    TheSocket=_TheSocket;
    Cycle=0;
}

void GameThread::run() {
    while (1) {
        if (KeyStatus['w'])
            TheWorld->Myself->Go(.1,0,0);
        if (KeyStatus['a'])
            TheWorld->Myself->Go(0,.1,0);
        if (KeyStatus['s'])
            TheWorld->Myself->Go(-.1,0,0);
        if (KeyStatus['d'])
            TheWorld->Myself->Go(0,-.1,0);
        if (KeyStatus['x'])
            TheWorld->Myself->Go(0,0,.1);
        if (KeyStatus['z'])
            TheWorld->Myself->Go(0,0,-.1);
        Sound::SetListenerValues(TheWorld->Myself->Position,TheWorld->Myself->EyeVector,TheWorld->Myself->HeadVector);
        if (Cycle%10==0){
            QVector<QMap<int,Bnode>::iterator> v=TheWorld->ThroughBlock(TheWorld->Myself->Position,TheWorld->Myself->LookAt);
            for (QMap<int,Bnode>::iterator it=TheWorld->Blocks.begin();it!=TheWorld->Blocks.end();++it)
                it->PointedAt=0;
            for (int i=0;i<v.size();++i)
                v[i]->PointedAt=1;
            QVariantMap qvm;
            qvm.insert("type","mvuser");
            qvm.insert("x",TheWorld->Myself->Position.x);
            qvm.insert("y",TheWorld->Myself->Position.y);
            qvm.insert("z",TheWorld->Myself->Position.z);
            emit TheSocket->sendVariantMap(qvm,-1);
        }
        QTime dieTime=QTime::currentTime().addMSecs(10);
        while (QTime::currentTime()<dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ++Cycle;
    }
}

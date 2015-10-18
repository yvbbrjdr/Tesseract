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

#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    Name="MusicPlayer1.0";
    Essential=1;
    SelectingObject=NULL;
}

void MusicPlayer::clientLoad(World *w,Socket*) {
    TheWorld=w;
    w->RegisterBlock(Block("Speaker",Coordinate(.8,.1,.1),"",1));
    w->RegisterBlock(Block("Controller",Coordinate(.1,.1,.8),"",1));
    w->RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
    connect(w,SIGNAL(keyPressSignal(QKeyEvent&)),this,SLOT(keyPressEvent(QKeyEvent&)));
    connect(w,SIGNAL(blockCreateSignal(QMap<int,Bnode>::iterator)),this,SLOT(blockCreateEvent(QMap<int,Bnode>::iterator)));
    connect(w,SIGNAL(blockDestroySignal(QMap<int,Bnode>::iterator)),this,SLOT(blockDestroyEvent(QMap<int,Bnode>::iterator)));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(Spinning()));
    timer->start(10);
}

void MusicPlayer::serverLoad(World *w,Server*) {
    TheWorld=w;
    w->RegisterBlock(Block("Speaker",Coordinate(.8,.1,.1),"",1));
    w->RegisterBlock(Block("Controller",Coordinate(.1,.1,.8),"",1));
    w->RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(Spinning()));
    timer->start(10);
}

void MusicPlayer::keyPressEvent(QKeyEvent &e) {
    QVector<QMap<int,Bnode>::iterator>v=TheWorld->ThroughBlock(TheWorld->Myself->Position,TheWorld->Myself->LookAt);
    if (!v.size())
        return;
    Bnode &b=v[0].value();
    if (b.Type=="Speaker") {
        Sound *ss=(Sound*)b.Data;
        if (e.key()==Qt::Key_E) {
            if (ss->Status==UNLOAD) {
                QFileDialog qfd;
                emit TheWorld->releaseMouse();
                ss->LoadFile(qfd.getOpenFileName(0,"","","MP3 Files(*.mp3);;Wave Files(*.wav)"));
                ss->Move(b.Position);
                emit TheWorld->trackMouse();
            }
        } else if (e.key()==Qt::Key_F) {
            ss->Unload();
        } else if (e.key()==Qt::Key_C) {
            if (SelectingObject!=NULL) {
                if (SelectingObject->Type=="Controller") {
                    ControllerStatus *cs=(ControllerStatus*)SelectingObject->Data;
                    cs->AddLink(b);
                } else {
                    SpinnerStatus *ss=(SpinnerStatus*)SelectingObject->Data;
                    ss->AddLink(b);
                }
                SelectingObject=NULL;
            }
        }
    } else if (b.Type=="Controller") {
        ControllerStatus *cs=(ControllerStatus*)b.Data;
        if (e.key()==Qt::Key_E) {
            cs->Play();
        } else if (e.key()==Qt::Key_F) {
            cs->Pause();
        } else if (e.key()==Qt::Key_G) {
            cs->Stop();
        } else if (e.key()==Qt::Key_C) {
            SelectingObject=&b;
        }
    } else if (b.Type=="Spinner") {
        SpinnerStatus *ss=(SpinnerStatus*)b.Data;
        if (e.key()==Qt::Key_E) {
            if (ss->Spinning)
                ss->Accelerate();
            else
                ss->Start();
        } else if (e.key()==Qt::Key_F) {
            ss->Stop();
        } else if (e.key()==Qt::Key_C) {
            SelectingObject=&b;
        }
    }
}

void MusicPlayer::blockCreateEvent(QMap<int,Bnode>::iterator b) {
    if (b.value().Type=="Speaker")
        b.value().Data=new Sound;
    else if (b.value().Type=="Controller") {
        b.value().Data=new ControllerStatus;
        Controllers.push_back(&b.value());
    }
    else if (b.value().Type=="Spinner") {
        b.value().Data=new SpinnerStatus;
        Spinners.push_back(&b.value());
    }
}

void MusicPlayer::blockDestroyEvent(QMap<int,Bnode>::iterator b) {
    if (b.value().Type=="Speaker") {
        Sound *ss=(Sound*)b.value().Data;
        ss->Unload();
        delete ss;
    } else if (b.value().Type=="Controller") {
        ControllerStatus *cs=(ControllerStatus*)b.value().Data;
        Controllers.remove(Controllers.indexOf(&b.value()));
        delete cs;
    } else if (b.value().Type=="Spinner") {
        SpinnerStatus *ss=(SpinnerStatus*)b.value().Data;
        Spinners.remove(Spinners.indexOf(&b.value()));
        delete ss;
    }
    for (int i=0;i<Controllers.size();++i) {
        ControllerStatus *cs=(ControllerStatus*)Controllers[i]->Data;
        cs->RemoveLink(b.value());
    }
    for (int i=0;i<Spinners.size();++i) {
        SpinnerStatus *ss=(SpinnerStatus*)Spinners[i]->Data;
        ss->RemoveLink(b.value());
    }
}

void MusicPlayer::Spinning() {
    for (int i=0;i<Spinners.size();++i) {
        Bnode &TheSpinner=*Spinners[i];
        SpinnerStatus *ss=(SpinnerStatus*)TheSpinner.Data;
        if (ss->Spinning) {
            for (int j=0;j<ss->Linked.size();++j) {
                Bnode &b=*ss->Linked[j];
                Sound *spst=(Sound*)b.Data;
                Coordinate r=b.Position-TheSpinner.Position;
                r.y=0;
                double Radius=r.Length();
                b.Position=Coordinate(TheSpinner.Position.x+Radius*cos(ss->Theta),b.Position.y,TheSpinner.Position.z+Radius*sin(ss->Theta));
                spst->Move(b.Position);
            }
            ss->Theta+=ss->Speed;
        }
    }
}

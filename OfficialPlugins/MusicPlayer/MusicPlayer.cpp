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
    connect(w,SIGNAL(blockCreateSignal(Bnode&)),this,SLOT(blockCreateEvent(Bnode&)));
    connect(w,SIGNAL(blockDestroySignal(Bnode&)),this,SLOT(blockDestroyEvent(Bnode&)));
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
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
        if (e.key()==Qt::Key_E) {
            if (ss->Status==UNLOAD) {
                QFileDialog qfd;
                emit TheWorld->releaseMouse();
                ss->LoadFile(b.Position,qfd.getOpenFileName(0,"","","MP3 Files(*.mp3);;Wave Files(*.wav)"));
                emit TheWorld->trackMouse();
            }
        } else if (e.key()==Qt::Key_F) {
            ss->UnloadFile();
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

void MusicPlayer::blockCreateEvent(Bnode &b) {
    if (b.Type=="Speaker")
        b.Data=new SpeakerStatus;
    else if (b.Type=="Controller") {
        b.Data=new ControllerStatus;
        Controllers.push_back(&b);
    }
    else if (b.Type=="Spinner") {
        b.Data=new SpinnerStatus;
        Spinners.push_back(&b);
    }
}

void MusicPlayer::blockDestroyEvent(Bnode &b) {
    if (b.Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
        ss->UnloadFile();
        delete ss;
    } else if (b.Type=="Controller") {
        ControllerStatus *cs=(ControllerStatus*)b.Data;
        Controllers.remove(Controllers.indexOf(&b));
        delete cs;
    } else if (b.Type=="Spinner") {
        SpinnerStatus *ss=(SpinnerStatus*)b.Data;
        Spinners.remove(Spinners.indexOf(&b));
        delete ss;
    }
    for (int i=0;i<Controllers.size();++i) {
        ControllerStatus *cs=(ControllerStatus*)Controllers[i]->Data;
        cs->RemoveLink(b);
    }
    for (int i=0;i<Spinners.size();++i) {
        SpinnerStatus *ss=(SpinnerStatus*)Spinners[i]->Data;
        ss->RemoveLink(b);
    }
}

void MusicPlayer::Spinning() {
    for (int i=0;i<Spinners.size();++i) {
        Bnode &TheSpinner=*Spinners[i];
        SpinnerStatus *ss=(SpinnerStatus*)TheSpinner.Data;
        if (ss->Spinning) {
            for (int j=0;j<ss->Linked.size();++j) {
                Bnode &b=*ss->Linked[j];
                SpeakerStatus *spst=(SpeakerStatus*)b.Data;
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

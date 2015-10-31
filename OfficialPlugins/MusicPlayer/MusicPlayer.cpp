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
    Name="MusicPlayer1.1";
    Essential=1;
}

void MusicPlayer::clientLoad(World *w,Socket *s) {
    TheWorld=w;
    TheSocket=s;
    SelectedBlock=-1;
    Timer=new QTimer;
    connect(w,SIGNAL(keyPressSignal(QKeyEvent&)),this,SLOT(keyPressEvent(QKeyEvent&)));
    connect(w,SIGNAL(blockCreateSignal(QMap<int,Bnode>::iterator)),this,SLOT(clientBlockCreateEvent(QMap<int,Bnode>::iterator)));
    connect(w,SIGNAL(blockDestroySignal(QMap<int,Bnode>::iterator)),this,SLOT(blockDestroyEvent(QMap<int,Bnode>::iterator)));
    connect(w,SIGNAL(drawBlockSignal(QMap<int,Bnode>::iterator,bool&)),this,SLOT(drawBlockEvent(QMap<int,Bnode>::iterator,bool&)));
    connect(s,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(clientRecvVariantMap(int,QString,quint16,QVariantMap)));
    connect(Timer,SIGNAL(timeout()),this,SLOT(delta()));
    w->RegisterBlock(Block("Speaker",Coordinate(.8,.1,.1),""));
    w->RegisterBlock(Block("Controller",Coordinate(.1,.1,.8),""));
    w->RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),""));
    w->RegisterBlock(Block("FFT",Coordinate(.1,.5,.5),""));
    Timer->start(16);
}

void MusicPlayer::serverLoad(World *w, Server *s) {
    TheWorld=w;
    TheServer=s;
    connect(w,SIGNAL(blockCreateSignal(QMap<int,Bnode>::iterator)),this,SLOT(serverBlockCreateEvent(QMap<int,Bnode>::iterator)));
    connect(w,SIGNAL(blockDestroySignal(QMap<int,Bnode>::iterator)),this,SLOT(blockDestroyEvent(QMap<int,Bnode>::iterator)));
    connect(s,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(serverRecvVariantMap(int,QString,quint16,QVariantMap)));
    w->RegisterBlock(Block("Speaker",Coordinate(.8,.1,.1),""));
    w->RegisterBlock(Block("Controller",Coordinate(.1,.1,.8),""));
    w->RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),""));
    w->RegisterBlock(Block("FFT",Coordinate(.1,.5,.5),""));
}

void MusicPlayer::keyPressEvent(QKeyEvent &event) {
    QVector<QMap<int,Bnode>::iterator> PointAt=TheWorld->ThroughBlock(TheWorld->Myself->Position,TheWorld->Myself->LookAt);
    if (PointAt.size()==0)
        return;
    QMap<int,Bnode>::iterator TheBlock=PointAt[0];
    if (TheBlock->Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)TheBlock->Data;
        if (event.key()==Qt::Key_E) {
            if (ss->TheSound.Status==UNLOAD) {
                QFileDialog qfd;
                emit TheWorld->releaseMouse();
                ss->TheSound.LoadFile(qfd.getOpenFileName(0,"","","All Files(*.*)"));
                emit TheWorld->trackMouse();
                if (ss->TheSound.Status==STOP)
                    ss->Belong=TheWorld->Myself.key();
            }
        } else if (event.key()==Qt::Key_F) {
            if (ss->Belong==TheWorld->Myself.key())
                ss->TheSound.Unload();
        } else if (event.key()==Qt::Key_C) {
            if (SelectedBlock!=-1) {
                Bnode &b=TheWorld->Blocks.find(SelectedBlock).value();
                if (b.Type=="Controller") {
                    ControllerStatus *cs=(ControllerStatus*)b.Data;
                    cs->AddLink(TheBlock.key());
                } else if (b.Type=="Spinner") {
                    SpinnerStatus *ss=(SpinnerStatus*)b.Data;
                    ss->AddLink(TheBlock.key());
                } else if (b.Type=="FFT") {
                    FFTStatus *fs=(FFTStatus*)b.Data;
                    fs->AddLink(TheBlock.key());
                }
                SelectedBlock=-1;
            }
        }
    } else if (TheBlock->Type=="Controller") {
        ControllerStatus *cs=(ControllerStatus*)TheBlock->Data;
        if (event.key()==Qt::Key_E) {
            cs->Play();
        } else if (event.key()==Qt::Key_F) {
            cs->Pause();
        } else if (event.key()==Qt::Key_G) {
            cs->Stop();
        } else if (event.key()==Qt::Key_C) {
            SelectedBlock=TheBlock.key();
        }
    } else if (TheBlock->Type=="Spinner") {
        SpinnerStatus *ss=(SpinnerStatus*)TheBlock->Data;
        if (event.key()==Qt::Key_E) {
            if (!ss->Spinning)
                ss->Start();
            else
                ss->Accelerate();
        } else if (event.key()==Qt::Key_F) {
            ss->Stop();
        } else if (event.key()==Qt::Key_C) {
            SelectedBlock=TheBlock.key();
        }
    } else if (TheBlock->Type=="FFT") {
        if (event.key()==Qt::Key_C) {
            SelectedBlock=TheBlock.key();
        }
    }
}

void MusicPlayer::clientBlockCreateEvent(QMap<int,Bnode>::iterator TheBlock) {
    bool isMusicPlayer=0;
    if (TheBlock->Type=="Speaker") {
        TheBlock->Data=new SpeakerStatus(TheBlock.key());
        connect((SpeakerStatus*)TheBlock->Data,SIGNAL(encodeSignal(int,const void*,DWORD)),this,SLOT(recvEncode(int,const void*,DWORD)));
        isMusicPlayer=1;
    } else if (TheBlock->Type=="Controller") {
        TheBlock->Data=new ControllerStatus(TheWorld);
        Controllers.push_back(TheBlock.key());
        isMusicPlayer=1;
    } else if (TheBlock->Type=="Spinner") {
        TheBlock->Data=new SpinnerStatus(TheWorld,TheBlock->Position);
        Spinners.push_back(TheBlock.key());
        isMusicPlayer=1;
    } else if (TheBlock->Type=="FFT") {
        TheBlock->Data=new FFTStatus(TheWorld);
        FFTs.push_back(TheBlock.key());
        isMusicPlayer=1;
    }
    if (isMusicPlayer) {
        QVariantMap qvm;
        qvm.insert("type","binfo");
        qvm.insert("num",TheBlock.key());
        emit TheSocket->sendVariantMap(qvm,-1);
    }
}

void MusicPlayer::blockDestroyEvent(QMap<int,Bnode>::iterator TheBlock) {
    if (TheBlock->Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)TheBlock->Data;
        ss->TheSound.Unload();
        delete ss;
        for (int i=0;i<Controllers.size();++i) {
            ControllerStatus *cs=(ControllerStatus*)TheWorld->Blocks.find(Controllers[i])->Data;
            cs->RemoveLink(TheBlock.key());
        }
        for (int i=0;i<Spinners.size();++i) {
            SpinnerStatus *ss=(SpinnerStatus*)TheWorld->Blocks.find(Spinners[i])->Data;
            ss->RemoveLink(TheBlock.key());
        }
        for (int i=0;i<FFTs.size();++i) {
            FFTStatus *fs=(FFTStatus*)TheWorld->Blocks.find(FFTs[i])->Data;
            fs->RemoveLink(TheBlock.key());
        }
    } else if (TheBlock->Type=="Controller") {
        Controllers.removeAll(TheBlock.key());
        delete (ControllerStatus*)TheBlock->Data;
    } else if (TheBlock->Type=="Spinner") {
        Spinners.removeAll(TheBlock.key());
        delete (SpinnerStatus*)TheBlock->Data;
    } else if (TheBlock->Type=="FFT") {
        FFTs.removeAll(TheBlock.key());
        delete (FFTStatus*)TheBlock->Data;
    }
}

void MusicPlayer::recvEncode(int Number,const void *buffer,DWORD length) {
    QVariantMap qvm;
    qvm.insert("type","mdata");
    QByteArray qba((const char*)buffer,length);
    qvm.insert("data",qba.toBase64());
    qvm.insert("num",Number);
    emit TheSocket->sendVariantMap(qvm,-1);
}

void MusicPlayer::serverBlockCreateEvent(QMap<int,Bnode>::iterator TheBlock) {
    if (TheBlock->Type=="Speaker") {
        TheBlock->Data=new SpeakerStatus(TheBlock.key());
    } else if (TheBlock->Type=="Controller") {
        TheBlock->Data=new ControllerStatus(TheWorld);
        Controllers.push_back(TheBlock.key());
    } else if (TheBlock->Type=="Spinner") {
        TheBlock->Data=new SpinnerStatus(TheWorld,TheBlock->Position);
        Spinners.push_back(TheBlock.key());
    } else if (TheBlock->Type=="FFT") {
        TheBlock->Data=new FFTStatus(TheWorld);
        FFTs.push_back(TheBlock.key());
    }
}

void MusicPlayer::clientRecvVariantMap(const int,const QString&,const quint16,const QVariantMap &qvm) {
    if (qvm["type"].toString()=="binfo") {
        int num=qvm["num"].toInt();
        Bnode &b=TheWorld->Blocks.find(num).value();
        QString &type=b.Type;
        if (type=="Speaker") {
            SpeakerStatus *ss=(SpeakerStatus*)b.Data;
            ss->Belong=qvm["belong"].toInt();
        } else if (type=="Controller") {
            ControllerStatus *cs=(ControllerStatus*)b.Data;
            cs->AddLink(qvm["link"].toInt());
        } else if (type=="Spinner") {
            SpinnerStatus *ss=(SpinnerStatus*)b.Data;
            ss->AddLink(qvm["link"].toInt());
        } else if (type=="FFT") {
            FFTStatus *fs=(FFTStatus*)b.Data;
            fs->AddLink(qvm["link"].toInt());
        }
    } else if (qvm["type"].toString()=="mdata") {
        int num=qvm["num"].toInt();
        Bnode &b=TheWorld->Blocks.find(num).value();
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
        if (ss->Belong!=TheWorld->Myself.key()) {
            QByteArray buffer=QByteArray::fromBase64(qvm["data"].toByteArray());
            ss->TheSound.StreamPushData(buffer.data(),buffer.size());
        }
    }
}

void MusicPlayer::serverRecvVariantMap(const int id,const QString&,const quint16,const QVariantMap &qvm) {
    if (qvm["type"].toString()=="binfo") {
        int num=qvm["num"].toInt();
        Bnode &b=TheWorld->Blocks.find(num).value();
        QString &type=b.Type;
        if (type=="Speaker") {
            QVariantMap ret=qvm;
            SpeakerStatus *ss=(SpeakerStatus*)b.Data;
            ret.insert("belong",ss->Belong);
            emit TheServer->sendVariantMap(ret,id);
        } else if (type=="Controller") {
            ControllerStatus *cs=(ControllerStatus*)b.Data;
            for (int i=0;i<cs->Linked.size();++i) {
                QVariantMap ret=qvm;
                ret.insert("link",cs->Linked[i]);
                emit TheServer->sendVariantMap(ret,id);
            }
        } else if (type=="Spinner") {
            SpinnerStatus *ss=(SpinnerStatus*)b.Data;
            for (int i=0;i<ss->Linked.size();++i) {
                QVariantMap ret=qvm;
                ret.insert("link",ss->Linked[i]);
                emit TheServer->sendVariantMap(ret,id);
            }
        } else if (type=="FFT") {
            FFTStatus *fs=(FFTStatus*)b.Data;
            QVariantMap ret=qvm;
            ret.insert("link",fs->Linked);
            emit TheServer->sendVariantMap(ret,id);
        }
    } else if (qvm["type"].toString()=="mdata") {
        emit TheServer->sendVariantMap(qvm,-1);
    }
}

void MusicPlayer::delta() {
    for (int i=0;i<Spinners.size();++i) {
        SpinnerStatus *ss=(SpinnerStatus*)TheWorld->Blocks.find(Spinners[i])->Data;
        ss->Delta();
    }
}

void MusicPlayer::drawBlockEvent(QMap<int,Bnode>::iterator TheBlock,bool&) {
    if (TheBlock->Type=="FFT") {
        FFTStatus *fs=(FFTStatus*)TheBlock->Data;
        QVector<float>fftdata=fs->GetData();

    }
}

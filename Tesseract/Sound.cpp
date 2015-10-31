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

#include "Sound.h"

void Sound::EncodeRecv(HENCODE handle,DWORD channel,const void *buffer,DWORD length,void *user) {
    Sound *sp=(Sound*)user;
    emit sp->encodeSignal(handle,channel,buffer,length);
}

void Sound::c(void*) {}

QWORD Sound::l(void*) {
    return 0;
}

DWORD Sound::r(void*,DWORD,void*) {
    return 0;
}

BOOL Sound::s(QWORD,void*) {
    return FALSE;
}

void Sound::Init() {
    BASS_Init(-1,44100,BASS_DEVICE_3D,0,0);
    BASS_Set3DFactors(1,1,0);
    BASS_SetConfig(BASS_CONFIG_3DALGORITHM,BASS_3DALG_FULL);
    BASS_RecordInit(-1);
    qRegisterMetaType<HENCODE>("HENCODE");
    qRegisterMetaType<DWORD>("DWORD");
}

void Sound::SetListenerValues(Coordinate Position,Coordinate EyeVector,Coordinate HeadVector) {
    BASS_3DVECTOR pos(Position.x,Position.y,Position.z),front(EyeVector.x,EyeVector.y,EyeVector.z),top(HeadVector.x,HeadVector.y,HeadVector.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

Sound::Sound() {
    handle=0;
    Status=UNLOAD;
    Encoding=0;
}

Sound::~Sound() {
    Unload();
}

void Sound::LoadFile(const QString &Filename) {
    if (Status!=UNLOAD)
        Unload();
    handle=BASS_StreamCreateFile(FALSE,Filename.toLocal8Bit().data(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D);
    if (handle)
        Status=STOP;
}

void Sound::Unload() {
    BASS_ChannelStop(handle);
    BASS_StreamFree(handle);
    handle=0;
    Status=UNLOAD;
}

void Sound::Pause() {
    if (Status!=UNLOAD) {
        BASS_ChannelPause(handle);
        Status=PAUSE;
    }
}

void Sound::Play() {
    if (Status!=UNLOAD) {
        BASS_ChannelPlay(handle,FALSE);
        Status=PLAY;
    }
}

void Sound::Stop() {
    if (Status!=UNLOAD) {
        BASS_ChannelStop(handle);
        BASS_ChannelSetPosition(handle,0,0);
        Status=STOP;
    }
}

void Sound::Move(Coordinate Position) {
    if (Status!=UNLOAD) {
        BASS_3DVECTOR v(Position.x,Position.y,Position.z);
        BASS_ChannelSet3DPosition(handle,&v,NULL,NULL);
        BASS_Apply3D();
    }
}

void Sound::StartEncode() {
    if ((Status!=UNLOAD)&&(!Encoding)) {
        BASS_Encode_Start(handle,"lame -f - -",BASS_ENCODE_AUTOFREE,Sound::EncodeRecv,this);
        Encoding=1;
    }
}

void Sound::StopEncode() {
    if (Status!=UNLOAD) {
        BASS_Encode_Stop(handle);
        Encoding=0;
    }
}

void Sound::StartRecord() {
    if (Status!=UNLOAD) {
        Unload();
    }
    handle=BASS_RecordStart(44100,1,0,NULL,this);
    Status=RECORDING;
}

void Sound::StopRecord() {
    Unload();
}

void Sound::CreateEmptyStream() {
    if (Status!=UNLOAD) {
        Unload();
    }
    BASS_FILEPROCS bfp={Sound::c,Sound::l,Sound::r,Sound::s};
    handle=BASS_StreamCreateFileUser(STREAMFILE_BUFFERPUSH,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D,&bfp,NULL);
    Status=STOP;
    Play();
}

void Sound::StreamPushData(void *buffer,DWORD length) {
    if (Status!=UNLOAD) {
        BASS_StreamPutFileData(handle,buffer,length);
    }
}

QVector<float> Sound::GetFFTData() {
    if (Status!=PLAY)
        return QVector<float>();
    QVector<float>ret(512);
    float fft[512];
    BASS_ChannelGetData(handle,fft,BASS_DATA_FFT1024);
    for (int i=0;i<512;++i)
        ret[i]=fft[i];
    return ret;
}

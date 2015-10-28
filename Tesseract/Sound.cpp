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

BOOL Sound::RecordRecv(HRECORD handle,const void *buffer,DWORD length,void *user) {
    Sound *sp=(Sound*)user;
    emit sp->recordSignal(handle,buffer,length);
    return TRUE;
}

void Sound::Init() {
    BASS_Init(-1,44100,BASS_DEVICE_3D,0,0);
    BASS_Set3DFactors(1,1,0);
    BASS_SetConfig(BASS_CONFIG_3DALGORITHM,BASS_3DALG_FULL);
    BASS_RecordInit(-1);
#ifdef WIN32
    BASS_PluginLoad("bassenc.dll",0);
#elif __linux__
    BASS_PluginLoad("libbassenc.so",0);
#else
    BASS_PluginLoad("libbassenc.dylib",0);
#endif
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
    if (!UNLOAD)
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
    if (!UNLOAD) {
        BASS_ChannelPause(handle);
        Status=PAUSE;
    }
}

void Sound::Play() {
    if (!UNLOAD) {
        BASS_ChannelPlay(handle,FALSE);
        Status=PLAY;
    }
}

void Sound::Stop() {
    if (!UNLOAD) {
        BASS_ChannelStop(handle);
        BASS_ChannelSetPosition(handle,0,0);
        Status=STOP;
    }
}

void Sound::Move(Coordinate Position) {
    if (!UNLOAD) {
        BASS_3DVECTOR v(Position.x,Position.y,Position.z);
        BASS_ChannelSet3DPosition(handle,&v,NULL,NULL);
        BASS_Apply3D();
    }
}

void Sound::StartEncode() {
    if (!UNLOAD&&!Encoding) {
        BASS_Encode_Start(handle,"lame -r --alt-preset cbr 128 - -",BASS_ENCODE_NOHEAD,Sound::EncodeRecv,this);
        Encoding=1;
    }
}

void Sound::StopEncode() {
    if (!UNLOAD) {
        BASS_Encode_Stop(handle);
        Encoding=0;
    }
}

void Sound::StartRecord() {
    if (!UNLOAD) {
        Unload();
    }
    handle=BASS_RecordStart(44100,1,0,Sound::RecordRecv,this);
    Status=RECORDING;
}

void Sound::StopRecord() {
    Unload();
}

void Sound::LoadRam(void *buffer,DWORD length) {
    if (!UNLOAD) {
        Unload();
    }
    handle=BASS_StreamCreateFile(TRUE,buffer,0,length,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D);
    if (handle)
        Status=STOP;
}

QVector<float> Sound::GetFFTData() {
    if (!PLAY)
        return QVector<float>();
    QVector<float>ret(512);
    float fft[512];
    BASS_ChannelGetData(handle,fft,BASS_DATA_FFT1024);
    for (int i=0;i<512;++i)
        ret[i]=fft[i];
    return ret;
}

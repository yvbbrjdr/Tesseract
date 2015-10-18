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

void Sound::Init() {
    BASS_Init(-1,44100,BASS_DEVICE_3D,0,0);
    BASS_Set3DFactors(1,1,0);
    BASS_SetConfig(BASS_CONFIG_3DALGORITHM,BASS_3DALG_FULL);
}

void Sound::SetListenerValues(Coordinate Position,Coordinate EyeVector,Coordinate HeadVector) {
    BASS_3DVECTOR pos(Position.x,Position.y,Position.z),front(EyeVector.x,EyeVector.y,EyeVector.z),top(HeadVector.x,HeadVector.y,HeadVector.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

Sound::Sound() {
    handle=0;
    Status=UNLOAD;
}

Sound::~Sound() {
    Unload();
}

void Sound::LoadFile(const QString &Filename) {
    if (!UNLOAD)
        Unload();
    handle=BASS_StreamCreateFile(FALSE,Filename.toLocal8Bit().data(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D);
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

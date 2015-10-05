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

#include "SpeakerStatus.h"

SpeakerStatus::SpeakerStatus() {
    Status=UNLOAD;
    hc=0;
}

bool SpeakerStatus::LoadFile(Coordinate Position,QString Filename) {
    if (Status!=UNLOAD)
        return 0;
    hc=Sound::AddNewFileSound(Position,Filename);
    if (hc==0)
        return 0;
    Status=STOP;
    return 1;
}

bool SpeakerStatus::UnloadFile() {
    if (Status==UNLOAD)
        return 0;
    Sound::RemoveASound(hc);
    Status=UNLOAD;
    return 1;
}

bool SpeakerStatus::Play() {
    if (Status==UNLOAD||Status==PLAY)
        return 0;
    Sound::PlayASound(hc);
    Status=PLAY;
    return 1;
}

bool SpeakerStatus::Pause() {
    if (Status==UNLOAD||Status==STOP||Status==PAUSE)
        return 0;
    Sound::PauseASound(hc);
    Status=PAUSE;
    return 1;
}

bool SpeakerStatus::Stop() {
    if (Status==UNLOAD||Status==STOP)
        return 0;
    Sound::StopASound(hc);
    Status=STOP;
    return 1;
}

bool SpeakerStatus::Move(Coordinate Position) {
    if (Status==UNLOAD)
        return 0;
    Sound::MoveASound(hc,Position);
    return 1;
}

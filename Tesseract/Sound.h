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

#ifndef SOUND
#define SOUND

#include <bass.h>
#include "Coordinate.h"
#include <QString>

class Sound {
public:
    static void SetListenerValues(Coordinate Position,Coordinate EyeVector,Coordinate HeadVector);
    static HSTREAM AddNewFileSound(Coordinate Position,const QString &Filename);
    static void RemoveASound(HCHANNEL hc);
    static void PauseASound(HCHANNEL hc);
    static void PlayASound(HCHANNEL hc);
    static void StopASound(HCHANNEL hc);
    static void MoveASound(HCHANNEL hc,Coordinate Position);
};

#endif // SOUND


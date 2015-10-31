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

SpeakerStatus::SpeakerStatus(int _Number) {
    Number=_Number;
    Belong=0;
    connect(&TheSound,SIGNAL(encodeSignal(HENCODE,DWORD,const void*,DWORD)),this,SLOT(recvEncode(HENCODE,DWORD,const void*,DWORD)));
}

void SpeakerStatus::recvEncode(HENCODE,DWORD,const void *buffer,DWORD length) {
    emit encodeSignal(Number,buffer,length);
}

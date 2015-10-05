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

#include "ControllerStatus.h"

bool ControllerStatus::AddLink(Bnode &b) {
    if (b.Type!="Speaker"||Linked.indexOf(&b)!=-1)
        return 0;
    Linked.push_back(&b);
    return 1;
}

bool ControllerStatus::RemoveLink(Bnode &b) {
    if (Linked.indexOf(&b)==-1)
        return 0;
    Linked.remove(Linked.indexOf(&b));
    return 1;
}

void ControllerStatus::Play() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Play();
    }
}

void ControllerStatus::Pause() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Pause();
    }
}

void ControllerStatus::Stop() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Stop();
    }
}

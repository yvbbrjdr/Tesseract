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

ControllerStatus::ControllerStatus(World *_TheWorld) {
    TheWorld=_TheWorld;
}

void ControllerStatus::AddLink(int n) {
    if (TheWorld->Blocks.find(n)->Type=="Speaker"&&Linked.indexOf(n)==-1)
        Linked.push_back(n);
}

void ControllerStatus::RemoveLink(int n) {
    Linked.removeAll(n);
}

void ControllerStatus::Play() {
	for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)TheWorld->Blocks.find(Linked[i])->Data;
        if (ss->Belong) {
            ss->TheSound.Move(TheWorld->Blocks.find(Linked[i])->Position);
            ss->TheSound.Play();
            ss->TheSound.StartEncode();
        }
    }
}

void ControllerStatus::Pause() {
	for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)TheWorld->Blocks.find(Linked[i])->Data;
        ss->TheSound.Pause();
        if (ss->Belong)
            ss->TheSound.StopEncode();
    }
}

void ControllerStatus::Stop() {
	for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)TheWorld->Blocks.find(Linked[i])->Data;
        ss->TheSound.Stop();
        if (!ss->Belong)
            ss->TheSound.Unload();
        else
            ss->TheSound.StopEncode();
    }
}

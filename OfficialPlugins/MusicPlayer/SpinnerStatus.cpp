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

#include "SpinnerStatus.h"

SpinnerStatus::SpinnerStatus(World *_TheWorld,const Coordinate &_Position) {
    Spinning=0;
    TheWorld=_TheWorld;
    Position=_Position;
}

void SpinnerStatus::AddLink(int n) {
    if (TheWorld->Blocks.find(n)->Type=="Speaker"&&Linked.indexOf(n)==-1)
        Linked.push_back(n);
}

void SpinnerStatus::RemoveLink(int n) {
    Linked.removeAll(n);
}

void SpinnerStatus::Start() {
    Speed=0.0167;
    Spinning=1;
}

void SpinnerStatus::Stop() {
    Spinning=0;
}

void SpinnerStatus::Accelerate() {
    Speed+=0.01;
}

void SpinnerStatus::Delta() {
    if (Spinning) {
        for (int j=0;j<Linked.size();++j) {
            Bnode &b=TheWorld->Blocks.find(Linked[j]).value();
            SpeakerStatus *spst=(SpeakerStatus*)b.Data;
            Coordinate r=b.Position-Position;
            r.y=0;
            double Radius=r.Length(),Theta=atan2(r.z,r.x)+Speed;
            b.Position=Coordinate(Position.x+Radius*cos(Theta),b.Position.y,Position.z+Radius*sin(Theta));
            spst->TheSound.Move(b.Position);
        }
    }
}

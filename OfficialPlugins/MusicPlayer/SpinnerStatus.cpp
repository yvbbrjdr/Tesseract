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

SpinnerStatus::SpinnerStatus() {
    Spinning=0;
    Theta=0;
}

bool SpinnerStatus::AddLink(Bnode &b) {
    if (b.Type!="Speaker"||Linked.indexOf(&b)!=-1)
        return 0;
    Linked.push_back(&b);
    return 1;
}

bool SpinnerStatus::RemoveLink(Bnode &b) {
    if (Linked.indexOf(&b)==-1)
        return 0;
    Linked.remove(Linked.indexOf(&b));
    return 1;
}

bool SpinnerStatus::Start() {
    if (Spinning)
        return 0;
    Speed=0.0167;
    Spinning=1;
    return 1;
}

bool SpinnerStatus::Stop() {
    if (!Spinning)
        return 0;
    Spinning=0;
    return 1;
}

bool SpinnerStatus::Accelerate() {
    if (!Spinning)
        return 0;
    Speed+=0.01;
    return 1;
}

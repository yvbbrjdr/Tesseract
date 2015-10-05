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

#include "Coordinate.h"

Coordinate::Coordinate() {
    x=y=z=0;
}

Coordinate::Coordinate(double a,double b,double c) {
    x=a;
    y=b;
    z=c;
}

Coordinate Coordinate::operator + (Coordinate b) {
    Coordinate a=*this;
    return Coordinate(a.x+b.x,a.y+b.y,a.z+b.z);
}

Coordinate Coordinate::operator - (Coordinate b) {
    Coordinate a=*this;
    return Coordinate(a.x-b.x,a.y-b.y,a.z-b.z);
}

Coordinate Coordinate::operator * (double d) {
    Coordinate a=*this;
    return Coordinate(a.x*d,a.y*d,a.z*d);
}

Coordinate Coordinate::operator / (double d) {
    Coordinate a=*this;
    return Coordinate(a.x/d,a.y/d,a.z/d);
}

double* Coordinate::ToArray(double res[3]) {
    res[0]=this->x;
    res[1]=this->y;
    res[2]=this->z;
    return res;
}

double Coordinate::Length() {
    return sqrt(x*x+y*y+z*z);
}

Coordinate Coordinate::ToDirection() {
    double l=Length();
    Coordinate res=*this;
    if (fabs(l)>ZERO) {
        res.x/=l;
        res.y/=l;
        res.z/=l;
    }
    return res;
}

Coordinate Coordinate::Abs() {
    Coordinate res=*this;
    res.x=fabs(x);
    res.y=fabs(y);
    res.z=fabs(z);
    return res;
}

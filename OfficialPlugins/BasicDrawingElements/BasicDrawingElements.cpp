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

#include "BasicDrawingElements.h"

BasicDrawingElements::BasicDrawingElements() {
    Name="BasicDrawingElements1.0";
}

void BasicDrawingElements::clientLoad(World *w,Socket*) {
    connect(w,SIGNAL(drawBeginSignal()),this,SLOT(drawBeginEvent()));
    connect(w,SIGNAL(drawDoneSignal()),this,SLOT(drawDoneEvent()));
    TheWorld=w;
}

void BasicDrawingElements::drawBeginEvent() {
    GLfloat c[4]={.1,.8,.1,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c);
    glBegin(GL_POLYGON);
        glVertex3f(TheWorld->Size.x/2,0,TheWorld->Size.z/2);
        glVertex3f(TheWorld->Size.x/2,0,-TheWorld->Size.z/2);
        glVertex3f(-TheWorld->Size.x/2,0,-TheWorld->Size.z/2);
        glVertex3f(-TheWorld->Size.x/2,0,TheWorld->Size.z/2);
    glEnd();
}

void BasicDrawingElements::drawDoneEvent() {
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
    glColor3f(0,0,0);
    emit TheWorld->renderText2D(Coordinate(20,40,0),QString("(%1,%2,%3)").arg(TheWorld->Myself->Position.x).arg(TheWorld->Myself->Position.y).arg(TheWorld->Myself->Position.z));
}

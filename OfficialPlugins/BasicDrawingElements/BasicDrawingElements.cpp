#include "BasicDrawingElements.h"

BasicDrawingElements::BasicDrawingElements() {
    Name="BasicDrawingElements1.0";
    Essential=0;
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

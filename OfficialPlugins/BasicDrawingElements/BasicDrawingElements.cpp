#include "BasicDrawingElements.h"

BasicDrawingElements::BasicDrawingElements() {
    Name="BasicDrawingElements";
}

void BasicDrawingElements::clientLoad(World &w) {
    connect(&w,SIGNAL(drawBeginSignal(World&)),this,SLOT(drawBeginEvent(World&)));
    connect(&w,SIGNAL(drawDoneSignal(World&)),this,SLOT(drawDoneEvent(World&)));
}

void BasicDrawingElements::drawBeginEvent(World &TheWorld) {
    GLfloat c[4]={.1,.8,.1,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c);
    glBegin(GL_POLYGON);
        glVertex3f(TheWorld.Size.x/2,0,TheWorld.Size.z/2);
        glVertex3f(TheWorld.Size.x/2,0,-TheWorld.Size.z/2);
        glVertex3f(-TheWorld.Size.x/2,0,-TheWorld.Size.z/2);
        glVertex3f(-TheWorld.Size.x/2,0,TheWorld.Size.z/2);
    glEnd();
}

void BasicDrawingElements::drawDoneEvent(World&) {
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
}

#include "BasicDrawingElements.h"

BasicDrawingElements::BasicDrawingElements() {
    Name="BasicDrawingElements";
    HookDrawBegin=
    HookDrawDone=1;
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

void BasicDrawingElements::drawDoneEvent(World &w) {
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
    glColor3f(0,0,0);
    Coordinate &p=w.Myself->Position;
    renderText(20,40,QString("(%1,%2,%3)").arg(p.x).arg(p.y).arg(p.z));
}

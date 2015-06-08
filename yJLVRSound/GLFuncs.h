#ifndef GLFUNCS_H
#define GLFUNCS_H

#include <cstdio>

void yJLVRSoundWidget::initializeGL() {
    setGeometry(0,0,800,600);
    glClearColor(.7,1,1,0);
    glEnable(GL_DEPTH_TEST);
    p.turn(0,0);
    p.go(0,0,0);
    p.turn(0,0);
    printf("%f %f %f %f %f %f %f %f %f\n",p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
}

void yJLVRSoundWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75,4.0/3,1,50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,-w.size.z/2);
        glVertex3f(w.size.x/2,0,-w.size.z/2);
    glEnd();
    glFlush();
}

void yJLVRSoundWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Escape:
            close();
    }
}

void yJLVRSoundWidget::resizeGL(int width,int height) {
    if(!height)
        height=1;
    glViewport(0,0,(GLint)width,(GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#endif // GLFUNCS_H

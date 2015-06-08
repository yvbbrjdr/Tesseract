#ifndef GLFUNCS_H
#define GLFUNCS_H

#include <cstdio>

void yJLVRSoundWidget::initializeGL() {
    setGeometry(0,0,800,600);
    glClearColor(.7,1,1,0);
}

void yJLVRSoundWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    printf("%f %f %f %f %f %f %f %f %f\n",p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    gluLookAt(p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(-w.size.x/2,w.size.y/2,0);
        glVertex3f(w.size.x/2,w.size.y/2,0);
        glVertex3f(w.size.x/2,-w.size.y/2,0);
        glVertex3f(-w.size.x/2,-w.size.y/2,0);
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
        height = 1;
    glViewport(0,0,(GLint)width,(GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#endif // GLFUNCS_H

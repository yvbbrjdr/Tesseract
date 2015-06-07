#ifndef GLFUNCS_H
#define GLFUNCS_H

void yJLVRSoundWidget::initializeGL() {
    setGeometry(0,0,800,600);
    glClearColor(.7,1,1,0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void yJLVRSoundWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(p.pos.x,p.pos.y,p.pos.z+1,p.at.x,p.at.y,p.at.z,0,0,1);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(-100,100,0);
        glVertex3f(100,100,0);
        glVertex3f(100,-100,0);
        glVertex3f(-100,-100,0);
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

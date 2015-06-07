#ifndef GLFUNCS_H
#define GLFUNCS_H

void yJLVRSoundWidget::initializeGL() {
    setGeometry(0,0,800,600);
    glClearColor(0,1,0,0);
}

void yJLVRSoundWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void yJLVRSoundWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Escape:
            close();
    }
}

#endif // GLFUNCS_H

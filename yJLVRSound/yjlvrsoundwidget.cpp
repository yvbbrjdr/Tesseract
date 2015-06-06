#include "yjlvrsoundwidget.h"
#include "ui_yjlvrsoundwidget.h"

yJLVRSoundWidget::yJLVRSoundWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::yJLVRSoundWidget) {ui->setupUi(this);}

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

yJLVRSoundWidget::~yJLVRSoundWidget() {
    delete ui;
}

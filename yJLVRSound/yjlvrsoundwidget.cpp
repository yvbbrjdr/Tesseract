#include "yjlvrsoundwidget.h"
#include "ui_yjlvrsoundwidget.h"

World w(Coordinate(100,100,100));
Player p(&w);

#include "GLFuncs.h"

yJLVRSoundWidget::yJLVRSoundWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::yJLVRSoundWidget) {
    ui->setupUi(this);
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    QGLFormat glf;
    glf.setDoubleBuffer(true);
    QGLFormat::setDefaultFormat(glf);
}

yJLVRSoundWidget::~yJLVRSoundWidget() {
    delete ui;
}

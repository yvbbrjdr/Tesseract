#include "yjlvrsoundwidget.h"
#include "ui_yjlvrsoundwidget.h"

World w(Coordinate(100,100,100));
Player p(&w);

#include "GLFuncs.h"

yJLVRSoundWidget::yJLVRSoundWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::yJLVRSoundWidget) {
    ui->setupUi(this);

}

yJLVRSoundWidget::~yJLVRSoundWidget() {
    delete ui;
}

#include "yjlvrsoundwidget.h"
#include "ui_yjlvrsoundwidget.h"

yJLVRSoundWidget::yJLVRSoundWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yJLVRSoundWidget)
{
    ui->setupUi(this);
}

yJLVRSoundWidget::~yJLVRSoundWidget()
{
    delete ui;
}

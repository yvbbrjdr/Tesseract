#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

World TesseractWidget::w(Coordinate(100,100,100));
Player TesseractWidget::p(Coordinate(100,100,100));
bool TesseractWidget::keystatus[128]={};

TesseractWidget::TesseractWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::TesseractWidget) {
    ui->setupUi(this);
    this->showFullScreen();
    memset(keystatus,0,sizeof(keystatus));
    creatingblock=0;
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread;
    gt->start();
    GLTimer=new QTimer;
    GLTimer->setInterval(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    GLTimer->start();
    w.RegisterBlock(SpeakerBlock());
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {delete ui;}

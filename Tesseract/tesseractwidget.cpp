#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

class GameThread : public QThread {
public:
    void run() {
        while (1) {
            if (TesseractWidget::keystatus['w'])
                TesseractWidget::p.go(.1,0,0);
            if (TesseractWidget::keystatus['a'])
                TesseractWidget::p.go(0,.1,0);
            if (TesseractWidget::keystatus['s'])
                TesseractWidget::p.go(-.1,0,0);
            if (TesseractWidget::keystatus['d'])
                TesseractWidget::p.go(0,-.1,0);
            if (TesseractWidget::keystatus['x'])
                TesseractWidget::p.go(0,0,.1);
            if (TesseractWidget::keystatus['z'])
                TesseractWidget::p.go(0,0,-.1);
            Sound::SetListenerValues(TesseractWidget::p.pos,TesseractWidget::p.face,TesseractWidget::p.up);
            QTime dieTime=QTime::currentTime().addMSecs(10);
            while (QTime::currentTime()<dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
};

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
    w.RegisterBlock("Stone",Coordinate(.2,.2,.2),"",1);
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {delete ui;}

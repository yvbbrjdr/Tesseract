#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

#include "ALFuncs.h"
#include "GLFuncs.h"
#include "NetFuncs.h"
#include "World.h"

class GameThread : public QThread {
public:
    TesseractWidget *tw;
    GameThread(TesseractWidget *t) {tw=t;}
    void run() {
        while (1) {
            if (tw->keystatus['w'])
                tw->p.go(.1,0,0);
            if (tw->keystatus['a'])
                tw->p.go(0,.1,0);
            if (tw->keystatus['s'])
                tw->p.go(-.1,0,0);
            if (tw->keystatus['d'])
                tw->p.go(0,-.1,0);
            if (tw->keystatus['x'])
                tw->p.go(0,0,.1);
            if (tw->keystatus['z'])
                tw->p.go(0,0,-.1);
            tw->SetListenerValues();
            QTime dieTime=QTime::currentTime().addMSecs(10);
            while (QTime::currentTime()<dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
};

TesseractWidget::TesseractWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::TesseractWidget) {
    ui->setupUi(this);
    memset(keystatus,0,sizeof(keystatus));
    creatingblock=0;
    w=World(Coordinate(100,100,100));
    p=Player(&w);
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread(this);
    gt->start();
    GLTimer=new QTimer;
    GLTimer->setInterval(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    GLTimer->start();
    AddNewSound(Coordinate(0,2,6),"sample.mp3");
    w.RegisterBlock("Stone",Coordinate(.5,.5,.5),"",1);
    w.RegisterBlock("Speaker",Coordinate(1,0,0),"",1);
    w.AddBlock(1,Coordinate(0,2,6),Coordinate(.5,.5,.5));
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {delete ui;}

#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

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
            tw->w.SetListenerValues(tw->p.pos,tw->p.face,tw->p.up);
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
    this->showFullScreen();
    memset(keystatus,0,sizeof(keystatus));
    creatingblock=0;
    w.size=Coordinate(100,100,100);
    p=Player(w.size);
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread(this);
    gt->start();
    GLTimer=new QTimer;
    GLTimer->setInterval(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    GLTimer->start();
    w.RegisterBlock("Stone",Coordinate(.2,.2,.2),"",1);
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {delete ui;}

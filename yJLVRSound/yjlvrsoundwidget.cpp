#include "yjlvrsoundwidget.h"
#include "ui_yjlvrsoundwidget.h"

World w(Coordinate(50,50,50));
Player p(&w);

#include "ALFuncs.h"
#include "GLFuncs.h"

class GameThread : public QThread {
public:
    void run() {
        while (1) {
            if (keystatus['w'])
                p.go(.1,0,0);
            if (keystatus['a'])
                p.go(0,.1,0);
            if (keystatus['s'])
                p.go(-.1,0,0);
            if (keystatus['d'])
                p.go(0,-.1,0);
            if (keystatus['x'])
                p.go(0,0,.1);
            if (keystatus['z'])
                p.go(0,0,-.1);
            SetListenerValues();
            QTime dieTime=QTime::currentTime().addMSecs(10);
            while (QTime::currentTime()<dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
};

yJLVRSoundWidget::yJLVRSoundWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::yJLVRSoundWidget) {
    ui->setupUi(this);
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread;
    gt->start();
    GLTimer=new QTimer;
    GLTimer->setInterval(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    GLTimer->start();
    AddNewSound(Coordinate(0,2,6),"sample.wav");
}

void yJLVRSoundWidget::DrawScene() {updateGL();}

yJLVRSoundWidget::~yJLVRSoundWidget() {delete ui;}

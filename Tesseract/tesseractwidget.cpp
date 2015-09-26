#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

World TesseractWidget::TheWorld(Coordinate(100,100,100));
bool TesseractWidget::KeyStatus[128]={};
PluginManager TesseractWidget::PM;

TesseractWidget::TesseractWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::TesseractWidget) {
    ui->setupUi(this);
    this->showFullScreen();
    memset(KeyStatus,0,sizeof(KeyStatus));
    creatingblock=0;
    this->setMouseTracking(true);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread;
    gt->start();
    GLTimer=new QTimer;
    GLTimer->setInterval(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    GLTimer->start();
    TheWorld.RegisterBlock(Block("Stone",Coordinate(.2,.2,.2),"",1));
    currentblocktype="Stone";
    connect(this,SIGNAL(drawBlockSignal(World&,Bnode&,bool&)),&TheWorld,SIGNAL(drawBlockSignal(World&,Bnode&,bool&)));
    connect(this,SIGNAL(drawBeginSignal(World&)),&TheWorld,SIGNAL(drawBeginSignal(World&)));
    connect(this,SIGNAL(drawDoneSignal(World&)),&TheWorld,SIGNAL(drawDoneSignal(World&)));
    connect(this,SIGNAL(keyPressSignal(World&,QKeyEvent&)),&TheWorld,SIGNAL(keyPressSignal(World&,QKeyEvent&)));
    connect(this,SIGNAL(keyReleaseSignal(World&,QKeyEvent&)),&TheWorld,SIGNAL(keyReleaseSignal(World&,QKeyEvent&)));
    connect(this,SIGNAL(blockCreateSignal(World&,Bnode&)),&TheWorld,SIGNAL(blockCreateSignal(World&,Bnode&)));
    connect(this,SIGNAL(blockDestroySignal(World&,Bnode&)),&TheWorld,SIGNAL(blockDestroySignal(World&,Bnode&)));
    QDir qdt(qApp->applicationDirPath());
    qdt.cd("plugins");
    PM.LoadFolder(qdt.absolutePath());
    for (QMap<QString,Plugin*>::iterator it=PM.Plugins.begin();it!=PM.Plugins.end();++it)
        it.value()->clientLoad(TheWorld);
}

void TesseractWidget::initializeGL() {
    glClearColor(.7,1,1,0);
    glPointSize(3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambient[]={1,1,1,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
}

void TesseractWidget::SetColor(Coordinate color) {
    GLfloat c[4]={GLfloat(color.x),GLfloat(color.y),GLfloat(color.z),1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c);
    glColor4fv(c);
}

void TesseractWidget::DrawBlock(Bnode TheBlock,int Mode) {
    const Coordinate Points[8]={Coordinate(1,1,1),Coordinate(1,1,-1),Coordinate(1,-1,1),Coordinate(1,-1,-1),Coordinate(-1,1,1),Coordinate(-1,1,-1),Coordinate(-1,-1,1),Coordinate(-1,-1,-1)};
    const int Sur[][4]={{0,2,3,1},{0,4,6,2},{4,5,7,6},{5,1,3,7},{0,1,5,4},{2,6,7,3}};
    const int Line[]={0,1,1,3,3,2,2,0,0,4,1,5,3,7,2,6,6,4,4,5,5,7,7,6};
    const float normal[][3]={{1,0,0},{0,0,1},{-1,0,0},{0,0,-1},{0,1,0},{0,-1,0}};
    if (Mode&2) {
        SetColor(TheWorld.BlockTypes[TheBlock.Type].Color);
        for (int i=0;i<6;++i) {
            glBegin(GL_POLYGON);
                glNormal3f(normal[i][0],normal[i][1],normal[i][2]);
                for (int j=0;j<4;++j) {
                    glVertex3f(TheBlock.Position.x+Points[Sur[i][j]].x*TheBlock.HalfSize.x,
                               TheBlock.Position.y+Points[Sur[i][j]].y*TheBlock.HalfSize.y,
                               TheBlock.Position.z+Points[Sur[i][j]].z*TheBlock.HalfSize.z);
                }
            glEnd();
        }
    }
    if (Mode&1) {
        SetColor(Coordinate(1,1,1));
        glBegin(GL_LINES);
            for (int i=0;i<24;++i)
                glVertex3f(TheBlock.Position.x+Points[Line[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Position.y+Points[Line[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Position.z+Points[Line[i]].z*TheBlock.HalfSize.z);
        glEnd();
    }
}

void TesseractWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75,aspect,.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(TheWorld.Myself->Position.x,TheWorld.Myself->Position.y,TheWorld.Myself->Position.z,TheWorld.Myself->LookAt.x,TheWorld.Myself->LookAt.y,TheWorld.Myself->LookAt.z,TheWorld.Myself->HeadVector.x,TheWorld.Myself->HeadVector.y,TheWorld.Myself->HeadVector.z);
    emit drawBeginSignal(TheWorld);
    for (QMap<int,Bnode>::iterator it=TheWorld.Blocks.begin();it!=TheWorld.Blocks.end();++it) {
        bool Cancel=0;
        emit drawBlockSignal(TheWorld,it.value(),Cancel);
        if (Cancel==0) {
            if (it.value().PointedAt==0)
                DrawBlock(it.value(),2);
            else
                DrawBlock(it.value(),3);
        }
    }
    if (creatingblock)
        DrawBlock(Bnode(currentblocktype,0,(TheWorld.Myself->LookAt+tempc)/2,((TheWorld.Myself->LookAt-tempc)/2).Abs()),1);
    SetColor(Coordinate(1,0,0));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    emit drawDoneSignal(TheWorld);
    SetColor(TheWorld.BlockTypes[currentblocktype].Color);
    renderText(20,20,currentblocktype);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glFlush();
}

void TesseractWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key()==Qt::Key_Escape)
        close();
    KeyStatus[int(e->text().toStdString()[0])]=1;
    emit keyPressSignal(TheWorld,*e);
}

void TesseractWidget::keyReleaseEvent(QKeyEvent *e) {
    KeyStatus[int(e->text().toStdString()[0])]=0;
    emit keyReleaseSignal(TheWorld,*e);
}

void TesseractWidget::mouseMoveEvent(QMouseEvent *event) {
    TheWorld.Myself->Turn(.01*(300-event->y()),.01*(400-event->x()));
    QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
}

void TesseractWidget::mousePressEvent(QMouseEvent *event) {
    QVector<QMap<int,Bnode>::iterator>vec;
    if (event->button()==Qt::LeftButton) {
        if (creatingblock) {
            Bnode b=Bnode(currentblocktype,0,(TheWorld.Myself->LookAt+tempc)/2,((TheWorld.Myself->LookAt-tempc)/2).Abs());
            QMap<int,Bnode>::iterator it=TheWorld.AddBlock(b); //Edit After Server
            emit blockCreateSignal(TheWorld,it.value());
            creatingblock=0;
        } else {
            tempc=TheWorld.Myself->LookAt;
            creatingblock=1;
        }
    } else if (event->button()==Qt::RightButton) {
        if (creatingblock)
            creatingblock=0;
        else {
            if ((vec=TheWorld.ThroughBlock(TheWorld.Myself->Position,TheWorld.Myself->LookAt)).size()) {
                emit blockDestroySignal(TheWorld,*vec[0]);
                TheWorld.RemoveBlock(vec[0]);  //Edit After Server
            }
        }
    }
}

void TesseractWidget::resizeGL(int width,int height) {
    if(!height)
        height=1;
    aspect=width/double(height);
    glViewport(0,0,(GLint)width,(GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
}

void TesseractWidget::wheelEvent(QWheelEvent *event) {
    QMap<QString,Block>::iterator it=TheWorld.BlockTypes.find(currentblocktype);
    if (event->delta()<0) {
        it+=1;
        if (it==TheWorld.BlockTypes.end())
            currentblocktype=TheWorld.BlockTypes.begin().key();
        else
            currentblocktype=it.key();
    } else if (event->delta()>0) {
        if (it==TheWorld.BlockTypes.begin())
            currentblocktype=(TheWorld.BlockTypes.end()-1).key();
        else
            currentblocktype=(it-1).key();
    }
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {
    while (!TheWorld.Blocks.empty())
        TheWorld.RemoveBlock(TheWorld.Blocks.begin());
    BASS_Free();
    while (!PM.Plugins.empty()) {
        PM.Plugins.begin().value()->clientUnload(TheWorld);
        delete PM.Plugins.begin().value();
        PM.Plugins.erase(PM.Plugins.begin());
    }
    while (!PM.Loaders.empty()) {
        PM.Loaders.begin().value()->unload();
        delete PM.Loaders.begin().value();
        PM.Loaders.erase(PM.Loaders.begin());
    }
    delete ui;
}

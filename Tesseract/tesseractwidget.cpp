#include "tesseractwidget.h"
#include "ui_tesseractwidget.h"

TesseractWidget::TesseractWidget(Socket *_TheSocket,int PlayerNum,QString PlayerName,QGLWidget *parent) : QGLWidget(parent), ui(new Ui::TesseractWidget) {
    ui->setupUi(this);
    TheSocket=_TheSocket;
    connect(TheSocket,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
    connect(TheSocket,SIGNAL(sockDisconnect(int,QString,quint16)),this,SLOT(sockDisconnect(int,QString,quint16)));
    memset(KeyStatus,0,sizeof(KeyStatus));
    creatingblock=0;
    mousetracked=1;
    TheWorld=new World;
    Player tp;
    tp.Name=PlayerName;
    TheWorld->Players.insert(PlayerNum,tp);
    TheWorld->Myself=TheWorld->Players.find(PlayerNum);
    PM=new PluginManager;
    PM->ClientLoadFolder("plugins",TheWorld,TheSocket);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    gt=new GameThread(TheWorld,KeyStatus,TheSocket);
    gt->start();
    GLTimer=new QTimer;
    GLTimer->start(16);
    connect(GLTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    TheWorld->RegisterBlock(Block("Stone",Coordinate(.2,.2,.2),"",1));
    currentblocktype="Stone";
    connect(TheWorld,SIGNAL(logSignal(QString)),this,SLOT(Log(QString)));
    connect(TheWorld,SIGNAL(releaseMouse()),this,SLOT(releaseMouse()));
    connect(TheWorld,SIGNAL(trackMouse()),this,SLOT(trackMouse()));
    QVariantMap qvm;
    qvm.insert("type","getbasic");
    emit TheSocket->sendVariantMap(qvm,-1);
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
        SetColor(TheWorld->BlockTypes[TheBlock.Type].Color);
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

void TesseractWidget::DrawPlayer(Player ThePlayer) {
    const Coordinate Points[8]={Coordinate(1,1,1),Coordinate(1,1,-1),Coordinate(1,-1,1),Coordinate(1,-1,-1),Coordinate(-1,1,1),Coordinate(-1,1,-1),Coordinate(-1,-1,1),Coordinate(-1,-1,-1)};
    const int Sur[][4]={{0,2,3,1},{0,4,6,2},{4,5,7,6},{5,1,3,7},{0,1,5,4},{2,6,7,3}};
    const float normal[][3]={{1,0,0},{0,0,1},{-1,0,0},{0,0,-1},{0,1,0},{0,-1,0}};
    for (int i=0;i<6;++i) {
        glBegin(GL_POLYGON);
            glNormal3f(normal[i][0],normal[i][1],normal[i][2]);
            for (int j=0;j<4;++j) {
                glVertex3f(ThePlayer.Position.x+Points[Sur[i][j]].x/2,
                           ThePlayer.Position.y+Points[Sur[i][j]].y/2,
                           ThePlayer.Position.z+Points[Sur[i][j]].z/2);
            }
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
    gluLookAt(TheWorld->Myself->Position.x,TheWorld->Myself->Position.y,TheWorld->Myself->Position.z,TheWorld->Myself->LookAt.x,TheWorld->Myself->LookAt.y,TheWorld->Myself->LookAt.z,TheWorld->Myself->HeadVector.x,TheWorld->Myself->HeadVector.y,TheWorld->Myself->HeadVector.z);
    emit TheWorld->drawBeginSignal();
    for (QMap<int,Bnode>::iterator it=TheWorld->Blocks.begin();it!=TheWorld->Blocks.end();++it) {
        bool Cancel=0;
        emit TheWorld->drawBlockSignal(it.value(),Cancel);
        if (Cancel==0) {
            if (it.value().PointedAt==0)
                DrawBlock(it.value(),2);
            else
                DrawBlock(it.value(),3);
        }
    }
    if (creatingblock)
        DrawBlock(Bnode(currentblocktype,(TheWorld->Myself->LookAt+tempc)/2,((TheWorld->Myself->LookAt-tempc)/2).Abs()),1);
    SetColor(Coordinate(.8,.8,.8));
    for (QMap<int,Player>::iterator it=TheWorld->Players.begin();it!=TheWorld->Players.end();++it)
        if (it!=TheWorld->Myself)
            DrawPlayer(it.value());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    emit TheWorld->drawDoneSignal();
    SetColor(TheWorld->BlockTypes[currentblocktype].Color);
    renderText(20,20,currentblocktype);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glFlush();
}

void TesseractWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key()==Qt::Key_Escape)
        close();
    KeyStatus[int(e->text().toStdString()[0])]=1;
    emit TheWorld->keyPressSignal(*e);
}

void TesseractWidget::keyReleaseEvent(QKeyEvent *e) {
    KeyStatus[int(e->text().toStdString()[0])]=0;
    emit TheWorld->keyReleaseSignal(*e);
}

void TesseractWidget::mouseMoveEvent(QMouseEvent *event) {
    if (mousetracked) {
        TheWorld->Myself->Turn(.01*(300-event->y()),.01*(400-event->x()));
        QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
    }
}

void TesseractWidget::mousePressEvent(QMouseEvent *event) {
    if (mousetracked) {
        QVector<QMap<int,Bnode>::iterator>vec;
        if (event->button()==Qt::LeftButton) {
            if (creatingblock) {
                Bnode b=Bnode(currentblocktype,(TheWorld->Myself->LookAt+tempc)/2,((TheWorld->Myself->LookAt-tempc)/2).Abs());
                QVariantMap qvm;
                qvm.insert("type","addblock");
                qvm.insert("bt",b.Type);
                qvm.insert("posx",b.Position.x);
                qvm.insert("posy",b.Position.y);
                qvm.insert("posz",b.Position.z);
                qvm.insert("hsx",b.HalfSize.x);
                qvm.insert("hsy",b.HalfSize.y);
                qvm.insert("hsz",b.HalfSize.z);
                emit TheSocket->sendVariantMap(qvm,-1);
                creatingblock=0;
            } else {
                tempc=TheWorld->Myself->LookAt;
                creatingblock=1;
            }
        } else if (event->button()==Qt::RightButton) {
            if (creatingblock)
                creatingblock=0;
            else {
                if ((vec=TheWorld->ThroughBlock(TheWorld->Myself->Position,TheWorld->Myself->LookAt)).size()) {
                    QVariantMap qvm;
                    qvm.insert("type","rmblock");
                    qvm.insert("num",vec[0].key());
                    emit TheSocket->sendVariantMap(qvm,-1);
                }
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
    if (mousetracked) {
        QMap<QString,Block>::iterator it=TheWorld->BlockTypes.find(currentblocktype);
        if (event->delta()<0) {
            it+=1;
            if (it==TheWorld->BlockTypes.end())
                currentblocktype=TheWorld->BlockTypes.begin().key();
            else
                currentblocktype=it.key();
        } else if (event->delta()>0) {
            if (it==TheWorld->BlockTypes.begin())
                currentblocktype=(TheWorld->BlockTypes.end()-1).key();
            else
                currentblocktype=(it-1).key();
        }
    }
}

void TesseractWidget::DrawScene() {updateGL();}

TesseractWidget::~TesseractWidget() {
    TheSocket->close();
    PM->ClientUnloadAll();
    delete ui;
}

void TesseractWidget::Log(QString s) {
    printf("%s\n",s.toUtf8().data());
}

void TesseractWidget::releaseMouse() {
    this->setMouseTracking(0);
    mousetracked=0;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void TesseractWidget::trackMouse() {
    QApplication::setOverrideCursor(Qt::BlankCursor);
    QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
    this->setMouseTracking(1);
    mousetracked=1;
}

void TesseractWidget::recvVariantMap(int,QString,quint16,QVariantMap qvm) {
    if (qvm["type"].toString()=="wsize") {
        TheWorld->Size=Coordinate(qvm["x"].toDouble(),qvm["y"].toDouble(),qvm["z"].toDouble());
        Player::CanGo=TheWorld->Size;
    } else if (qvm["type"].toString()=="addblock") {
        Bnode b=Bnode(qvm["bt"].toString(),Coordinate(qvm["posx"].toDouble(),qvm["posy"].toDouble(),qvm["posz"].toDouble()),Coordinate(qvm["hsx"].toDouble(),qvm["hsy"].toDouble(),qvm["hsz"].toDouble()));
        TheWorld->Blocks.insert(qvm["num"].toInt(),b);
        QMap<int,Bnode>::iterator it=TheWorld->Blocks.find(qvm["num"].toInt());
        emit TheWorld->blockCreateSignal(it.value());
    } else if (qvm["type"].toString()=="rmblock") {
        emit TheWorld->blockDestroySignal(TheWorld->Blocks.find(qvm["num"].toInt()).value());
        TheWorld->Blocks.remove(qvm["num"].toInt());
    } else if (qvm["type"].toString()=="rmuser") {
        TheWorld->Players.remove(qvm["num"].toInt());
    } else if (qvm["type"].toString()=="adduser") {
        Player p;
        p.Name=qvm["name"].toString();
        TheWorld->Players.insert(qvm["num"].toInt(),p);
    } else if (qvm["type"].toString()=="mvuser") {
        if (qvm["num"]!=TheWorld->Myself.key())
            TheWorld->Players[qvm["num"].toInt()].Position=Coordinate(qvm["x"].toInt(),qvm["y"].toInt(),qvm["z"].toInt());
    } else if (qvm["type"].toString()=="essentialplugin") {
        if (PM->Plugins.find(qvm["name"].toString())==PM->Plugins.end()) {
            QMessageBox::warning(0,"Exiting","Missing Plugin: "+qvm["name"].toString());
            close();
        }
    }
}

void TesseractWidget::sockDisconnect(int,QString,quint16) {
    QMessageBox::warning(0,"Exiting","Server is closed");
    close();
}

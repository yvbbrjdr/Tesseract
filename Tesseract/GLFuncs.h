#ifndef GLFUNCS_H
#define GLFUNCS_H

#include "tesseractwidget.h"
#include <cstdio>

void TesseractWidget::initializeGL() {
    glClearColor(.7,1,1,0);
    glPointSize(3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat pos[4]={0,GLfloat(w.size.y),0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
}

void TesseractWidget::SetColor(Coordinate color) {
    GLfloat c1[4]={GLfloat(color.x),GLfloat(color.y),GLfloat(color.z),1},c2[4]={0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,c1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,c2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,c1);
}

void TesseractWidget::DrawBlock(Bnode TheBlock,int Mode) {
    const Coordinate Points[8]={Coordinate(1,1,1),Coordinate(1,1,-1),Coordinate(1,-1,1),Coordinate(1,-1,-1),Coordinate(-1,1,1),Coordinate(-1,1,-1),Coordinate(-1,-1,1),Coordinate(-1,-1,-1)};
    const int Sur[][4]={{0,2,3,1},{0,4,6,2},{4,5,7,6},{5,1,3,7},{0,1,5,4},{2,6,7,3}};
    const int Line[]={0,1,1,3,3,2,2,0,0,4,1,5,3,7,2,6,6,4,4,5,5,7,7,6};
    const float normal[][3]={{1,0,0},{0,0,1},{-1,0,0},{0,0,-1},{0,1,0},{0,-1,0}};
    if (Mode&2) {
        SetColor(w.BlockTypes[TheBlock.Type].Color);
        glPolygonMode(GL_FRONT,GL_FILL);
        glPolygonMode(GL_BACK,GL_LINE);
        for (int i=0;i<6;++i) {
            glBegin(GL_POLYGON);
                glNormal3f(normal[i][0],normal[i][1],normal[i][2]);
                for (int j=0;j<4;++j) {
                    glVertex3f(TheBlock.Pos.x+Points[Sur[i][j]].x*TheBlock.HalfSize.x,
                               TheBlock.Pos.y+Points[Sur[i][j]].y*TheBlock.HalfSize.y,
                               TheBlock.Pos.z+Points[Sur[i][j]].z*TheBlock.HalfSize.z);
                }
            glEnd();
        }
    }
    if (Mode&1) {
        SetColor(Coordinate(1,1,1));
        glBegin(GL_LINES);
            for (int i=0;i<24;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line[i]].z*TheBlock.HalfSize.z);
    }
}

void TesseractWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75,aspect,.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    glColor3f(.1,1,.2);
    SetColor(Coordinate(0,1,0));
    glNormal3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(w.size.x/2,0,-w.size.z/2);
        glVertex3f(-w.size.x/2,0,-w.size.z/2);
        glVertex3f(-w.size.x/2,0,w.size.z/2);
        glVertex3f(w.size.x/2,0,w.size.z/2);
    glEnd();
    for (QList<Bnode>::iterator it=w.Blocks.begin();it!=w.Blocks.end();++it)
        if (w.ThroughBlock(it,p.pos,p.at)<0)
            DrawBlock(*it,2);
        else
            DrawBlock(*it,3);
    if (creatingblock)
        DrawBlock(Bnode(0,(p.at+tempc)/2,(p.at-tempc)/2),1);
    glColor3f(1,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glColor3f(0,0,0);
    renderText(20,20,"Tesseract Debug Data",QFont());
    char s[1000]={};
    sprintf(s,"Position: x=%.3f y=%.3f z=%.3f",p.pos.x,p.pos.y,p.pos.z);
    renderText(20,40,s,QFont());
    sprintf(s,"Orientation: Theta=%.3f Phi=%.3f",p.theta*180/PI,p.phi*180/PI);
    renderText(20,60,s,QFont());
    glFlush();
}

void TesseractWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Escape:
            while (!w.Blocks.empty())
                w.RemoveBlock(w.Blocks.begin());
            BASS_Free();
            close();
            break;
        case Qt::Key_R:
            p=Player(&w);
            break;
        case Qt::Key_F:
            w.AttachSoundToBlock(w.ThroughBlock(p.pos,p.at),"sample.mp3");
            break;
        case Qt::Key_G:
            w.DetachSoundFromBlock(w.ThroughBlock(p.pos,p.at));
            break;
        default:
            keystatus[int(e->text().toStdString()[0])]=1;
    }
}

void TesseractWidget::keyReleaseEvent(QKeyEvent *e) {keystatus[int(e->text().toStdString()[0])]=0;}

void TesseractWidget::mouseMoveEvent(QMouseEvent *event) {
    p.turn(.01*(300-event->y()),.01*(400-event->x()));
    QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
}

void TesseractWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        if (creatingblock) {
            w.AddBlock(0,(p.at+tempc)/2,(p.at-tempc)/2);
            creatingblock=0;
        } else {
            tempc=p.at;
            creatingblock=1;
        }
    } else if (event->button()==Qt::RightButton) {
        if (creatingblock)
            creatingblock=0;
        else
            w.RemoveBlock(w.ThroughBlock(p.pos,p.at));
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

#endif // GLFUNCS_H

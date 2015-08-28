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
}

void TesseractWidget::DrawBlock(Bnode TheBlock,int Mode) {
    const Coordinate Points[8]={Coordinate(1,1,1),Coordinate(1,1,-1),Coordinate(1,-1,1),Coordinate(1,-1,-1),Coordinate(-1,1,1),Coordinate(-1,1,-1),Coordinate(-1,-1,1),Coordinate(-1,-1,-1)};
    const int Sur1[]={0,1,2,3,6,7,4,5,0,1},Sur2[]={6,2,4,0,5,1,7,3};
    const int Line1[]={0,1,3,2,6,4,5,1},Line2[]={2,0,4},Line3[]={6,7,3,7,5};
    if (Mode&2) {
        glColor3f(w.BlockTypes[TheBlock.Type].Color.x,
                  w.BlockTypes[TheBlock.Type].Color.y,
                  w.BlockTypes[TheBlock.Type].Color.z);
        glBegin(GL_QUAD_STRIP);
            for (int i=0;i<10;++i)
                glVertex3f(TheBlock.Pos.x+Points[Sur1[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Sur1[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Sur1[i]].z*TheBlock.HalfSize.z);
        glEnd();
        glBegin(GL_QUAD_STRIP);
            for (int i=0;i<8;++i)
                glVertex3f(TheBlock.Pos.x+Points[Sur2[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Sur2[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Sur2[i]].z*TheBlock.HalfSize.z);
        glEnd();
    }
    if (Mode&1) {
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<8;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line1[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line1[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line1[i]].z*TheBlock.HalfSize.z);
        glEnd();
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<3;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line2[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line2[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line2[i]].z*TheBlock.HalfSize.z);
        glEnd();
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<5;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line3[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line3[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line3[i]].z*TheBlock.HalfSize.z);
        glEnd();
    }
    if (Mode&4) {
        glColor3f(1,1,1);
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<8;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line1[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line1[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line1[i]].z*TheBlock.HalfSize.z);
        glEnd();
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<3;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line2[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line2[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line2[i]].z*TheBlock.HalfSize.z);
        glEnd();
        glBegin(GL_LINE_STRIP);
            for (int i=0;i<5;++i)
                glVertex3f(TheBlock.Pos.x+Points[Line3[i]].x*TheBlock.HalfSize.x,
                           TheBlock.Pos.y+Points[Line3[i]].y*TheBlock.HalfSize.y,
                           TheBlock.Pos.z+Points[Line3[i]].z*TheBlock.HalfSize.z);
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
    gluLookAt(p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    glColor3f(.1,1,.2);
    glBegin(GL_QUADS);
        glVertex3f(w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,-w.size.z/2);
        glVertex3f(w.size.x/2,0,-w.size.z/2);
    glEnd();
    for (QList<Bnode>::iterator it=w.Blocks.begin();it!=w.Blocks.end();++it)
        if (w.ThroughBlock(it,p.pos,p.at)<0)
            DrawBlock(*it,3);
        else
            DrawBlock(*it,6);
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

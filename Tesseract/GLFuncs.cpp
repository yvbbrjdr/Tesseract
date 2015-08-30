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
}

void TesseractWidget::DrawBlock(Bnode TheBlock,int Mode) {
    const Coordinate Points[8]={Coordinate(1,1,1),Coordinate(1,1,-1),Coordinate(1,-1,1),Coordinate(1,-1,-1),Coordinate(-1,1,1),Coordinate(-1,1,-1),Coordinate(-1,-1,1),Coordinate(-1,-1,-1)};
    const int Sur[][4]={{0,2,3,1},{0,4,6,2},{4,5,7,6},{5,1,3,7},{0,1,5,4},{2,6,7,3}};
    const int Line[]={0,1,1,3,3,2,2,0,0,4,1,5,3,7,2,6,6,4,4,5,5,7,7,6};
    const float normal[][3]={{1,0,0},{0,0,1},{-1,0,0},{0,0,-1},{0,1,0},{0,-1,0}};
    if (Mode&2) {
        SetColor(w.BlockTypes[TheBlock.Type]->Color);
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
    SetColor(Coordinate(.1,1,.2));
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
        DrawBlock(Bnode(0/*To be edited*/,(p.at+tempc)/2,(p.at-tempc)/2),1);
    SetColor(Coordinate(1,0,0));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glFlush();
}

void TesseractWidget::keyPressEvent(QKeyEvent *e) {
    QList<Bnode>::iterator it;
    switch(e->key()) {
        case Qt::Key_Escape:
            while (!w.Blocks.empty())
                w.RemoveBlock(w.Blocks.begin());
            BASS_Free();
            close();
            break;
        case Qt::Key_R:
            p=Player(w.size);
            break;
        case Qt::Key_E:
            if ((it=w.ThroughBlock(p.pos,p.at))!=w.Blocks.end())
                w.BlockTypes[it->Type]->E(w,p,*it);
            break;
        case Qt::Key_F:
            if ((it=w.ThroughBlock(p.pos,p.at))!=w.Blocks.end())
                w.BlockTypes[it->Type]->F(w,p,*it);
            break;
        case Qt::Key_G:
            if ((it=w.ThroughBlock(p.pos,p.at))!=w.Blocks.end())
                w.BlockTypes[it->Type]->G(w,p,*it);
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

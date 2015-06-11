#ifndef GLFUNCS_H
#define GLFUNCS_H
#define mousespeed 0.01

#include "yjlvrsoundwidget.h"
#include <cstdio>

bool keystatus[128];
double aspect;

void yJLVRSoundWidget::initializeGL() {
    setGeometry(0,0,800,600);
    glClearColor(.7,1,1,0);
    glEnable(GL_DEPTH_TEST);
}

void yJLVRSoundWidget::SetSquare(int sx,int sy,int sz,int id){
    int idcolor[6][3]={{1,0,0},{1,0,0},{0,1,0},{0,1,0},{0,0,1},{0,0,1}};
    int squarepoint[8][3]={{1,1,-1},{1,1,1},{1,-1,1},{1,-1,-1},{-1,1,-1},{-1,1,1},{-1,-1,1},{-1,-1,-1}};
    int squareface[6][4]={{1,2,3,4},{5,6,7,8},{1,5,8,4},{2,6,7,3},{1,2,6,5},{4,3,7,8}};

        for(int i=0;i<6;i++)
        {
        glColor3f(idcolor[i][0],idcolor[i][1],idcolor[i][2]);
        glBegin(GL_QUADS);
            for(int j=0;j<4;j++)
            {
                glVertex3f(sx+squarepoint[squareface[i][j]-1][0],sy+squarepoint[squareface[i][j]-1][1],sz+squarepoint[squareface[i][j]-1][2]);
            }
        glEnd();
        }
/*    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex3f(2,0,4);
        glVertex3f(-2,0,4);
        glVertex3f(-2,4,4);
        glVertex3f(2,4,4);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(2,0,8);
        glVertex3f(-2,0,8);
        glVertex3f(-2,4,8);
        glVertex3f(2,4,8);
    glEnd();
    */
}

void yJLVRSoundWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75,aspect,.5,50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(p.pos.x,p.pos.y,p.pos.z,p.at.x,p.at.y,p.at.z,p.up.x,p.up.y,p.up.z);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,w.size.z/2);
        glVertex3f(-w.size.x/2,0,-w.size.z/2);
        glVertex3f(w.size.x/2,0,-w.size.z/2);
    glEnd();
    SetSquare(0,3,0,0);
    glColor3f(0,0,0);
    renderText(20,20,"yJLVRSound Debug Data",QFont());
    char s[1000]={};
    sprintf(s,"Position: x=%.3f y=%.3f z=%.3f",p.pos.x,p.pos.y,p.pos.z);
    renderText(20,40,s,QFont());
    sprintf(s,"Orientation: Theta=%.3f Phi=%.3f",p.theta*180/PI,p.phi*180/PI);
    renderText(20,60,s,QFont());
    //sprintf(s,"Debug Test Mouse Moving : X=%d Y=%d",debugX,debugY);
    //renderText(20,80,s,QFont());
    glFlush();
}

void yJLVRSoundWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_R:
            p=Player(&w);
            break;
        default:
            keystatus[int(e->text().toStdString()[0])]=1;
    }
}

void yJLVRSoundWidget::keyReleaseEvent(QKeyEvent *e) {keystatus[int(e->text().toStdString()[0])]=0;}

void yJLVRSoundWidget::mouseMoveEvent(QMouseEvent *event) {
    if((event->x()==400)&&(event->y()==300))return;
    //if(event->x()!=400)debugX=event->x();
    //if(event->y()!=300)debugY=event->y();
    p.turn(0,mousespeed*(400-event->x()));
    p.turn(mousespeed*(300-event->y()),0);
    QCursor::setPos(this->mapToGlobal(QPoint(400,300)));
}

void yJLVRSoundWidget::resizeGL(int width,int height) {
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

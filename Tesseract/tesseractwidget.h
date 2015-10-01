#ifndef TESSERACTWIDGET_H
#define TESSERACTWIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <bass.h>
#include <QTimer>
#include <QWheelEvent>
#include "Coordinate.h"
#include "GameThread.h"
#include "Socket.h"
#include <cstdio>

class PluginManager;

namespace Ui {
    class TesseractWidget;
}

class TesseractWidget : public QGLWidget {
    Q_OBJECT

public:
    explicit TesseractWidget(Socket *_TheSocket,QGLWidget *parent = 0);
    ~TesseractWidget();

public slots:
    void DrawScene();
    void Log(QString s);

public:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void resizeGL(int,int);
    void mousePressEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void DrawBlock(Bnode,int);
    void SetColor(Coordinate);
    World *TheWorld;
    bool KeyStatus[128];
    PluginManager *PM;
    Socket *TheSocket;

private:
    Ui::TesseractWidget *ui;
    GameThread *gt;
    QTimer *GLTimer;
    bool creatingblock;
    double aspect;
    Coordinate tempc;
    QString currentblocktype;

signals:
    void drawBlockSignal(World&,Bnode&,bool&);
    void drawBeginSignal(World&);
    void drawDoneSignal(World&);
    void keyPressSignal(World&,QKeyEvent&);
    void keyReleaseSignal(World&,QKeyEvent&);
    void blockCreateSignal(World&,Bnode&);
    void blockDestroySignal(World&,Bnode&);
};

#include "PluginManager.h"

#endif // TESSERACTWIDGET_H

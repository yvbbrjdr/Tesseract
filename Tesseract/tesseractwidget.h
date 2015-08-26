#ifndef TESSERACTWIDGET_H
#define TESSERACTWIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <bass.h>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QTime>
#include <QTimer>
#include "Block.h"
#include "Coordinate.h"
#include "Player.h"
#include "World.h"


class GameThread;

namespace Ui {
    class TesseractWidget;
}

class TesseractWidget : public QGLWidget {
    Q_OBJECT

public:
    explicit TesseractWidget(QGLWidget *parent = 0);
    ~TesseractWidget();

public slots:
    void DrawScene();

public:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void resizeGL(int,int);
    void mousePressEvent(QMouseEvent*);
    void SetListenerValues();
    void AddNewSound(Coordinate,QString);
    void DrawBlock(Bnode,int);
    void connectserver(QString);
    World w;
    Player p;
    bool keystatus[128],creatingblock;
    double aspect;
    Coordinate tempc;

private:
    Ui::TesseractWidget *ui;
    GameThread *gt;
    QTimer *GLTimer;
};

#endif // TESSERACTWIDGET_H

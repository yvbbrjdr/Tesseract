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
#include <QWheelEvent>
#include "Coordinate.h"

class GameThread;
class World;
class PluginManager;
class Bnode;

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
    void wheelEvent(QWheelEvent*);
    void DrawBlock(Bnode,int);
    void SetColor(Coordinate);
    static World TheWorld;
    static bool KeyStatus[128];
    static PluginManager PM;

private:
    Ui::TesseractWidget *ui;
    GameThread *gt;
    QTimer *GLTimer;
    bool creatingblock;
    double aspect;
    Coordinate tempc;
    QString currentblocktype;
};

#include "GameThread.h"
#include "PluginManager.h"

#endif // TESSERACTWIDGET_H

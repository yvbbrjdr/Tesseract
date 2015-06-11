#ifndef YJLVRSOUNDWIDGET_H
#define YJLVRSOUNDWIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <QtNetwork/QTcpSocket>
#include <QThread>
#include <QTime>
#include <QTimer>
#include "Coordinate.h"
#include "Player.h"
#include "World.h"

class GameThread;

namespace Ui {
    class yJLVRSoundWidget;
}

class yJLVRSoundWidget : public QGLWidget {
    Q_OBJECT

public:
    explicit yJLVRSoundWidget(QGLWidget *parent = 0);
    ~yJLVRSoundWidget();

public slots:
    void DrawScene();

protected:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void resizeGL(int,int);
    void SetSquare(int,int,int,int);

private:
    Ui::yJLVRSoundWidget *ui;
    GameThread *gt;
    QTimer *GLTimer;
};

#endif // YJLVRSOUNDWIDGET_H

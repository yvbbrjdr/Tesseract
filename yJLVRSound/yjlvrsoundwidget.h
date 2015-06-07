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
#include <QTimer>
#include "Coordinate.h"
#include "Player.h"
#include "World.h"

namespace Ui {
    class yJLVRSoundWidget;
}

class yJLVRSoundWidget : public QGLWidget {
    Q_OBJECT

public:
    explicit yJLVRSoundWidget(QGLWidget *parent = 0);
    ~yJLVRSoundWidget();

protected:
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent*);
    void resizeGL(int,int);

private:
    Ui::yJLVRSoundWidget *ui;
};

#endif // YJLVRSOUNDWIDGET_H

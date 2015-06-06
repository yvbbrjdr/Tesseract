#ifndef YJLVRSOUNDWIDGET_H
#define YJLVRSOUNDWIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>


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
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::yJLVRSoundWidget *ui;
};

#endif // YJLVRSOUNDWIDGET_H

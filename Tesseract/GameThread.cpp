#include "GameThread.h"

void GameThread::run() {
    while (1) {
        if (TesseractWidget::keystatus['w'])
            TesseractWidget::p.go(.1,0,0);
        if (TesseractWidget::keystatus['a'])
            TesseractWidget::p.go(0,.1,0);
        if (TesseractWidget::keystatus['s'])
            TesseractWidget::p.go(-.1,0,0);
        if (TesseractWidget::keystatus['d'])
            TesseractWidget::p.go(0,-.1,0);
        if (TesseractWidget::keystatus['x'])
            TesseractWidget::p.go(0,0,.1);
        if (TesseractWidget::keystatus['z'])
            TesseractWidget::p.go(0,0,-.1);
        Sound::SetListenerValues(TesseractWidget::p.pos,TesseractWidget::p.face,TesseractWidget::p.up);
        QTime dieTime=QTime::currentTime().addMSecs(10);
        while (QTime::currentTime()<dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

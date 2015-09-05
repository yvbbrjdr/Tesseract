#include "GameThread.h"

void GameThread::run() {
    while (1) {
        if (TesseractWidget::KeyStatus['w'])
            TesseractWidget::TheWorld.Myself->Go(.1,0,0);
        if (TesseractWidget::KeyStatus['a'])
            TesseractWidget::TheWorld.Myself->Go(0,.1,0);
        if (TesseractWidget::KeyStatus['s'])
            TesseractWidget::TheWorld.Myself->Go(-.1,0,0);
        if (TesseractWidget::KeyStatus['d'])
            TesseractWidget::TheWorld.Myself->Go(0,-.1,0);
        if (TesseractWidget::KeyStatus['x'])
            TesseractWidget::TheWorld.Myself->Go(0,0,.1);
        if (TesseractWidget::KeyStatus['z'])
            TesseractWidget::TheWorld.Myself->Go(0,0,-.1);
        Sound::SetListenerValues(TesseractWidget::TheWorld.Myself->Position,TesseractWidget::TheWorld.Myself->EyeVector,TesseractWidget::TheWorld.Myself->HeadVector);
        QTime dieTime=QTime::currentTime().addMSecs(10);
        while (QTime::currentTime()<dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

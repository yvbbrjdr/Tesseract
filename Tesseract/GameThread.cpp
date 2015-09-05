#include "GameThread.h"

GameThread::GameThread() {
    Cycle=0;
}

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
        if (Cycle%10==0){
            QVector<QMap<int,Bnode>::iterator> v=TesseractWidget::TheWorld.ThroughBlock(TesseractWidget::TheWorld.Myself->Position,TesseractWidget::TheWorld.Myself->LookAt);
            for (QMap<int,Bnode>::iterator it=TesseractWidget::TheWorld.Blocks.begin();it!=TesseractWidget::TheWorld.Blocks.end();++it)
                it->PointedAt=0;
            for (int i=0;i<v.size();++i)
                v[i]->PointedAt=1;
        }
        QTime dieTime=QTime::currentTime().addMSecs(10);
        while (QTime::currentTime()<dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ++Cycle;
    }
}

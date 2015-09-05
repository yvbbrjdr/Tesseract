#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include "tesseractwidget.h"

class GameThread : public QThread {
public:
    int Cycle;
    GameThread();
    void run();
};

#endif // GAMETHREAD_H

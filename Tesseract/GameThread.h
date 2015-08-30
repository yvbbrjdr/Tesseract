#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include "tesseractwidget.h"

class GameThread : public QThread {
public:
    void run();
};

#endif // GAMETHREAD_H

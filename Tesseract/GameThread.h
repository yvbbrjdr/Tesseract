#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include "World.h"
#include "Sound.h"
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

class GameThread : public QThread {
private:
    World *TheWorld;
    bool *KeyStatus;
    Socket *TheSocket;

public:
    int Cycle;
    GameThread(World *_TheWorld,bool *_KeyStatus,Socket *_TheSocket);
    void run();
};

#endif // GAMETHREAD_H

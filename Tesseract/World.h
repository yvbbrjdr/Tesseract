#ifndef WORLD_H
#define WORLD_H

#include "Block.h"
#include <QMap>
#include <QVector>
#include <QObject>
#include <QKeyEvent>
#include "Player.h"
#include "Socket.h"

class World : public QObject {
    Q_OBJECT
public:
    Coordinate Size;
    QMap<QString,Block>BlockTypes;
    QMap<int,Bnode>Blocks;
    QMap<int,Player>Players;
    QMap<int,Player>::iterator Myself;
    bool RegisterBlock(Block _BlockType);
    bool InBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position);
    QVector<QMap<int,Bnode>::iterator> InBlock(Coordinate Position);
    double ThroughBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position1,Coordinate Position2);
    QVector<QMap<int,Bnode>::iterator> ThroughBlock(Coordinate Position1, Coordinate Position2);

signals:
    void drawBlockSignal(Bnode&,bool&);
    void drawBeginSignal();
    void drawDoneSignal();
    void keyPressSignal(QKeyEvent&);
    void keyReleaseSignal(QKeyEvent&);
    void blockCreateSignal(Bnode&);
    void blockDestroySignal(Bnode&);
    void logSignal(QString);
    void releaseMouse();
    void trackMouse();
    void helpSignal();
    void processSignal(QVector<QString>&);
    void sendCommandSignal(QVector<QString>&);
};

#endif // WORLD_H

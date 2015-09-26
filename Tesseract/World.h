#ifndef WORLD_H
#define WORLD_H

#include "Block.h"
#include <QMap>
#include <QVector>
#include <QObject>
#include <QKeyEvent>
#include "Player.h"

class World : public QObject {
    Q_OBJECT
public:
    Coordinate Size;
    QMap<QString,Block>BlockTypes;
    QMap<int,Bnode>Blocks;
    QMap<int,Player>Players;
    QMap<int,Player>::iterator Myself;
    World();
    World(Coordinate _Size);
    bool RegisterBlock(Block _BlockType);
    QMap<int,Bnode>::iterator AddBlock(Bnode b);
    void RemoveBlock(QMap<int,Bnode>::iterator TheBlock);
    bool InBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position);
    QVector<QMap<int,Bnode>::iterator> InBlock(Coordinate Position);
    double ThroughBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position1,Coordinate Position2);
    QVector<QMap<int,Bnode>::iterator> ThroughBlock(Coordinate Position1, Coordinate Position2);

signals:
    void drawBlockSignal(World&,Bnode&,bool&);
    void drawBeginSignal(World&);
    void drawDoneSignal(World&);
    void keyPressSignal(World&,QKeyEvent&);
    void keyReleaseSignal(World&,QKeyEvent&);
    void blockCreateSignal(World&,Bnode&);
    void blockDestroySignal(World&,Bnode&);
};

#endif // WORLD_H

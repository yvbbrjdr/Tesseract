#ifndef WORLD_H
#define WORLD_H

#include "Block.h"
#include <QMap>
#include <QVector>
#include "Player.h"

class World {
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
};

#endif // WORLD_H

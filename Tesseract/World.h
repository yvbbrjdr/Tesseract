#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"
#include "Block.h"
#include <QMap>
#include <QVector>
#include "Player.h"
#include "Sound.h"

class World {
public:
    Coordinate Size;
    QVector<Block*>BlockTypes;
    QMap<int,Bnode>Blocks;
    QMap<int,Player>Players;
    QMap<int,Player>::iterator Myself;
    World();
    World(Coordinate);
    template<class T>int RegisterBlock(T BT);
    void AddBlock(int Type,Coordinate Position,Coordinate HalfSize);
    void RemoveBlock(QMap<int,Bnode>::iterator TheBlock);
    bool InBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position);
    QVector<QMap<int,Bnode>::iterator> InBlock(Coordinate Position);
    double ThroughBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position1,Coordinate Position2);
    QVector<QMap<int,Bnode>::iterator> ThroughBlock(Coordinate Position1, Coordinate Position2);
};

template<class T>int World::RegisterBlock(T BT) {
    T *b=new T;
    *b=BT;
    BlockTypes.push_back(b);
    return BlockTypes.size()-1;
}

#endif // WORLD_H

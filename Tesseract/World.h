#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"
#include "Block.h"
#include <QList>
#include <QVector>
#include "Player.h"
#include "Sound.h"

class World {
public:
    Coordinate size;
    QVector<Block>BlockTypes;
    QList<Bnode>Blocks;
    QList<Player>Players;
    World();
    World(Coordinate);
    int RegisterBlock(QString,Coordinate,QString,bool);
    void AddBlock(int,Coordinate,Coordinate);
    void RemoveBlock(QList<Bnode>::iterator);
    bool InBlock(QList<Bnode>::iterator,Coordinate);
    QList<Bnode>::iterator InBlock(Coordinate);
    double ThroughBlock(QList<Bnode>::iterator,Coordinate,Coordinate);
    QList<Bnode>::iterator ThroughBlock(Coordinate,Coordinate);
};

#endif // WORLD_H

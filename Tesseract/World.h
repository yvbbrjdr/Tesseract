#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"
#include "Block.h"
#include <QList>
#include <QVector>
#include "Player.h"

class World {
public:
    Coordinate size;
    QVector<Block>BlockTypes;
    QList<Bnode>Blocks;
    World();
    World(Coordinate);
    void SetListenerValues(Coordinate position,Coordinate face,Coordinate up);
    int RegisterBlock(QString,Coordinate,QString,bool);
    void AddBlock(int,Coordinate,Coordinate);
    void AttachSoundToBlock(QList<Bnode>::iterator,QString);
    void DetachSoundFromBlock(QList<Bnode>::iterator);
    void RemoveBlock(QList<Bnode>::iterator);
    bool InBlock(QList<Bnode>::iterator,Coordinate);
    QList<Bnode>::iterator InBlock(Coordinate);
    double ThroughBlock(QList<Bnode>::iterator,Coordinate,Coordinate);
    QList<Bnode>::iterator ThroughBlock(Coordinate,Coordinate);

private:
    HSTREAM AddNewSound(Coordinate,QString);
    void RemoveASound(HSTREAM);
};

#endif // WORLD_H

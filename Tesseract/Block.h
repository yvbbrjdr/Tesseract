#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>
#include <QList>
#include "Sound.h"
#include "Player.h"
#include <cstring>

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGoOut;
};

class Bnode {
public:
    int Type,Belong;
    Coordinate Position,HalfSize;
    bool PointedAt;
    void *Data;
    Bnode(int _Type,int _Belong,Coordinate _Position,Coordinate _HalfSize);
};

#endif // BLOCK_H

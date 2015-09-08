#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGoOut;
    Block();
    Block(QString _Name,Coordinate _Color,QString _TextureName,bool _SoundCanGoOut);
};

class Bnode {
public:
    QString Type;
    int Belong;
    Coordinate Position,HalfSize;
    bool PointedAt;
    void *Data;
    Bnode(QString _Type,int _Belong,Coordinate _Position,Coordinate _HalfSize);
};

#endif // BLOCK_H

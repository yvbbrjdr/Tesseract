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
    Block(const QString &_Name,const Coordinate &_Color,const QString &_TextureName,const bool &_SoundCanGoOut);
};

class Bnode {
public:
    QString Type;
    Coordinate Position,HalfSize;
    bool PointedAt;
    void *Data;
    Bnode(const QString &_Type,const Coordinate &_Position,const Coordinate &_HalfSize);
};

#endif // BLOCK_H

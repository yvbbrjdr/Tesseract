#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGetThrough;
};

struct Bnode {
    int Type;
    Coordinate Pos,HalfSize;
    HSTREAM hs;
    Bnode(int,Coordinate,Coordinate);
};

#endif // BLOCK_H

#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"

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
    Bnode(int Ty,Coordinate Po,Coordinate HS) {
        Type=Ty;
        Pos=Po;
        HalfSize=HS;
        hs=0;
    }

    Bnode(){}
};

#endif // BLOCK_H

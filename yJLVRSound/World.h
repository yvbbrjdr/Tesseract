#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"
#include "Block.h"
#include <QList>
#include <QVector>
using namespace std;

struct Bnode {
    int Type;
    Coordinate Pos,HalfSize;
    Bnode(int Ty,Coordinate Po,Coordinate HS) {
        Type=Ty;
        Pos=Po;
        HalfSize=HS;
    }
    Bnode(){}
};

class World {
public:
    Coordinate size;
    World(Coordinate s) {size=s;}
    QVector<Block>BlockTypes;
    int RegisterBlock(QString Name,Coordinate Color,QString TextureName,bool SoundCanGetThrough) {
        Block b;
        b.Name=Name;
        b.Color=Color;
        b.TextureName=TextureName;
        b.SoundCanGetThrough=SoundCanGetThrough;
        BlockTypes.push_back(b);
        return BlockTypes.size()-1;
    }
    QList<Bnode>Blocks;
    void AddBlock(int Type,Coordinate Pos,Coordinate HalfSize) {
        if (Type<BlockTypes.size()) {
            Bnode b(Type,Pos,HalfSize);
            Blocks.push_back(b);
        }
    }
};

#endif // WORLD_H

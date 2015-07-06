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
            HalfSize=HalfSize.Abs();
            Bnode b(Type,Pos,HalfSize);
            Blocks.push_back(b);
        }
    }
    void RemoveBlock(QList<Bnode>::iterator it) {
        if (it!=Blocks.end())
            Blocks.erase(it);
    }
    bool InBlock(QList<Bnode>::iterator TheBlock,Coordinate Pos) {
        Coordinate a=TheBlock->Pos-TheBlock->HalfSize,b=TheBlock->Pos+TheBlock->HalfSize;
        if (a.x<=Pos.x&&b.x>=Pos.x&&a.y<=Pos.y&&b.y>=Pos.y&&a.z<=Pos.z&&b.z>=Pos.z)
            return 1;
        return 0;
    }
    QList<Bnode>::iterator InBlock(Coordinate Pos) {
        for (QList<Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
            if (InBlock(it,Pos))
                return it;
        return Blocks.end();
    }
    bool ThroughBlock(QList<Bnode>::iterator TheBlock,Coordinate Pos1,Coordinate Pos2) {
        return 0;//TO BE ADDED
    }
    QList<Bnode>::iterator ThroughBlock(Coordinate Pos1, Coordinate Pos2) {
        for (QList<Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
            if (ThroughBlock(it,Pos1,Pos2))
                return it;
        return Blocks.end();
    }
};

#endif // WORLD_H

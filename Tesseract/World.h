#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"
#include "Block.h"
#include <QList>
#include <QVector>
#include "Player.h"
using namespace std;

struct Bnode {
    int Type;
    Coordinate Pos,HalfSize;
    Bnode(int Ty,Coordinate Po,Coordinate HS) {
        Type=Ty;
        Pos=Po;
        HalfSize=HS;
    }

    double dmin(double a,double b){
        return a>b?b:a;
    }

    double dmax(double a,double b){
        return a>b?a:b;
    }

    double GetPierceLength(Player p){
      double length=0;
      double dx[4][2]={0};
      dx[0][0]=Pos.x-HalfSize.x;
      dx[0][1]=Pos.x+HalfSize.x;
      dx[1][0]=p.at.x/p.at.y*(Pos.y-HalfSize.y-p.pos.y)+p.pos.x;
      dx[1][1]=p.at.x/p.at.y*(Pos.y+HalfSize.y-p.pos.y)+p.pos.x;
      dx[2][0]=p.at.x/p.at.z*(Pos.z-HalfSize.z-p.pos.z)+p.pos.x;
      dx[2][1]=p.at.x/p.at.z*(Pos.z+HalfSize.z-p.pos.z)+p.pos.x;
      for(int i=0;i<=2;i++)if (dx[i][0]>dx[i][1]){double c;c=dx[i][0];dx[i][0]=dx[i][1];dx[i][1]=c;}//Swap dx0 & dx1
      dx[3][0]=dmax(dmax(dx[0][0],dx[1][0]),dx[2][0]);
      dx[3][1]=dmin(dmin(dx[0][1],dx[1][1]),dx[2][1]);
      length=dx[3][1]-dx[3][0];
      if (length<=0)return 0;else return length;
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

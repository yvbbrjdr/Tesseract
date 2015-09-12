#include "World.h"

World::World() {}

World::World(Coordinate _Size) {
    Size=_Size;
    Players[0]=Player(_Size);
    Myself=Players.begin(); //Edit After Server
}

bool World::RegisterBlock(Block _BlockType) {
    if (BlockTypes.find(_BlockType.Name)!=BlockTypes.end())
        return 0;
    BlockTypes.insert(_BlockType.Name,_BlockType);
    return 1;
}

QMap<int,Bnode>::iterator World::AddBlock(Bnode b) {
    Blocks.insert((Blocks.end()-1).key()+1,b);
	return Blocks.end()-1;
}

void World::RemoveBlock(QMap<int,Bnode>::iterator TheBlock) {
    if (TheBlock!=Blocks.end()) {
        Blocks.erase(TheBlock);
    }
}

bool World::InBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position) {
    Coordinate a=TheBlock.value().Position-TheBlock.value().HalfSize,b=TheBlock.value().Position+TheBlock.value().HalfSize;
    return (a.x<=Position.x&&b.x>=Position.x&&a.y<=Position.y&&b.y>=Position.y&&a.z<=Position.z&&b.z>=Position.z);
}

QVector<QMap<int,Bnode>::iterator> World::InBlock(Coordinate Position) {
    QVector<QMap<int,Bnode>::iterator>ret;
    for (QMap<int,Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
        if (InBlock(it,Position))
            ret.push_back(it);
    return ret;
}

double World::ThroughBlock(QMap<int,Bnode>::iterator TheBlock,Coordinate Position1,Coordinate Position2) {
    double &x1=Position1.x,&y1=Position1.y,&z1=Position1.z,
           &x2=Position2.x,&y2=Position2.y,&z2=Position2.z,
           a=TheBlock.value().Position.x-TheBlock.value().HalfSize.x,
           b=TheBlock.value().Position.x+TheBlock.value().HalfSize.x,
           c=TheBlock.value().Position.y-TheBlock.value().HalfSize.y,
           d=TheBlock.value().Position.y+TheBlock.value().HalfSize.y,
           e=TheBlock.value().Position.z-TheBlock.value().HalfSize.z,
           f=TheBlock.value().Position.z+TheBlock.value().HalfSize.z;
    Coordinate point[6];
    point[0].x=a;
    point[0].y=(y1-y2)*(a-x1)/(x1-x2)+y1;
    point[0].z=(z1-z2)*(a-x1)/(x1-x2)+z1;
    point[1].x=b;
    point[1].y=(y1-y2)*(b-x1)/(x1-x2)+y1;
    point[1].z=(z1-z2)*(b-x1)/(x1-x2)+z1;
    point[2].x=(x1-x2)*(c-y1)/(y1-y2)+x1;
    point[2].y=c;
    point[2].z=(z1-z2)*(c-y1)/(y1-y2)+z1;
    point[3].x=(x1-x2)*(d-y1)/(y1-y2)+x1;
    point[3].y=d;
    point[3].z=(z1-z2)*(d-y1)/(y1-y2)+z1;
    point[4].x=(x1-x2)*(e-z1)/(z1-z2)+x1;
    point[4].y=(y1-y2)*(e-z1)/(z1-z2)+y1;
    point[4].z=e;
    point[5].x=(x1-x2)*(f-z1)/(z1-z2)+x1;
    point[5].y=(y1-y2)*(f-z1)/(z1-z2)+y1;
    point[5].z=f;
    int n=0,arr[2];
    for (int i=0;i<6;++i)
        if (InBlock(TheBlock,point[i]))
            arr[n++]=i;
    if (n<2)
        return -1;
    Coordinate Position[4]={Position1,Position2,point[arr[0]],point[arr[1]]};
    if (Position[0].x>Position[1].x) {
        Coordinate t=Position[0];
        Position[0]=Position[1];
        Position[1]=t;
    }
    if ((Position[2].x<Position[0].x||Position[2].x>Position[1].x)&&(Position[3].x<Position[0].x||Position[3].x>Position[1].x))
        return -1;
    for (int i=0;i<3;++i)
        for (int j=i+1;j<4;++j)
            if (Position[i].x>Position[j].x) {
                Coordinate t=Position[i];
                Position[i]=Position[j];
                Position[j]=t;
            }
    return (Position[2]-Position[1]).Length();
}

QVector<QMap<int,Bnode>::iterator> World::ThroughBlock(Coordinate Position1, Coordinate Position2) {
    QVector<QMap<int,Bnode>::iterator> ret;
    for (QMap<int,Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
        if (ThroughBlock(it,Position1,Position2)>=0)
            ret.push_back(it);
    return ret;
}

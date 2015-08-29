#include "World.h"

World::World() {}

World::World(Coordinate s) {
    size=s;
}

void World::SetListenerValues(Coordinate position,Coordinate face,Coordinate up) {
    BASS_3DVECTOR pos(position.x,position.y,position.z),front(face.x,face.y,face.z),top(up.x,up.y,up.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

HSTREAM World::AddNewSound(Coordinate Position,QString Filename) {
    HSTREAM hs=BASS_StreamCreateFile(FALSE,Filename.toStdString().c_str(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D|BASS_SAMPLE_LOOP);
    BASS_3DVECTOR v(Position.x,Position.y,Position.z);
    BASS_ChannelSet3DPosition(hs,&v,NULL,NULL);
    BASS_Apply3D();
    BASS_ChannelPlay(hs,FALSE);
    return hs;
}

void World::RemoveASound(HSTREAM hs) {
    if (hs!=0) {
        BASS_ChannelStop(hs);
        BASS_StreamFree(hs);
    }
}

int World::RegisterBlock(QString Name,Coordinate Color,QString TextureName,bool SoundCanGetThrough) {
    Block b;
    b.Name=Name;
    b.Color=Color;
    b.TextureName=TextureName;
    b.SoundCanGetThrough=SoundCanGetThrough;
    BlockTypes.push_back(b);
    return BlockTypes.size()-1;
}

void World::AddBlock(int Type,Coordinate Pos,Coordinate HalfSize) {
    if (Type<BlockTypes.size()) {
        HalfSize=HalfSize.Abs();
        Bnode b(Type,Pos,HalfSize);
        Blocks.push_back(b);
    }
}

void World::AttachSoundToBlock(QList<Bnode>::iterator TheBlock,QString Filename) {
    if (TheBlock!=Blocks.end()&&TheBlock->hs==0)
        TheBlock->hs=AddNewSound(TheBlock->Pos,Filename);
}

void World::DetachSoundFromBlock(QList<Bnode>::iterator TheBlock) {
    if (TheBlock!=Blocks.end()) {
        RemoveASound(TheBlock->hs);
        TheBlock->hs=0;
    }
}

void World::RemoveBlock(QList<Bnode>::iterator TheBlock) {
    if (TheBlock!=Blocks.end()) {
        DetachSoundFromBlock(TheBlock);
        Blocks.erase(TheBlock);
    }
}

bool World::InBlock(QList<Bnode>::iterator TheBlock,Coordinate Pos) {
    Coordinate a=TheBlock->Pos-TheBlock->HalfSize,b=TheBlock->Pos+TheBlock->HalfSize;
    return (a.x<=Pos.x&&b.x>=Pos.x&&a.y<=Pos.y&&b.y>=Pos.y&&a.z<=Pos.z&&b.z>=Pos.z);
}

QList<Bnode>::iterator World::InBlock(Coordinate Pos) {
    for (QList<Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
        if (InBlock(it,Pos))
            return it;
    return Blocks.end();
}

double World::ThroughBlock(QList<Bnode>::iterator TheBlock,Coordinate Pos1,Coordinate Pos2) {
    double &x1=Pos1.x,&y1=Pos1.y,&z1=Pos1.z,
           &x2=Pos2.x,&y2=Pos2.y,&z2=Pos2.z,
           a=TheBlock->Pos.x-TheBlock->HalfSize.x,
           b=TheBlock->Pos.x+TheBlock->HalfSize.x,
           c=TheBlock->Pos.y-TheBlock->HalfSize.y,
           d=TheBlock->Pos.y+TheBlock->HalfSize.y,
           e=TheBlock->Pos.z-TheBlock->HalfSize.z,
           f=TheBlock->Pos.z+TheBlock->HalfSize.z;
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
    Coordinate Pos[4]={Pos1,Pos2,point[arr[0]],point[arr[1]]};
    if (Pos[0].x>Pos[1].x) {
        Coordinate t=Pos[0];
        Pos[0]=Pos[1];
        Pos[1]=t;
    }
    if ((Pos[2].x<Pos[0].x||Pos[2].x>Pos[1].x)&&(Pos[3].x<Pos[0].x||Pos[3].x>Pos[1].x))
        return -1;
    for (int i=0;i<3;++i)
        for (int j=i+1;j<4;++j)
            if (Pos[i].x>Pos[j].x) {
                Coordinate t=Pos[i];
                Pos[i]=Pos[j];
                Pos[j]=t;
            }
    return (Pos[2]-Pos[1]).Length();
}

QList<Bnode>::iterator World::ThroughBlock(Coordinate Pos1, Coordinate Pos2) {
    for (QList<Bnode>::iterator it=Blocks.begin();it!=Blocks.end();++it)
        if (ThroughBlock(it,Pos1,Pos2)>=0)
            return it;
    return Blocks.end();
}

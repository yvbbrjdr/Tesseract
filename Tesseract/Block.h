#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>
#include <QList>
#include "Sound.h"
#include "Player.h"

class World;
class Bnode;

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGetThrough;
    virtual void E(World&,Player&,Bnode&)=0;
    virtual void F(World&,Player&,Bnode&)=0;
    virtual void G(World&,Player&,Bnode&)=0;
};

class Bnode {
public:
    int Type;
    Coordinate Pos,HalfSize;
    Bnode(int,Coordinate,Coordinate);
    void AttachSound(QString);
    void DetachSound();
    void PauseSound();
    bool SoundAttached();

private:
    HCHANNEL hc;
};

#endif // BLOCK_H

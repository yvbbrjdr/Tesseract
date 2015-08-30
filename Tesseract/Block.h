#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>
#include <QList>
#include "Sound.h"

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGetThrough;
};

class Bnode {
public:
    int Type;
    Coordinate Pos,HalfSize;
    Bnode(int,Coordinate,Coordinate);
    void AttachSound(QString);
    void DetachSound();
    bool SoundAttached();

private:
    HCHANNEL hc;
};

#endif // BLOCK_H

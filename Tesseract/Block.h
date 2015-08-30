#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>
#include <QList>
#include "Sound.h"
#include "Player.h"
#include <cstring>


class World;
class Bnode;
class TesseractWidget;

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGetThrough;
    virtual void Create(World&,Player&,Bnode&);
    virtual void E(World&,Player&,Bnode&);
    virtual void F(World&,Player&,Bnode&);
    virtual void G(World&,Player&,Bnode&);
    virtual void Global(World&,Player&,Bnode&);
    virtual void Destroy(World&,Player&,Bnode&);
};

class Bnode {
public:
    int Type;
    Coordinate Pos,HalfSize;
    void *Data;
    Bnode(int,Coordinate,Coordinate);
};

#include "tesseractwidget.h"

#endif // BLOCK_H

#ifndef SPEAKERBLOCK_H
#define SPEAKERBLOCK_H

#include "../Block.h"
#include "../World.h"
#include "../Player.h"
#include "../Sound.h"
#include <QFileDialog>

class Block;

class SpeakerBlock:public Block {
public:
    SpeakerBlock();
    virtual void Create(World&,Player&,Bnode&);
    virtual void E(World&,Player&,Bnode&);
    virtual void F(World&,Player&,Bnode&);
    virtual void G(World&,Player&,Bnode&);
    virtual void Destroy(World&,Player&,Bnode&);
};

#endif // SPEAKERBLOCK_H

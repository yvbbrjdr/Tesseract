#ifndef SPEAKERBLOCK_H
#define SPEAKERBLOCK_H

#include "../Block.h"
#include "../World.h"
#include "../Player.h"
#include <QFileDialog>

class SpeakerBlock:public Block {
public:
    SpeakerBlock();
    virtual void E(World&,Player&,Bnode&);
    virtual void F(World&,Player&,Bnode&);
    virtual void G(World&,Player&,Bnode&);
};

#endif // SPEAKERBLOCK_H

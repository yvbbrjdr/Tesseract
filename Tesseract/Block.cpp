#include "Block.h"

Bnode::Bnode(int Ty,Coordinate Po,Coordinate HS,bool created) {
    Type=Ty;
    Pos=Po;
    HalfSize=HS;
    Data=NULL;
    if (created)
        TesseractWidget::w.BlockTypes[Type]->Create(TesseractWidget::w,TesseractWidget::p,*this);
}

Bnode::~Bnode() {
    TesseractWidget::w.BlockTypes[Type]->Destroy(TesseractWidget::w,TesseractWidget::p,*this);
}

void Block::E(World&,Player&,Bnode&) {}

void Block::F(World&,Player&,Bnode&) {}

void Block::G(World&,Player&,Bnode&) {}

void Block::Global(World&,Player&,Bnode&) {}

void Block::Create(World&,Player&,Bnode&) {}

void Block::Destroy(World&,Player&,Bnode&) {}

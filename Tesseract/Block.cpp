#include "Block.h"

Bnode::Bnode(int Ty,Coordinate Po,Coordinate HS) {
    Type=Ty;
    Pos=Po;
    HalfSize=HS;
    hc=0;
}

void Bnode::AttachSound(QString Filename) {
    if (hc==0)
        hc=Sound::AddNewSound(Pos,Filename);
}

void Bnode::DetachSound() {
    Sound::RemoveASound(hc);
    hc=0;
}

bool Bnode::SoundAttached() {
    return hc;
}

#include "SpeakerBlock.h"

SpeakerBlock::SpeakerBlock() {
    Name="Speaker";
    Color=Coordinate(.5,0,0);
    TextureName="";
    SoundCanGetThrough=false;
}

void SpeakerBlock::E(World&,Player&,Bnode &b) {
    b.PauseSound();
}

void SpeakerBlock::F(World&,Player&,Bnode &b) {
    if (!b.SoundAttached()) {
        QFileDialog qfd;
        b.AttachSound(qfd.getOpenFileName(0,"","","MP3 Files(*.mp3);;Wave Files(*.wav)"));
    } else
        b.AttachSound("");
}

void SpeakerBlock::G(World&,Player&,Bnode &b) {
    b.DetachSound();
}

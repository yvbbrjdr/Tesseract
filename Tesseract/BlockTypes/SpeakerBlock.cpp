#include "SpeakerBlock.h"

SpeakerBlock::SpeakerBlock() {
    Name="Speaker";
    Color=Coordinate(.5,0,0);
    TextureName="";
    SoundCanGetThrough=false;
}

void SpeakerBlock::Create(World&,Player&,Bnode &b) {
    b.Data=malloc(sizeof(HCHANNEL));
}

void SpeakerBlock::E(World&,Player&,Bnode &b) {
	QFileDialog qfd;
    *(HCHANNEL*)(b.Data)=Sound::AddNewSound(b.Pos,qfd.getOpenFileName(0,"","","MP3 Files(*mp3);;Wave Files(*.wav)"));
    Sound::PlayASound(*(HCHANNEL*)b.Data);
}

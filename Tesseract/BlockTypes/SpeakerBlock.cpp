#include "SpeakerBlock.h"

SpeakerBlock::SpeakerBlock() {
    Name="Speaker";
    Color=Coordinate(.5,0,0);
    TextureName="";
    SoundCanGetThrough=false;
}

void SpeakerBlock::Create(World&,Player&,Bnode &b) {
    b.Data=new HCHANNEL;
    *(HCHANNEL*)(b.Data)=0;
}

void SpeakerBlock::E(World&,Player&,Bnode &b) {
    if (*(HCHANNEL*)(b.Data)==0) {
        QFileDialog qfd;
        *(HCHANNEL*)(b.Data)=Sound::AddNewSound(b.Pos,qfd.getOpenFileName(0,"","","MP3 Files(*mp3);;Wave Files(*.wav)"));
    }
    Sound::PlayASound(*(HCHANNEL*)b.Data);
}

void SpeakerBlock::F(World&,Player&,Bnode &b) {
    Sound::PauseASound(*(HCHANNEL*)b.Data);
}

void SpeakerBlock::G(World&,Player&,Bnode &b) {
    Sound::RemoveASound(*(HCHANNEL*)b.Data);
    *(HCHANNEL*)(b.Data)=0;
}

void SpeakerBlock::Destroy(World&,Player&,Bnode &b) {
    Sound::RemoveASound(*(HCHANNEL*)(b.Data));
    delete (HCHANNEL*)(b.Data);
}

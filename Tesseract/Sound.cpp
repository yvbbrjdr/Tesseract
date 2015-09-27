#include "Sound.h"

void Sound::SetListenerValues(Coordinate Position,Coordinate EyeVector,Coordinate HeadVector) {
    BASS_3DVECTOR pos(Position.x,Position.y,Position.z),front(EyeVector.x,EyeVector.y,EyeVector.z),top(HeadVector.x,HeadVector.y,HeadVector.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

HSTREAM Sound::AddNewFileSound(Coordinate Position, const QString &Filename) {
    HSTREAM hs=BASS_StreamCreateFile(FALSE,Filename.toLocal8Bit().data(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D|BASS_SAMPLE_LOOP);
    BASS_3DVECTOR v(Position.x,Position.y,Position.z);
    BASS_ChannelSet3DPosition(hs,&v,NULL,NULL);
    BASS_Apply3D();
    return hs;
}

void Sound::RemoveASound(HCHANNEL hc) {
    BASS_ChannelStop(hc);
    BASS_StreamFree(hc);
}

void Sound::PauseASound(HCHANNEL hc) {
    BASS_ChannelPause(hc);
}

void Sound::PlayASound(HCHANNEL hc) {
    BASS_ChannelPlay(hc,FALSE);
}

void Sound::StopASound(HCHANNEL hc) {
    BASS_ChannelStop(hc);
    BASS_ChannelSetPosition(hc,0,0);
}

void Sound::MoveASound(HCHANNEL hc,Coordinate Position) {
    BASS_3DVECTOR v(Position.x,Position.y,Position.z);
    BASS_ChannelSet3DPosition(hc,&v,NULL,NULL);
    BASS_Apply3D();
}

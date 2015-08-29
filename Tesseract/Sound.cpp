#include "Sound.h"

void Sound::SetListenerValues(Coordinate position,Coordinate face,Coordinate up) {
    BASS_3DVECTOR pos(position.x,position.y,position.z),front(face.x,face.y,face.z),top(up.x,up.y,up.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

HSTREAM Sound::AddNewSound(Coordinate Position,QString Filename) {
    HSTREAM hs=BASS_StreamCreateFile(FALSE,Filename.toStdString().c_str(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D|BASS_SAMPLE_LOOP);
    BASS_3DVECTOR v(Position.x,Position.y,Position.z);
    BASS_ChannelSet3DPosition(hs,&v,NULL,NULL);
    BASS_Apply3D();
    BASS_ChannelPlay(hs,FALSE);
    return hs;
}

void Sound::RemoveASound(HSTREAM hs) {
    if (hs!=0) {
        BASS_ChannelStop(hs);
        BASS_StreamFree(hs);
    }
}

void Sound::AttachSoundToBlock(QList<Bnode>::iterator TheBlock,QString Filename) {
    TheBlock->hs=AddNewSound(TheBlock->Pos,Filename);
}

void Sound::DetachSoundFromBlock(QList<Bnode>::iterator TheBlock) {
    RemoveASound(TheBlock->hs);
    TheBlock->hs=0;
}

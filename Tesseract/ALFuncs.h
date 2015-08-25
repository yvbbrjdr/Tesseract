#ifndef ALFUNCS_H
#define ALFUNCS_H

#include "tesseractwidget.h"
#include <cstring>

void SetListenerValues() {
    BASS_3DVECTOR pos(p.pos.x,p.pos.y,p.pos.z),front(p.face.x,p.face.y,p.face.z),top(p.up.x,p.up.y,p.up.z);
    BASS_Set3DPosition(&pos,NULL,&top,&front);
    BASS_Apply3D();
}

void AddNewSound(Coordinate Position,QString Filename) {
    HSTREAM hs=BASS_StreamCreateFile(FALSE,Filename.toStdString().c_str(),0,0,BASS_SAMPLE_MONO|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_3D|BASS_SAMPLE_LOOP);
    BASS_3DVECTOR v(Position.x,Position.y,Position.z);
    BASS_ChannelSet3DPosition(hs,&v,NULL,NULL);
    BASS_Apply3D();
    BASS_ChannelPlay(hs,FALSE);
}

#endif // ALFUNCS_H

#ifndef ALFUNCS_H
#define ALFUNCS_H

#include "tesseractwidget.h"
#include <cstring>

void SetListenerValues() {
    ALfloat Vel[]={0,0,0},LPos[]={float(p.pos.x),float(p.pos.y),float(p.pos.z)},LOri[]={float(p.at.x),float(p.at.y),float(p.at.z),float(p.up.x),float(p.up.y),float(p.up.z)};
    alListenerfv(AL_POSITION,LPos);
    alListenerfv(AL_VELOCITY,Vel);
    alListenerfv(AL_ORIENTATION,LOri);
}

void AddNewSound(Coordinate Position,QString Filename) {
    ALuint Buf,Source;
    ALfloat SPos[]={float(Position.x),float(Position.y),float(Position.z)},Vel[]={0,0,0};
    SetListenerValues();
    alGenBuffers(1,&Buf);
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;
    ALbyte fn[256];
    strcpy((char*)fn,Filename.toStdString().c_str());
    alutLoadWAVFile(fn,&format,&data,&size,&freq,&loop);
    alBufferData(Buf,format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);
    alGenSources(1,&Source);
    alSourcei(Source,AL_BUFFER,Buf);
    alSourcef(Source,AL_PITCH,1);
    alSourcef(Source,AL_GAIN,10);
    alSourcefv(Source,AL_POSITION,SPos);
    alSourcefv(Source,AL_VELOCITY,Vel);
    alSourcei(Source,AL_LOOPING,AL_TRUE);
    alSourcePlay(Source);
}

#endif // ALFUNCS_H

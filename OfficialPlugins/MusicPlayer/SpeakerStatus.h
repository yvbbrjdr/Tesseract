#ifndef SPEAKERSTATUS_H
#define SPEAKERSTATUS_H

enum PlayStatus{UNLOAD,STOP,PLAY,PAUSE};

#include <bass.h>
#include "../../Tesseract/Coordinate.h"
#include <QString>
#include "../../Tesseract/Sound.h"

class SpeakerStatus {
private:
    HCHANNEL hc;
public:
    SpeakerStatus();
    bool LoadFile(Coordinate Position,QString Filename);
    bool UnloadFile();
    bool Play();
    bool Pause();
    bool Stop();
    bool Move(Coordinate Position);
    int Status;
};

#endif // SPEAKERSTATUS_H

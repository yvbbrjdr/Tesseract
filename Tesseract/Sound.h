#ifndef SOUND
#define SOUND

#include "Block.h"
#include <bass.h>
#include <QList>

class Sound {
public:
    static void SetListenerValues(Coordinate position,Coordinate face,Coordinate up);
    static HSTREAM AddNewSound(Coordinate,QString);
    static void RemoveASound(HCHANNEL);
    static void PauseASound(HCHANNEL);
    static void PlayASound(HCHANNEL);
};

#endif // SOUND


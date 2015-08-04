#ifndef SOUND
#define SOUND

#include "Block.h"
#include <bass.h>
#include <QList>

class Sound {
public:
    static void SetListenerValues(Coordinate,Coordinate,Coordinate);
    static HSTREAM AddNewFileSound(Coordinate,QString);
    static void RemoveASound(HCHANNEL);
    static void PauseASound(HCHANNEL);
    static void PlayASound(HCHANNEL);
};

#endif // SOUND


#ifndef SOUND
#define SOUND

#include "Block.h"
#include <bass.h>
#include <QList>

class Sound {
public:
    static void SetListenerValues(Coordinate Position,Coordinate EyeVector,Coordinate HeadVector);
    static HSTREAM AddNewFileSound(Coordinate Position,QString Filename);
    static void RemoveASound(HCHANNEL hc);
    static void PauseASound(HCHANNEL hc);
    static void PlayASound(HCHANNEL hc);
};

#endif // SOUND


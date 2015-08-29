#ifndef SOUND
#define SOUND

#include "Block.h"
#include <bass.h>
#include <QList>

class Sound {
public:
    static void SetListenerValues(Coordinate position,Coordinate face,Coordinate up);
    static int RegisterBlock(QString,Coordinate,QString,bool);
    static HSTREAM AddNewSound(Coordinate,QString);
    static void RemoveASound(HSTREAM);
    static void AttachSoundToBlock(QList<Bnode>::iterator,QString);
    static void DetachSoundFromBlock(QList<Bnode>::iterator);
};

#endif // SOUND


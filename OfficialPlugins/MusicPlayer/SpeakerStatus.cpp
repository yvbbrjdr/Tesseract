#include "SpeakerStatus.h"

SpeakerStatus::SpeakerStatus() {
    Status=UNLOAD;
    hc=0;
}

bool SpeakerStatus::LoadFile(Coordinate Position,QString Filename) {
    if (Status!=UNLOAD)
        return 0;
    hc=Sound::AddNewFileSound(Position,Filename);
    if (hc==0)
        return 0;
    Status=STOP;
    return 1;
}

bool SpeakerStatus::UnloadFile() {
    if (Status==UNLOAD)
        return 0;
    Sound::RemoveASound(hc);
    Status=UNLOAD;
    return 1;
}

bool SpeakerStatus::Play() {
    if (Status==UNLOAD||Status==PLAY)
        return 0;
    Sound::PlayASound(hc);
    Status=PLAY;
    return 1;
}

bool SpeakerStatus::Pause() {
    if (Status==UNLOAD||Status==STOP||Status==PAUSE)
        return 0;
    Sound::PauseASound(hc);
    Status=PAUSE;
    return 1;
}

bool SpeakerStatus::Stop() {
    if (Status==UNLOAD||Status==STOP)
        return 0;
    Sound::StopASound(hc);
    Status=STOP;
    return 1;
}

bool SpeakerStatus::Move(Coordinate Position) {
    if (Status==UNLOAD)
        return 0;
    Sound::MoveASound(hc,Position);
    return 1;
}

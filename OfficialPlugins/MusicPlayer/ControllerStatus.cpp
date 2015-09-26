#include "ControllerStatus.h"

bool ControllerStatus::AddLink(Bnode &b) {
    if (b.Type!="Speaker"||Linked.indexOf(&b)!=-1)
        return 0;
    Linked.push_back(&b);
    return 1;
}

bool ControllerStatus::RemoveLink(Bnode &b) {
    if (Linked.indexOf(&b)==-1)
        return 0;
    Linked.remove(Linked.indexOf(&b));
    return 1;
}

void ControllerStatus::Play() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Play();
    }
}

void ControllerStatus::Pause() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Pause();
    }
}

void ControllerStatus::Stop() {
    for (int i=0;i<Linked.size();++i) {
        SpeakerStatus *ss=(SpeakerStatus*)Linked[i]->Data;
        ss->Stop();
    }
}

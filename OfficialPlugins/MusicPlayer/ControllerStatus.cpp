#include "ControllerStatus.h"

bool ControllerStatus::AddLink(Bnode &b) {
	if (Bnode.Type!="Speaker"||Linked.find(&b)!=Linked.end())
		return 0;
	Linked.push_back(&b);
	return 1;
}

bool ControllerStatus::RemoveLink(Bnode&) {
	if (Linked.find(&b)==Linked.end())
		return 0;
	Linked.erase(Linked.find(&b));
	return 1;
}

void ControllerStatus::Play() {
	for (int i=0;i<Linked.size();++i) {
		SpeakerStatus *ss=Linked[i]->Data;
		ss->Play();
	}
}

void ControllerStatus::Pause() {
	for (int i=0;i<Linked.size();++i) {
		SpeakerStatus *ss=Linked[i]->Data;
		ss->Pause();
	}
}

void ControllerStatus::Stop() {
	for (int i=0;i<Linked.size();++i) {
		SpeakerStatus *ss=Linked[i]->Data;
		ss->Stop();
	}
}

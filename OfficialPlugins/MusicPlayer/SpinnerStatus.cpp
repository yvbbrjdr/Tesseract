#include "SpinnerStatus.h"

SpinnerStatus::SpinnerStatus() {
	Spinning=0;
	Theta=0;
}

bool SpinnerStatus::AddLink(Bnode &b) {
    if (b.Type!="Speaker"||Linked.indexOf(&b)!=-1)
		return 0;
	Linked.push_back(&b);
	return 1;
}

bool SpinnerStatus::RemoveLink(Bnode &b) {
    if (Linked.indexOf(&b)==-1)
		return 0;
    Linked.remove(Linked.indexOf(&b));
	return 1;
}

bool SpinnerStatus::Start() {
	if (Spinning)
		return 0;
	Speed=0.167;
	Spinning=1;
    return 1;
}

bool SpinnerStatus::Stop() {
	if (!Spinning)
		return 0;
	Spinning=0;
	return 1;
}

bool SpinnerStatus::Accelerate() {
	if (!Spinning)
		return 0;
	Speed+=0.01;
	return 1;
}

#ifndef SPINNERSTATUS_H
#define SPINNERSTATUS_H

#include <QVector>
#include "SpeakerStatus.h"
#include "../../Tesseract/Block.h"

class SpinnerStatus {
public:
	QVector<Bnode*>Linked;
	double Speed,Theta;
	bool Spinning;
	SpinnerStatus();
	bool AddLink(Bnode&);
	bool RemoveLink(Bnode&);
	bool Start();
	bool Stop();
	bool Accelerate();
};

#endif // SPINNERSTATUS_H

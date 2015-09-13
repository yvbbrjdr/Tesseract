#ifndef CONTROLLERSTATUS_H
#define CONTROLLERSTATUS_H

#include <QVector>
#include "SpeakerStatus.h"
#include "../../Tesseract/Block.h"

class ControllerStatus {
private:
	QVector<Bnode*>Linked;
public:
	bool AddLink(Bnode&);
	bool RemoveLink(Bnode&);
	void Play();
	void Pause();
	void Stop();
};

#endif // CONTROLLERSTATUS_H

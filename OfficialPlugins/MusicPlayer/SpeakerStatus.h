#ifndef SPEAKERSTATUS_H
#define SPEAKERSTATUS_H

enum PlayStatus{Unload,Stop,Play,Pause};

class SpeakerStatus {
private:
	HCHANNEL hc;
public:
	SpeakerStatus();
	bool LoadFile(Coordinate Position,QString Filename);
	bool UnloadFile();
	bool Play();
	bool Pause();
	bool Stop();
	bool Move(Coordinate Position);
	int Status;
};

#endif // SPEAKERSTATUS_H

#include "SpeakerStatus.h"

SpeakerStatus::SpeakerStatus() {
	Status=PlayStatus::Unload;
	hc=0;
}

bool SpeakerStatus::LoadFile(Coordinate Position,QString Filename) {
	if (Status!=PlayStatus::Unload)
		return 0;
	hc=Sound::AddNewFileSound(Position,Filename);
	if (hc==0)
		return 0;
	Status=PlayStatus::Stop;
	return 1;
}

bool SpeakerStatus::UnloadFile() {
	if (Status==PlayStatus::Unload)
		return 0;
	Sound::RemoveASound(hc);
	Status=PlayStatus::Unload;
	return 1;
}

bool SpeakerStatus::Play() {
	if (Status==PlayStatus::Unload||Status==PlayStatus::Play)
		return 0;
	Sound::PlayASound(hc);
	Status=PlayStatus::Play;
	return 1;
}

bool SpeakerStatus::Pause() {
	if (Status==PlayStatus::Unload||Status==PlayStatus::Stop||Status==PlayStatus::Pause)
		return 0;
	Sound::PauseASound(hc);
	Status=PlayStatus::Pause;
	return 1;
}

bool SpeakerStatus::Stop() {
	if (Status==PlayStatus::Unload||Status==PlayStatus::Stop)
		return 0;
	Sound::StopASound(hc);
	Status=PlayStatus::Stop;
	return 1;
}

bool Move(Coordinate Position) {
	if (Status==PlayStatus::Unload)
		return 0;
	Sound::MoveASound(hc,Position);
	return 1;
}

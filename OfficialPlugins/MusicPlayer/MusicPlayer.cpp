#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    Name="MusicPlayer";
    SelectingObject=NULL;
}

void MusicPlayer::clientLoad(World &w) {
	HookKeyPress=
	HookBlockCreate=
	HookBlockDestroy=
	HookGlobal=1;
	w.RegisterBlock(Block("Speaker",Coordinate(.8,0,0),"",1));
	w.RegisterBlock(Block("Controller",Coordinate(0,0,.8),"",1));
	w.RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
}

void MusicPlayer::keyPressEvent(World &w,QKeyEvent &e) {
	QVector<QMap<int,Bnode>::iterator>v=w.ThroughBlock(w.Myself->Position,w.Myself->LookAt);
	if (!v.size())
        return;
	Bnode &b=v[0].value();
    if (b.Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
		if (e.key()==Qt::Key_E) {
            if (ss->Status==UNLOAD) {
				QFileDialog qfd;
                ss->LoadFile(b.Position,qfd.getOpenFileName(0,"","","MP3 Files(*.mp3);;Wave Files(*.wav)"));
			}
		} else if (e.key()==Qt::Key_L) {
			if (SelectingObject!=NULL) {
				if (SelectingObject->Type=="Controller") {
					ControllerStatus *cs=SelectingObject->Data;
					cs->AddLink(b);
				} else {
					SpinnerStatus *ss=SelectingObject->Data;
					ss->AddLink(b);
				}
				SelectingObject=NULL;
			}
		}
    } else if (b.Type=="Controller") {
		ControllerStatus *cs=(ControllerStatus*)b.Data;
		if (e.key()==Qt::Key_E) {
			cs->Play();
		} else if (e.key()==Qt::Key_F) {
			cs->Pause();
		} else if (e.key()==Qt::Key_G) {
			cs->Stop();
		} else if (e.key()==Qt::Key_L) {
			SelectingObject=&b;
		}
    } else if (b.Type=="Spinner") {
		SpinnerStatus *ss=(SpinnerStatus*)b.Data;
		if (e.key()==Qt::Key_E) {
			if (ss->Spinning)
				ss->Accelerate();
			else
				ss->Start();
		} else if (e.key()==Qt::Key_F) {
			ss->Stop();
		} else if (e.key()==Qt::Key_L) {
			SelectingObject=&b;
		}
	}
}

void MusicPlayer::blockCreateEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker")
		b.Data=new SpeakerStatus;
	else if (b.Type=="Controller") {
		b.Data=new ControllerStatus;
		Controllers.push_back(*b);
	}
	else if (b.Type=="Spinner") {
		b.Data=new SpinnerStatus;
		Spinners.push_back(*b);
	}
}

void MusicPlayer::blockDestroyEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
		ss->UnloadFile();
		delete ss;
	} else if (b.Type=="Controller") {
		ControllerStatus *cs=(ControllerStatus*)b.Data;
		Controllers.erase(Controllers.find(&b));
		delete cs;
	} else if (b.Type=="Spinner") {
		SpinnerStatus *ss=(SpinnerStatus*)b.Data;
		Spinner.erase(Spinners.find(&b));
		delete ss;
	}
	for (int i=0;i<Controllers.size();++i) {
		ControllerStatus *cs=(ControllerStatus*)Controllers[i]->Data;
		cs->RemoveLink(b);
	}
	for (int i=0;i<Spinners.size();++i) {
		SpinnerStatus *ss=(SpinnerStatus*)Spinners[i]->Data;
		ss->RemoveLink(b);
	}
}

void MusicPlayer:: globalEvent(World &w,QVector<QMap<int,Bnode>::iterator>) {
	for (int i=0;i<Spinners.size();++i) {
		Bnode &TheSpinner=*Spinners[i];
		SpinnerStatus *ss=(SpinnerStatus*)TheSpinner.Data;
		if (ss->Spinning)
			for (int j=0;j<TheSpinner.Linked.size();++j) {
				Bnode &b=*TheSpinner.Linked[i];
				SpeakerStatus *spst=(SpeakerStatus*)b.Data;
				double Radius=(b.Position-TheSpinner.Position).Length();
				b.Position=Coordinate(TheSpinner.Position.x+Radius*cos(Theta),b.Position.y,TheSpinner.Position.z+Radius*sin(Theta));
				spst->Move(b.Position);
			}
	}
	Theta+=Speed;
}

Q_EXPORT_PLUGIN2(MusicPlayer,MusicPlayer)

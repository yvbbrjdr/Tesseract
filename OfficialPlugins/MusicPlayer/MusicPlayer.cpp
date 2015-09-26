#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    Name="MusicPlayer";
    SelectingObject=NULL;
}

void MusicPlayer::clientLoad(World &w) {
	w.RegisterBlock(Block("Speaker",Coordinate(.8,.1,.1),"",1));
	w.RegisterBlock(Block("Controller",Coordinate(.1,.1,.8),"",1));
	w.RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
    connect(&w,SIGNAL(keyPressSignal(World&,QKeyEvent&)),this,SLOT(keyPressEvent(World&,QKeyEvent&)));
    connect(&w,SIGNAL(blockCreateSignal(World&,Bnode&)),this,SLOT(blockCreateEvent(World&,Bnode&)));
    connect(&w,SIGNAL(blockDestroySignal(World&,Bnode&)),this,SLOT(blockDestroyEvent(World&,Bnode&)));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(Spinning()));
    timer->start(10);
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
        } else if (e.key()==Qt::Key_F) {
            ss->UnloadFile();
        } else if (e.key()==Qt::Key_C) {
			if (SelectingObject!=NULL) {
				if (SelectingObject->Type=="Controller") {
                    ControllerStatus *cs=(ControllerStatus*)SelectingObject->Data;
					cs->AddLink(b);
				} else {
                    SpinnerStatus *ss=(SpinnerStatus*)SelectingObject->Data;
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
		} else if (e.key()==Qt::Key_C) {
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
		} else if (e.key()==Qt::Key_C) {
			SelectingObject=&b;
		}
	}
}

void MusicPlayer::blockCreateEvent(World &,Bnode &b) {
	if (b.Type=="Speaker")
		b.Data=new SpeakerStatus;
	else if (b.Type=="Controller") {
		b.Data=new ControllerStatus;
        Controllers.push_back(&b);
	}
	else if (b.Type=="Spinner") {
		b.Data=new SpinnerStatus;
        Spinners.push_back(&b);
	}
}

void MusicPlayer::blockDestroyEvent(World &,Bnode &b) {
	if (b.Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
		ss->UnloadFile();
		delete ss;
	} else if (b.Type=="Controller") {
        ControllerStatus *cs=(ControllerStatus*)b.Data;
        Controllers.remove(Controllers.indexOf(&b));
		delete cs;
	} else if (b.Type=="Spinner") {
        SpinnerStatus *ss=(SpinnerStatus*)b.Data;
        Spinners.remove(Spinners.indexOf(&b));
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

void MusicPlayer::Spinning() {
	for (int i=0;i<Spinners.size();++i) {
		Bnode &TheSpinner=*Spinners[i];
		SpinnerStatus *ss=(SpinnerStatus*)TheSpinner.Data;
        if (ss->Spinning) {
            for (int j=0;j<ss->Linked.size();++j) {
                Bnode &b=*ss->Linked[j];
				SpeakerStatus *spst=(SpeakerStatus*)b.Data;
                Coordinate r=b.Position-TheSpinner.Position;
                r.y=0;
                double Radius=r.Length();
                b.Position=Coordinate(TheSpinner.Position.x+Radius*cos(ss->Theta),b.Position.y,TheSpinner.Position.z+Radius*sin(ss->Theta));
				spst->Move(b.Position);
			}
            ss->Theta+=ss->Speed;
        }
	}
}

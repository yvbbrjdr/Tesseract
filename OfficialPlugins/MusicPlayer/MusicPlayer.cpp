#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    Name="MusicPlayer";
    HookKeyPress=
    HookBlockCreate=
    HookBlockDestroy=
    HookGlobal=1;
    SelectingObject=NULL;
}

void clientLoad(World &w) {
	w.RegisterBlock(Block("Speaker",Coordinate(.8,0,0),"",1));
	w.RegisterBlock(Block("Controller",Coordinate(0,0,.8),"",1));
	w.RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
}

void clientUnload(World &w) {

}

void keyPressEvent(World &w,QKeyEvent &e) {
	QVector<QMap<int,Bnode>::iterator>v=w.ThroughBlock(w.Myself->Position,w.Myself->LookAt);
	if (!v.size())
		return 0;
	Bnode &b=v[0].value();
	if (b.value().Type=="Speaker") {
		SpeakerStatus *ss=b.Data;
		if (e.key()==Qt::Key_E) {
			if (ss->Status==PlayStatus::Unload) {
				QFileDialog qfd;
				ss->LoadFile(b.Position,qfd.getOpenFileName); //Unsure
			}
		}
	} else if (b.value().Type=="Controller") {

	} else if (b.value().Type=="Spinner") {

	}
}

void blockCreateEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker")
		b.Data=new SpeakerStatus;
}

void blockDestroyEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker") {
		SpeakerStatus *ss=b.Data;
		ss->UnloadFile();
		delete ss;
	}
}

void globalEvent(World &w,QVector<QMap<int,Bnode>::iterator>v) {

}

Q_EXPORT_PLUGIN2(MusicPlayer,MusicPlayer)

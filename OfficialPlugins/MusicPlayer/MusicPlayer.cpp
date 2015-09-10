#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    Name="MusicPlayer";
    HookKeyPress=
    HookBlockCreate=
    HookBlockDestroy=
    HookGlobal=1;
    SelectingObject=NULL;
}

void MusicPlayer::clientLoad(World &w) {
	w.RegisterBlock(Block("Speaker",Coordinate(.8,0,0),"",1));
	w.RegisterBlock(Block("Controller",Coordinate(0,0,.8),"",1));
	w.RegisterBlock(Block("Spinner",Coordinate(.5,.5,0),"",1));
}

void MusicPlayer::clientUnload(World &w) {

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
		}
    } else if (b.Type=="Controller") {

    } else if (b.Type=="Spinner") {

	}
}

void MusicPlayer::blockCreateEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker")
		b.Data=new SpeakerStatus;
}

void MusicPlayer::blockDestroyEvent(World &w,Bnode &b) {
	if (b.Type=="Speaker") {
        SpeakerStatus *ss=(SpeakerStatus*)b.Data;
		ss->UnloadFile();
		delete ss;
	}
}

void MusicPlayer:: globalEvent(World &w,QVector<QMap<int,Bnode>::iterator>v) {

}

Q_EXPORT_PLUGIN2(MusicPlayer,MusicPlayer)

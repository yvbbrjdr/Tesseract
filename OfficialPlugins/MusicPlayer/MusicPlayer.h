#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "../../Tesseract/Plugin.h"
#include "SpeakerStatus.h"
#include "ControllerStatus.h"
#include "SpinnerStatus.h"
#include <cmath>
#include <QVector>

class MusicPlayer:public QObject,public Plugin {
    Q_OBJECT
    Q_INTERFACES(Plugin)
private:
	Bnode* SelectingObject;
	QVector<Bnode*>Spinners;
	QVector<Bnode*>Controllers;
public:
    MusicPlayer();
    virtual void clientLoad(World&);
    virtual void keyPressEvent(World&,QKeyEvent&);
    virtual void blockCreateEvent(World&,Bnode&);
    virtual void blockDestroyEvent(World&,Bnode&);
    virtual void globalEvent(World&,QVector<QMap<int,Bnode>::iterator>);
};

#endif // MUSICPLAYER_H

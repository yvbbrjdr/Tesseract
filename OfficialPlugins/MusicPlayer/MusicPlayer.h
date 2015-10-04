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
    Q_PLUGIN_METADATA(IID "MusicPlayer")
    Q_INTERFACES(Plugin)
private:
    Bnode* SelectingObject;
    QVector<Bnode*>Spinners;
    QVector<Bnode*>Controllers;
    QTimer *timer;
    World *TheWorld;
public:
    MusicPlayer();
    void clientLoad(World*,Socket*);
    void serverLoad(World*,Server*);
public slots:
    void keyPressEvent(QKeyEvent&);
    void blockCreateEvent(Bnode&);
    void blockDestroyEvent(Bnode&);
    void Spinning();
};

#endif // MUSICPLAYER_H

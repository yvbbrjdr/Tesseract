#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QKeyEvent>
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>

class World;
class Bnode;

class Plugin {
public:
    QString Name;
    bool Essential,HookKeyPress,HookKeyRelease,HookBlockCreate,HookBlockDestroy,HookGlobal,HookDrawBlock,HookDrawBegin,HookDrawDone;
    Plugin();
    virtual void clientLoad(World&);
    virtual void clientUnload(World&);
    virtual void serverLoad(World&);
    virtual void serverUnload(World&);
    virtual void drawBlockEvent(World&,Bnode&,bool&);
    virtual void drawBeginEvent(World&);
    virtual void drawDoneEvent(World&);
    virtual void keyPressEvent(World&,QKeyEvent&);
    virtual void keyReleaseEvent(World&,QKeyEvent&);
    virtual void blockCreateEvent(World&,Bnode&);
    virtual void blockDestroyEvent(World&,Bnode&);
    virtual void globalEvent(World&,QVector<QMap<int,Bnode>::iterator>);
    virtual ~Plugin();
};

#include "World.h"

Q_DECLARE_INTERFACE(Plugin,"tk.tesser.yvbbrjdr.Tesseract.Plugin/1.0")

#endif // PLUGIN_H

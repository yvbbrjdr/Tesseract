#ifndef PLUGIN_H
#define PLUGIN_H

#include "World.h"
#include <QKeyEvent>

class Plugin
{
public:
    bool HookKeyPress,HookKeyRelease,HookBlockCreate,HookBlockDestroy,HookGlobal,HookDrawBlock,OverrideDrawBlock;
    Plugin();
    virtual void clientLoad(World&)=0;
    virtual void cliendUnload(World&)=0;
    virtual void serverLoad(World&)=0;
    virtual void serverUnload(World&)=0;
    virtual void drawBlockEvent(World&,Bnode&)=0;
    virtual void keyPressEvent(World&,QKeyEvent&)=0;
    virtual void keyReleaseEvent(World&,QKeyEvent&)=0;
    virtual void blockCreateEvent(World&,Bnode&)=0;
    virtual void blockDestroyEvent(World&,Bnode&)=0;
    virtual void globalEvent(World&)=0;
    virtual ~Plugin()=0;
};

Q_DECLARE_INTERFACE(Plugin,"tk.tesser.yvbbrjdr.Tesseract.Plugin/1.0")

#endif // PLUGIN_H

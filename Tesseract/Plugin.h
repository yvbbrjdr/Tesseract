#ifndef PLUGIN_H
#define PLUGIN_H

#include "World.h"
#include <QKeyEvent>

class Plugin
{
public:
    bool HookKeyPress,HookKeyRelease,HookBlockCreate,HookBlockDestroy,HookGlobal,HookDrawBlock,OverrideDrawBlock;
    Plugin() {
        HookBlockCreate=
        HookBlockDestroy=
        HookGlobal=
        HookKeyPress=
        HookKeyRelease=
        HookDrawBlock=
        OverrideDrawBlock=0;
    }
    virtual void clientLoad(World&) {};
    virtual void cliendUnload(World&) {};
    virtual void serverLoad(World&) {};
    virtual void serverUnload(World&) {};
    virtual void drawBlockEvent(World&,Bnode&) {};
    virtual void keyPressEvent(World&,QKeyEvent&) {};
    virtual void keyReleaseEvent(World&,QKeyEvent&) {};
    virtual void blockCreateEvent(World&,Bnode&) {};
    virtual void blockDestroyEvent(World&,Bnode&) {};
    virtual void globalEvent(World&) {};
    virtual ~Plugin() {};
};

Q_DECLARE_INTERFACE(Plugin,"tk.tesser.yvbbrjdr.Tesseract.Plugin/1.0")

#endif // PLUGIN_H

#include "Plugin.h"

Plugin::Plugin() {
    Essential=
    HookBlockCreate=
    HookBlockDestroy=
    HookGlobal=
    HookKeyPress=
    HookKeyRelease=
    HookDrawBegin=
    HookDrawDone=
    HookDrawBlock=0;
}

void Plugin::clientLoad(World&) {}

void Plugin::clientUnload(World&) {}

void Plugin::serverLoad(World&) {}

void Plugin::serverUnload(World&) {}

void Plugin::drawBlockEvent(World&,Bnode&,bool&) {}

void Plugin::drawBeginEvent(World&) {}

void Plugin::drawDoneEvent(World&) {}

void Plugin::keyPressEvent(World&,QKeyEvent&) {}

void Plugin::keyReleaseEvent(World&,QKeyEvent&) {}

void Plugin::blockCreateEvent(World&,Bnode&) {}

void Plugin::blockDestroyEvent(World&,Bnode&) {}

void Plugin::globalEvent(World&,QVector<QMap<int,Bnode>::iterator>) {}

Plugin::~Plugin() {}

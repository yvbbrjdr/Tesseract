#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QKeyEvent>
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include "Sound.h"
#include "Socket.h"
#include "Server.h"

class World;

class Plugin {
public:
    QString Name;
    bool Essential;
    Plugin();
    virtual void clientLoad(World*,Socket*);
    virtual void clientUnload();
    virtual void serverLoad(World*,Server*);
    virtual void serverUnload();
    virtual ~Plugin();
};

#include "World.h"

Q_DECLARE_INTERFACE(Plugin,"tk.tesser.yvbbrjdr.Tesseract.Plugin/1.0")

#endif // PLUGIN_H

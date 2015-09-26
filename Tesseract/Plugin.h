#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QKeyEvent>
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include "Sound.h"

class World;
class Bnode;

class Plugin {
public:
    QString Name;
    virtual void clientLoad(World&);
    virtual void clientUnload(World&);
    virtual void serverLoad(World&);
    virtual void serverUnload(World&);
    virtual ~Plugin();
};

#include "World.h"

Q_DECLARE_INTERFACE(Plugin,"tk.tesser.yvbbrjdr.Tesseract.Plugin/1.0")

#endif // PLUGIN_H

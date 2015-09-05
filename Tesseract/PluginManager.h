#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QVector>
#include <QPluginLoader>
#include "Plugin.h"
#include <QDir>

class PluginManager {
public:
    QVector<Plugin*>Plugins;
    QVector<QPluginLoader*>Loaders;
    bool LoadPlugin(QString Filename);
    int LoadFolder(QString Path);
};

#endif // PLUGINMANAGER_H

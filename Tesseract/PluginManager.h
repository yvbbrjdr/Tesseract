#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QVector>
#include <QPluginLoader>
#include "Plugin.h"
#include <QDir>

class PluginManager {
public:
    QMap<QString,Plugin*>Plugins;
    QMap<QString,QPluginLoader*>Loaders;
    bool LoadPlugin(const QString &Filename);
    int LoadFolder(const QString &Path);
};

#endif // PLUGINMANAGER_H

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QVector>
#include <QPluginLoader>
#include "Plugin.h"
#include <QDir>

class PluginManager {
private:
    QMap<QString,QPluginLoader*>Loaders;
    QMap<QString,Plugin*>Plugins;

public:
    bool LoadPlugin(const QString &Filename);
    int ClientLoadFolder(const QString &Path,World &TheWorld);
    int ServerLoadFolder(const QString &Path,World &TheWorld);
    void ClientUnloadAll(World &TheWorld);
    void ServerUnloadAll(World &TheWorld);
};

#endif // PLUGINMANAGER_H

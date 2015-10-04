#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QVector>
#include <QPluginLoader>
#include "Plugin.h"
#include <QDir>

class PluginManager {

public:
    QMap<QString,QPluginLoader*>Loaders;
    QMap<QString,Plugin*>Plugins;
    bool LoadPlugin(const QString &Filename);
    int ClientLoadFolder(const QString &Path,World *TheWorld,Socket *TheSocket);
    int ServerLoadFolder(const QString &Path,World *TheWorld,Server *TheServer);
    void ClientUnloadAll();
    void ServerUnloadAll();
};

#endif // PLUGINMANAGER_H

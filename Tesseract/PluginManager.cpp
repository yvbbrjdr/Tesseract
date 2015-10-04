#include "PluginManager.h"

bool PluginManager::LoadPlugin(const QString &Filename) {
    QPluginLoader *qpl=new QPluginLoader(Filename);
    QObject *plugin=qpl->instance();
    if (!plugin)
        return 0;
    Plugin* ThePlugin=qobject_cast<Plugin*>(plugin);
    if (!ThePlugin)
        return 0;
    Loaders.insert(ThePlugin->Name,qpl);
    Plugins.insert(ThePlugin->Name,ThePlugin);
    return 1;
}

int PluginManager::ClientLoadFolder(const QString &Path,World *TheWorld,Socket *TheSocket) {
    int ret=0;
    QDir qd(Path);
    if (!qd.exists())
        return 0;
    qd.setFilter(QDir::Files);
    QFileInfoList list=qd.entryInfoList();
    int file_count=list.count();
    if (file_count<=0)
        return 0;
    for (QFileInfoList::iterator it=list.begin();it!=list.end();++it)
        if (LoadPlugin(it->absoluteFilePath())) {
            ++ret;
            (Plugins.end()-1).value()->clientLoad(TheWorld,TheSocket);
        }
    return ret;
}

int PluginManager::ServerLoadFolder(const QString &Path,World *TheWorld,Server *TheServer) {
    int ret=0;
    QDir qd(Path);
    if (!qd.exists())
        return 0;
    qd.setFilter(QDir::Files);
    QFileInfoList list=qd.entryInfoList();
    int file_count=list.count();
    if (file_count<=0)
        return 0;
    for (QFileInfoList::iterator it=list.begin();it!=list.end();++it)
        if (LoadPlugin(it->absoluteFilePath())) {
            ++ret;
            (Plugins.end()-1).value()->serverLoad(TheWorld,TheServer);
        }
    return ret;
}

void PluginManager::ClientUnloadAll() {
    while (!Plugins.empty()) {
        Plugins.begin().value()->clientUnload();
        delete Plugins.begin().value();
        Plugins.erase(Plugins.begin());
    }
    while (!Loaders.empty()) {
        Loaders.begin().value()->unload();
        delete Loaders.begin().value();
        Loaders.erase(Loaders.begin());
    }
}

void PluginManager::ServerUnloadAll() {
    while (!Plugins.empty()) {
        Plugins.begin().value()->serverUnload();
        delete Plugins.begin().value();
        Plugins.erase(Plugins.begin());
    }
    while (!Loaders.empty()) {
        Loaders.begin().value()->unload();
        delete Loaders.begin().value();
        Loaders.erase(Loaders.begin());
    }
}

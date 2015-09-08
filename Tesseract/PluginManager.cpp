#include "PluginManager.h"

bool PluginManager::LoadPlugin(QString Filename) {
    QPluginLoader *qpl=new QPluginLoader(Filename);
    if (!qpl->isLoaded())
        return 0;
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

int PluginManager::LoadFolder(QString Path) {
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
        if (LoadPlugin(it->absoluteFilePath()))
            ++ret;
    return ret;
}

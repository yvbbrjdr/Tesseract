/*
This file is part of the source code of Tesseract.
Tesseract is a block-based 3D VR Engine.

Copyright (C) 2015  yvbbrjdr

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "PluginManager.h"

bool PluginManager::LoadPlugin(const QString &Filename) {
    QPluginLoader *qpl=new QPluginLoader(Filename);
    QObject *plugin=qpl->instance();
    if (!plugin)
        return 0;
    Plugin* ThePlugin=qobject_cast<Plugin*>(plugin);
    if (!ThePlugin)
        return 0;
    if (Version::Verify(ThePlugin->TesseractVersion)) {
        Loaders.insert(ThePlugin->Name,qpl);
        Plugins.insert(ThePlugin->Name,ThePlugin);
        return 1;
    }
    return 0;
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

#ifndef PLUGINTEMPLATE_H
#define PLUGINTEMPLATE_H

#include "../../Tesseract/Plugin.h"

class PluginTemplate:public QObject,public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PluginTemplate")
    Q_INTERFACES(Plugin)
public:
    PluginTemplate();
};

#endif // PLUGINTEMPLATE_H

#ifndef BASICDRAWINGELEMENTS_H
#define BASICDRAWINGELEMENTS_H

#include "../../Tesseract/Plugin.h"
#include <QString>


class BasicDrawingElements:public QObject,public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "BasicDrawingElements")
    Q_INTERFACES(Plugin)
private:
    World *TheWorld;
public:
    BasicDrawingElements();
    void clientLoad(World*,Socket*);
public slots:
    void drawBeginEvent();
    void drawDoneEvent();
};

#endif // BASICDRAWINGELEMENTS_H

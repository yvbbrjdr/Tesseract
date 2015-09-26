#ifndef BASICDRAWINGELEMENTS_H
#define BASICDRAWINGELEMENTS_H

#include "../../Tesseract/Plugin.h"
#include <QString>


class BasicDrawingElements:public QObject,public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "BasicDrawingElements")
    Q_INTERFACES(Plugin)
public:
    BasicDrawingElements();
    void clientLoad(World &);
public slots:
    void drawBeginEvent(World&);
    void drawDoneEvent(World&);
};

#endif // BASICDRAWINGELEMENTS_H

#ifndef BASICDRAWINGELEMENTS_H
#define BASICDRAWINGELEMENTS_H

#include "../../Tesseract/Plugin.h"


class BasicDrawingElements:public QObject,public Plugin {
    Q_OBJECT
    Q_INTERFACES(Plugin)
public:
    BasicDrawingElements();
    virtual void drawBeginEvent(World&);
    virtual void drawDoneEvent(World&);
};

#endif // BASICDRAWINGELEMENTS_H

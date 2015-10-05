#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "../../Tesseract/Plugin.h"

class UserControl:public QObject,public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "UserControl")
    Q_INTERFACES(Plugin)
private:
    World *TheWorld;
    Server *TheServer;
    Socket *TheSocket;

public:
    UserControl();
    void clientLoad(World*,Socket*);
    void serverLoad(World*,Server*);

private slots:
    void showhelp();
    void process(QVector<QString>&);
    void recvVariantMap(int,QString,quint16,QVariantMap);
};

#endif // USERCONTROL_H

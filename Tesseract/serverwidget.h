#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QMainWindow>
#include "Server.h"
#include "World.h"
#include "PluginManager.h"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWidget(quint16 port,QWidget *parent = 0);
    ~ServerWidget();
    Server *TheServer;
    World *TheWorld;
    PluginManager *PM;

public slots:
    void on_lineEdit_returnPressed();
    void Log(QString s);
    void newClient(int socket,QString ip,quint16 port);
    void Process(QVector<QString> &v);
    void recvVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void userLogOff(int,QString,quint16);

private:
    Ui::ServerWidget *ui;
};

#endif // SERVERWIDGET_H

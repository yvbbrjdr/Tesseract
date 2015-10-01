#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QMainWindow>
#include "Server.h"
#include "World.h"

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

public slots:
    void on_lineEdit_returnPressed();
    void Log(QString s);
    void newClient(int socket,QString ip,quint16 port);
    void Process(QVector<QString> &v);
    void receiveData(int socket,QString ip,quint16 port,QByteArray qba);

private:
    Ui::ServerWidget *ui;
};

#endif // SERVERWIDGET_H

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "Socket.h"
#include <QThread>

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent=0);
    ~Server();

signals:
    void connectClient(const int,const QString&,const quint16);
    void readVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void sockDisconnect(const int,const QString&,const quint16);
    void sendVariantMap(const QVariantMap&,const int);

private slots:
    void setVariantMap(const QVariantMap &data,const int handle);
    void sockDisconnectSlot(int handle,QString ip,quint16 port);

protected:
    void incomingConnection(qintptr handle);

private:
    QMap<int,Socket*>*Clients;
};

#endif // SERVER_H

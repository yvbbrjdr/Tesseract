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
    void readData(const int,const QString&,const quint16,const QByteArray&);
    void sockDisconnect(const int,const QString&,const quint16);
    void sendData(const QByteArray&,const int);

public slots:
    void setData(const QByteArray &data,const int handle);
    void sockDisconnectSlot(int handle,QString ip,quint16 port);

protected:
    void incomingConnection(qintptr handle);

private:
    QMap<int,Socket*>*Clients;
};

#endif // SERVER_H

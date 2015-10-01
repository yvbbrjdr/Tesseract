#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class Socket : public QTcpSocket {
    Q_OBJECT
public:
    explicit Socket(qintptr socketDescriptor,QObject *parent=0);

signals:
    void sockDisconnect(int,QString,quint16);
    void readData(const int,const QString&,const quint16,const QByteArray&);

public slots:
    void thisReadData();
    void sendData(const QByteArray &data,const int id=-1);

private:
    qintptr socketID;
};

#endif // SOCKET_H

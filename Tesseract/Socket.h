#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>

class Socket : public QTcpSocket {
    Q_OBJECT
public:
    explicit Socket(qintptr socketDescriptor,QObject *parent=0);

signals:
    void sockDisconnect(const int,QString,quint16);
    void readVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void sendVariantMap(const QVariantMap&,const int);

private slots:
    void thisReadData();
    void setVariantMap(const QVariantMap &qvm,const int id=-1);
    void emitDisconnect();

private:
    qintptr socketID;
    QString buffer;
};

#endif // SOCKET_H

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
    void sockDisconnect(int,QString,quint16);
    void readVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void sendVariantMap(const QVariantMap&,const int);

private slots:
    void thisReadData();

public slots:
    void setVariantMap(const QVariantMap &qvm,const int id=-1);

private:
    qintptr socketID;
    QString buffer;
};

#endif // SOCKET_H

#include "Socket.h"

Socket::Socket(qintptr socketDescriptor,QObject *parent) : QTcpSocket(parent) {
    if (socketDescriptor>0) {
        this->setSocketDescriptor(socketDescriptor);
        socketID=socketDescriptor;
    }
    connect(this,SIGNAL(readyRead()),this,SLOT(thisReadData()));
    connect(this,SIGNAL(sendVariantMap(QVariantMap,int)),this,SLOT(setVariantMap(QVariantMap,int)));
    connect(this,SIGNAL(disconnected()),this,SLOT(emitDisconnect()));
}

void Socket::setVariantMap(const QVariantMap &data, const int id) {
    if (id==socketID||id==-1) {
        write(QJsonDocument::fromVariant(data).toJson());
    }
}

void Socket::thisReadData() {
    buffer+=readAll();
    int pos=buffer.indexOf('}');
    if (pos>=0) {
        QString t=buffer.mid(0,pos+1);
        buffer=buffer.mid(pos+1,buffer.size()-pos);
        emit readVariantMap(socketID,peerAddress().toString(),peerPort(),QJsonDocument::fromJson(t.toUtf8()).toVariant().toMap());
    }
}

void Socket::emitDisconnect() {
    emit sockDisconnect(socketID,peerAddress().toString(),peerPort());
}

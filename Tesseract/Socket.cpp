#include "Socket.h"

Socket::Socket(qintptr socketDescriptor,QObject *parent) : QTcpSocket(parent) {
    if (socketDescriptor>0) {
        this->setSocketDescriptor(socketDescriptor);
        socketID=socketDescriptor;
    }
    connect(this,SIGNAL(readyRead()),this,SLOT(thisReadData()));
}

void Socket::sendData(const QByteArray &data, const int id) {
    if (id==socketID||id==-1)
        write(data);
}

void Socket::thisReadData() {
    emit readData(socketID,peerAddress().toString(),peerPort(),readAll());
}

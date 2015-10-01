#include "Server.h"

Server::Server(QObject*) {
    Clients=new QMap<int,Socket*>;
}

void Server::incomingConnection(qintptr handle) {
    Socket *tempSock=new Socket(handle);
    QThread *tt=new QThread(tempSock);
    connect(tempSock,SIGNAL(readData(int,QString,quint16,QByteArray)),this,SIGNAL(readData(int,QString,quint16,QByteArray)));
    connect(tempSock,SIGNAL(sockDisconnect(int,QString,quint16)),this,SLOT(sockDisconnectSlot(int,QString,quint16)));
    connect(this,SIGNAL(sendData(QByteArray,int)),tempSock,SLOT(sendData(QByteArray,int)));
    connect(tempSock,SIGNAL(disconnected()),tt,SLOT(quit()));
    tempSock->moveToThread(tt);
    tt->start();
    Clients->insert(handle,tempSock);
    emit connectClient(tempSock->socketDescriptor(),tempSock->peerAddress().toString(),tempSock->peerPort());
}

void Server::setData(const QByteArray &data, const int handle) {
    emit sendData(data,handle);
}

void Server::sockDisconnectSlot(int handle, QString ip, quint16 port) {
    Socket *tcp=Clients->value(handle);
    Clients->remove(handle);
    delete tcp;
    emit sockDisconnect(handle,ip,port);
}

Server::~Server() {
    while (!Clients->empty()) {
        Clients->begin().value()->disconnectFromHost();
        emit Clients->begin().value()->disconnected();
    }
    delete Clients;
}

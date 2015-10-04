#include "Server.h"

Server::Server(QObject*) {
    Clients=new QMap<int,Socket*>;
}

void Server::incomingConnection(qintptr handle) {
    Socket *tempSock=new Socket(handle);
    QThread *tt=new QThread(tempSock);
    connect(tempSock,SIGNAL(readVariantMap(int,QString,quint16,const QVariantMap&)),this,SIGNAL(readVariantMap(int,QString,quint16,const QVariantMap&)));
    connect(tempSock,SIGNAL(sockDisconnect(const int,QString,quint16)),this,SLOT(sockDisconnectSlot(const int,QString,quint16)));
    connect(this,SIGNAL(sendVariantMap(const QVariantMap&,int)),tempSock,SIGNAL(sendVariantMap(const QVariantMap&,int)));
    connect(tempSock,SIGNAL(disconnected()),tt,SLOT(quit()));
    tempSock->moveToThread(tt);
    tt->start();
    Clients->insert(handle,tempSock);
    emit connectClient(tempSock->socketDescriptor(),tempSock->peerAddress().toString(),tempSock->peerPort());
}

void Server::setVariantMap(const QVariantMap &data, const int handle) {
    emit sendVariantMap(data,handle);
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

/*
This file is part of the source code of Tesseract.
Tesseract is a block-based 3D VR Engine.

Copyright (C) 2015  yvbbrjdr

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

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

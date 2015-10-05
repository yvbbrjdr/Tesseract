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
    for (;pos>=0;pos=buffer.indexOf('}')) {
        QString t=buffer.mid(0,pos+1);
        buffer=buffer.mid(pos+1,buffer.size()-pos);
        emit readVariantMap(socketID,peerAddress().toString(),peerPort(),QJsonDocument::fromJson(t.toUtf8()).toVariant().toMap());
    }
}

void Socket::emitDisconnect() {
    emit sockDisconnect(socketID,peerAddress().toString(),peerPort());
}

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
    void readVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void sockDisconnect(const int,const QString&,const quint16);
    void sendVariantMap(const QVariantMap&,const int);

private slots:
    void setVariantMap(const QVariantMap &data,const int handle);
    void sockDisconnectSlot(int handle,QString ip,quint16 port);

protected:
    void incomingConnection(qintptr handle);

private:
    QMap<int,Socket*>*Clients;
};

#endif // SERVER_H

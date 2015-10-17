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

#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QMainWindow>
#include "Server.h"
#include "World.h"
#include "PluginManager.h"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWidget(quint16 port,QWidget *parent = 0);
    ~ServerWidget();
    Server *TheServer;
    World *TheWorld;
    PluginManager *PM;

public slots:
    void on_lineEdit_returnPressed();
    void Log(const QString &s);
    void newClient(int socket,QString ip,quint16 port);
    void Process(QVector<QString> &v);
    void Process(const QString &comm);
    void recvVariantMap(const int,const QString&,const quint16,const QVariantMap&);
    void userLogOff(int,QString,quint16);

private:
    Ui::ServerWidget *ui;
};

#endif // SERVERWIDGET_H

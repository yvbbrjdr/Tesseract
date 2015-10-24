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

#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(quint16 port,QWidget *parent) : QMainWindow(parent),ui(new Ui::ServerWidget) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    Log("Welcome to Tesseract Server");
    TheServer=new Server;
    connect(TheServer,SIGNAL(connectClient(int,QString,quint16)),this,SLOT(newClient(int,QString,quint16)));
    connect(TheServer,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
    connect(TheServer,SIGNAL(sockDisconnect(int,QString,quint16)),this,SLOT(userLogOff(int,QString,quint16)));
    if (TheServer->listen(QHostAddress::Any,port))
        Log("Server listening at port "+QString::number(port));
    else
        Log("Server error: cannot listen at port "+QString::number(port));
    TheWorld=new World;
    TheWorld->Size=Coordinate(1000,1000,1000);
    TheWorld->RegisterBlock(Block("Stone",Coordinate(.2,.2,.2),"",1));
    connect(TheWorld,SIGNAL(log(QString)),this,SLOT(Log(QString)));
    connect(TheWorld,SIGNAL(sendCommand(QVector<QString>&)),this,SLOT(Process(QVector<QString>&)));
    connect(TheWorld,SIGNAL(sendCommand(const QString&)),this,SLOT(Process(const QString&)));
    Log("World initialized");
    PM=new PluginManager;
    int p=PM->ServerLoadFolder("plugins",TheWorld,TheServer);
    Log(QString("Plugin Manager initialized and loaded %1 plugin(s)").arg(p));
}

ServerWidget::~ServerWidget() {
    TheServer->close();
    delete ui;
}

void ServerWidget::Log(const QString &s) {
    ui->plainTextEdit->appendPlainText(s);
}

void ServerWidget::Process(QVector<QString> &v) {
    if (!v.size())
        return;
    if (v[0]=="exit") {
        close();
    } else if (v[0]=="help") {
        Log("help: \nexit: exit the server\nhelp: show this help");
        emit TheWorld->helpSignal();
    }
    emit TheWorld->processSignal(v);
}

void ServerWidget::Process(const QString &comm) {
    QVector<QString>command;
    int len=comm.length();
    QString tmp;
    bool yh=0;
    for (int i=0;i<len;++i) {
        if (comm[i]=='\"')
            yh=!yh;
        else if (comm[i]==' '&&!yh&&tmp!="") {
            command.push_back(tmp);
            tmp="";
        } else
              tmp+=comm[i];
    }
    if (tmp!="")
        command.push_back(tmp);
    if (command.size()) {
        Log("> "+comm);
        Process(command);
    }
}

void ServerWidget::on_lineEdit_returnPressed() {
    QString comm=ui->lineEdit->text();
    ui->lineEdit->setText("");
    Process(comm);
}

void ServerWidget::newClient(int socket,QString ip,quint16 port) {
    Log("New connection: "+ip+':'+QString::number(port)+" as player "+QString::number(socket));
}

void ServerWidget::recvVariantMap(const int id, const QString &, const quint16, const QVariantMap &qvm) {
    if (qvm["type"].toString()=="login") {
        QString name=qvm["name"].toString();
        int verify=id;
        for (QMap<int,Player>::iterator it=TheWorld->Players.begin();it!=TheWorld->Players.end();++it)
            if (it.value().Name==name)
                verify=0;
        if (!Version::Verify(qvm["ver"].toString()))
            verify=-1;
        QVariantMap q;
        q.insert("type","login");
        q.insert("num",QString::number(verify));
        emit TheServer->sendVariantMap(q,id);
        if (verify>0) {
            Log(QString("Player %1 logged in with the name %2").arg(id).arg(qvm["name"].toString()));
            Player ThePlayer;
            ThePlayer.Name=name;
            TheWorld->Players.insert(id,ThePlayer);
            q.clear();
            q.insert("type","adduser");
            q.insert("num",id);
            q.insert("name",name);
            emit TheServer->sendVariantMap(q,-1);
        }
    } else if (qvm["type"].toString()=="addblock") {
        if (TheWorld->BlockTypes.find(qvm["bt"].toString())==TheWorld->BlockTypes.end())
            return;
        int n;
        if (TheWorld->Blocks.empty())
            n=0;
        else
            n=(TheWorld->Blocks.end()-1).key()+1;
        Bnode b=Bnode(qvm["bt"].toString(),Coordinate(qvm["posx"].toDouble(),qvm["posy"].toDouble(),qvm["posz"].toDouble()),Coordinate(qvm["hsx"].toDouble(),qvm["hsy"].toDouble(),qvm["hsz"].toDouble()));
        TheWorld->Blocks.insert(n,b);
        QMap<int,Bnode>::iterator it=TheWorld->Blocks.find(n);
        QVariantMap q=qvm;
        q.insert("num",it.key());
        emit TheWorld->blockCreateSignal(it);
        emit TheServer->sendVariantMap(q,-1);
    } else if (qvm["type"].toString()=="rmblock") {
        int n=qvm["num"].toInt();
        emit TheWorld->blockDestroySignal(TheWorld->Blocks.find(n));
        TheWorld->Blocks.remove(n);
        emit TheServer->sendVariantMap(qvm,-1);
    } else if (qvm["type"].toString()=="getbasic") {
        QVariantMap q;
        q.insert("type","wsize");
        q.insert("x",TheWorld->Size.x);
        q.insert("y",TheWorld->Size.y);
        q.insert("z",TheWorld->Size.z);
        emit TheServer->sendVariantMap(q,id);
        for (QMap<QString,Plugin*>::iterator it=PM->Plugins.begin();it!=PM->Plugins.end();++it)
            if (it.value()->Essential) {
                q.clear();
                q.insert("type","essentialplugin");
                q.insert("name",it.value()->Name);
                emit TheServer->sendVariantMap(q,id);
            }
        for (QMap<int,Player>::iterator it=TheWorld->Players.begin();it!=TheWorld->Players.end();++it) {
            q.clear();
            q.insert("type","adduser");
            q.insert("num",it.key());
            q.insert("name",it.value().Name);
            emit TheServer->sendVariantMap(q,id);
        }
        for (QMap<int,Bnode>::iterator it=TheWorld->Blocks.begin();it!=TheWorld->Blocks.end();++it) {
            q.clear();
            q.insert("type","addblock");
            q.insert("num",it.key());
            q.insert("bt",it.value().Type);
            q.insert("posx",it.value().Position.x);
            q.insert("posy",it.value().Position.y);
            q.insert("posz",it.value().Position.z);
            q.insert("hsx",it.value().HalfSize.x);
            q.insert("hsy",it.value().HalfSize.y);
            q.insert("hsz",it.value().HalfSize.z);
            emit TheServer->sendVariantMap(q,id);
        }
    } else if (qvm["type"]=="mvuser") {
        TheWorld->Players[id].Position=Coordinate(qvm["x"].toDouble(),qvm["y"].toDouble(),qvm["z"].toDouble());
        QVariantMap q=qvm;
        q.insert("num",id);
        emit TheServer->sendVariantMap(q,-1);
    }
}

void ServerWidget::userLogOff(int id,QString,quint16) {
    Log(QString("Player %1 (%2) logged off").arg(id).arg(TheWorld->Players[id].Name));
    TheWorld->Players.remove(id);
    QVariantMap qvm;
    qvm.insert("type","rmuser");
    qvm.insert("num",id);
    emit TheServer->sendVariantMap(qvm,-1);
}

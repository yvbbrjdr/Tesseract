#include "UserControl.h"

UserControl::UserControl() {
    Name="UserControl1.0";
    Essential=1;
}

void UserControl::clientLoad(World *_TheWorld,Socket *_TheSocket) {
    TheWorld=_TheWorld;
    TheSocket=_TheSocket;
    connect(TheSocket,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
}

void UserControl::serverLoad(World *_TheWorld,Server *_TheServer) {
    TheWorld=_TheWorld;
    TheServer=_TheServer;
    connect(TheWorld,SIGNAL(helpSignal()),this,SLOT(showhelp()));
    connect(TheWorld,SIGNAL(processSignal(QVector<QString>&)),this,SLOT(process(QVector<QString>&)));
}

void UserControl::showhelp() {
    emit TheWorld->log("list: list all the players\nban [num1] <num2> ...: ban specified players\ntp [num] [x] [y] [z]: teleport a player");
}

void UserControl::process(QVector<QString>&v) {
    if (v.size()) {
        if (v[0]=="list") {
            for (QMap<int,Player>::iterator it=TheWorld->Players.begin();it!=TheWorld->Players.end();++it)
                emit TheWorld->log(QString::number(it.key())+' '+it.value().Name+QString(" (%1,%2,%3)").arg(it.value().Position.x).arg(it.value().Position.y).arg(it.value().Position.z));
        } else if (v[0]=="ban"&&v.size()>=2) {
            for (QVector<QString>::iterator it=v.begin()+1;it!=v.end();++it) {
                QVariantMap qvm;
                qvm.insert("type","ban");
                emit TheServer->sendVariantMap(qvm,it->toInt());
            }
        } else if (v[0]=="tp"&&v.size()==5) {
            if (TheWorld->Players.find(v[1].toInt())!=TheWorld->Players.end()) {
                QVariantMap qvm;
                qvm.insert("type","tp");
                qvm.insert("x",v[2].toDouble());
                qvm.insert("y",v[3].toDouble());
                qvm.insert("z",v[4].toDouble());
                emit TheServer->sendVariantMap(qvm,v[1].toInt());
                emit TheWorld->log(QString("Player %1 (%2) has been teleported to (%3,%4,%5)").arg(v[1].toInt()).arg(TheWorld->Players.find(v[1].toInt()).value().Name).arg(v[2].toDouble()).arg(v[3].toDouble()).arg(v[4].toDouble()));
            } else {
                emit TheWorld->log(QString("Unknown player %1").arg(v[1].toInt()));
            }
        }
    }
}

void UserControl::recvVariantMap(int,QString,quint16,QVariantMap qvm) {
    if (qvm["type"].toString()=="ban") {
        TheSocket->disconnectFromHost();
        QMessageBox::warning(0,"Exiting","You are banned from the server");
        exit(0);
    } else if (qvm["type"].toString()=="tp") {
        TheWorld->Myself.value().Position=Coordinate(qvm["x"].toDouble(),qvm["y"].toDouble(),qvm["z"].toDouble());
        TheWorld->Myself.value().Turn(0,0);
    }
}

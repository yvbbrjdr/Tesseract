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
    emit TheWorld->logSignal("list: list all the players\nban [num]: ban a specified player");
}

void UserControl::process(QVector<QString>&v) {
    if (v.size()) {
        if (v[0]=="list") {
            for (QMap<int,Player>::iterator it=TheWorld->Players.begin();it!=TheWorld->Players.end();++it)
                emit TheWorld->logSignal(QString::number(it.key())+' '+it.value().Name);
        } else if (v[0]=="ban"&&v.size()>=2) {
            for (QVector<QString>::iterator it=v.begin()+1;it!=v.end();++it) {
                QVariantMap qvm;
                qvm.insert("type","ban");
                emit TheServer->sendVariantMap(qvm,it->toInt());
            }
        }
    }
}

void UserControl::recvVariantMap(int,QString,quint16,QVariantMap qvm) {
    if (qvm["type"].toString()=="ban") {
        TheSocket->disconnectFromHost();
        QMessageBox::warning(0,"Exiting","You are banned from the server");
        exit(0);
    }
}

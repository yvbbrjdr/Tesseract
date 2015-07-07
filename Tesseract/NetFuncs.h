#ifndef NETFUNCS_H
#define NETFUNCS_H

#include "tesseractwidget.h"

QTcpSocket sock;

void connectserver(QString IP) {
    sock.connectToHost(QHostAddress(IP),8377);
}

#endif // NETFUNCS_H

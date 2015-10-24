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

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QMainWindow>
#include "tesseractwidget.h"
#include "serverwidget.h"
#include <QFile>
#include <QJsonDocument>
#include "Version.h"

namespace Ui {
    class LoginWidget;
}

class LoginWidget : public QMainWindow {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    QString LoadFile(QString Filename);
    bool SaveFile(QString Filename,QString Content);
    bool LoadConfigFile();
    bool SaveConfigFile();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void recvVariantMap(int,QString,quint16,QVariantMap);

private:
    Ui::LoginWidget *ui;
    Socket *TheSocket;
};

#endif // LOGINWIDGET_H

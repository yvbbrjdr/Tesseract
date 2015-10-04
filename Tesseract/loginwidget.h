#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QMainWindow>
#include "tesseractwidget.h"
#include "serverwidget.h"
#include <QFile>
#include <QJsonDocument>

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

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H

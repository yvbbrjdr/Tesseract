#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) : QMainWindow(parent),ui(new Ui::LoginWidget) {
    ui->setupUi(this);
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::on_pushButton_2_clicked() {
    close();
}

void LoginWidget::on_pushButton_clicked() {
    Socket *TheSocket=new Socket(-1);
    TheSocket->connectToHost(ui->lineEdit->text(),ui->lineEdit_2->text().toUInt());
    QByteArray qba(ui->lineEdit_3->text().toLocal8Bit().data());
    TheSocket->sendData(qba);
    TesseractWidget *w=new TesseractWidget(TheSocket);
    w->showFullScreen();
    hide();
}

void LoginWidget::on_pushButton_3_clicked() {
    ServerWidget *w=new ServerWidget(ui->lineEdit_2->text().toUInt());
    w->show();
    hide();
}

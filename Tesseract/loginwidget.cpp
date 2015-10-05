#include "loginwidget.h"
#include "ui_loginwidget.h"

QString LoginWidget::LoadFile(QString Filename) {
    QFile file(Filename.toLocal8Bit().data());
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return "";
    QTextStream qts(&file);
    QString ret=qts.readAll();
    file.close();
    return ret;
}

bool LoginWidget::SaveFile(QString Filename,QString Content) {
    QFile file(Filename);
    if (!file.open(QIODevice::ReadWrite|QIODevice::Text))
        return 0;
    QTextStream qts(&file);
    qts<<Content;
    file.close();
    return 1;
}

bool LoginWidget::LoadConfigFile() {
    QString Config=LoadFile("Tesseract.conf");
    if (Config=="")
        return 0;
    QVariantMap qvm=QJsonDocument::fromJson(Config.toUtf8()).toVariant().toMap();
    ui->lineEdit->setText(qvm["server"].toString());
    ui->lineEdit_2->setText(qvm["port"].toString());
    ui->lineEdit_3->setText(qvm["name"].toString());
    return 1;
}

bool LoginWidget::SaveConfigFile() {
    QVariantMap qvm;
    qvm.insert("server",ui->lineEdit->text());
    qvm.insert("port",ui->lineEdit_2->text());
    qvm.insert("name",ui->lineEdit_3->text());
    return SaveFile("Tesseract.conf",QJsonDocument::fromVariant(qvm).toJson().data());
}

LoginWidget::LoginWidget(QWidget *parent) : QMainWindow(parent),ui(new Ui::LoginWidget) {
    ui->setupUi(this);
    if (!LoadConfigFile())
        SaveConfigFile();
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::on_pushButton_2_clicked() {
    close();
}

void LoginWidget::on_pushButton_clicked() {
    SaveConfigFile();
    TheSocket=new Socket(-1);
    TheSocket->connectToHost(ui->lineEdit->text(),ui->lineEdit_2->text().toUShort());
    ui->label->setText("Connecting. . . ");
    if (!TheSocket->waitForConnected()) {
        delete TheSocket;
        QMessageBox::warning(0,"Failed","Unable to connect to the server");
        ui->label->setText("Retry!");
        return;
    }
    connect(TheSocket,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
    QVariantMap qvm;
    qvm.insert("type","login");
    qvm.insert("name",ui->lineEdit_3->text());
    qvm.insert("ver","1.0");
    emit TheSocket->sendVariantMap(qvm,-1);
}

void LoginWidget::on_pushButton_3_clicked() {
    SaveConfigFile();
    ServerWidget *w=new ServerWidget(ui->lineEdit_2->text().toUInt());
    w->show();
    hide();
}

void LoginWidget::recvVariantMap(int,QString,quint16,QVariantMap qvm) {
    if (qvm["type"].toString()=="login") {
        disconnect(TheSocket,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
        if (qvm["num"].toInt()>0) {
            TesseractWidget *w=new TesseractWidget(TheSocket,qvm["num"].toInt(),ui->lineEdit_3->text());
            w->showFullScreen();
            hide();
        } else if (qvm["num"].toInt()==0) {
            TheSocket->disconnectFromHost();
            delete TheSocket;
            QMessageBox::warning(0,"Failed","Name existed. Please change to another one.");
            ui->label->setText("Retry!");
        } else {
            TheSocket->disconnectFromHost();
            delete TheSocket;
            QMessageBox::warning(0,"Failed","Version is not correct.");
            ui->label->setText("Retry!");
        }
    }
}

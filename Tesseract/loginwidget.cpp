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
    TesseractWidget *w=new TesseractWidget(ui->lineEdit->text(),ui->lineEdit_2->text().toUInt(),ui->lineEdit_3->text());
    w->showFullScreen();
    hide();
}

void LoginWidget::on_pushButton_3_clicked() {
    SaveConfigFile();
    ServerWidget *w=new ServerWidget(ui->lineEdit_2->text().toUInt());
    w->show();
    hide();
}
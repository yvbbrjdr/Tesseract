#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    log("Welcome to TesseractServer");
    server=new QTcpServer;
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectionSlot()));
    if (server->listen(QHostAddress::Any,8377))
        log("Server is listening at port 8377. . . ");
    else
        log("Failed to initialize the server");
}

void MainWindow::newConnectionSlot() {
    QTcpSocket *sock=server->nextPendingConnection();
    log("New connection from "+sock->peerAddress().toString());
    sock->disconnect();
    sock->close();
}

void MainWindow::log(QString s) {ui->plainTextEdit->appendPlainText(s);}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::process(QVector<QString>command) {
    if (command[0]=="exit") {
        server->close();
        log("Server is shutting down. . . ");
        exit(0);
    } else if (command[0]=="help") {
        log("exit: To exit");
        log("help: To show this help");
    } else {
        log("Unknown command. Try to type \'help\'. ");
    }
}

void MainWindow::on_lineEdit_editingFinished() {
    QString comm=ui->lineEdit->text();
    ui->lineEdit->setText("");
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
        log("> "+comm);
        process(command);
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

World *w;

QQueue<QString>UniMsgQue;

class MainLoop:public QThread {
public:
    void run() {
        while (1) {
            if (UniMsgQue.empty()) {
                sleep(10);
                continue;
            }

        }
    }
};

class TcpThread;

QVector<TcpThread*>TcpThreads;

class TcpThread:public QThread {
public:
    int id;
    bool maintain;
    QTcpSocket *sock;
    Player *p;
    QQueue<QString>MsgQue;
    TcpThread(int ID,qintptr handle) {
        id=ID;
        maintain=1;
        p=new Player(w);
        sock=new QTcpSocket;
        connect(sock,SIGNAL(readyRead()),this,SLOT(readdata()));          //There are some problems here...
        connect(sock,SIGNAL(disconnected()),this,SLOT(disconnect()));
        sock->setSocketDescriptor(handle);
        puts("hello");
    }
    void run() {
        while (maintain) {
            if (MsgQue.empty()) {
                sleep(10);
                continue;
            }
            sock->write(MsgQue.front().toStdString().c_str());
        }
    }
    void process(QString data) {

    }

public slots:
    void readdata() {
        char data[1001]={};
        sock->readLine(data,1000);
        process(data);
    }
    void disconnect() {
        sock->disconnect();
        sock->close();
        TcpThreads.remove(id);
        maintain=0;
        delete this;
    }
};

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    log("Welcome to TesseractServer");
    w=new World(Coordinate(100,100,100));
    log("World generated");
    MainLoop *ml=new MainLoop;
    ml->start();
    server=new myQTcpServer;
    if (server->listen(QHostAddress::Any,8377))
        log("Server is listening at port 8377. . . ");
    else
        log("Failed to initialize the server");
}

void myQTcpServer::incomingConnection(qintptr handle) {
    TcpThread *tt=new TcpThread(TcpThreads.count(),handle);
    TcpThreads.push_back(tt);
    tt->start();
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

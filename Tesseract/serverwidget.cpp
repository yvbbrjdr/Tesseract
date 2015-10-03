#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(quint16 port,QWidget *parent) : QMainWindow(parent),ui(new Ui::ServerWidget) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    Log("Welcome to Tesseract Server");
    TheServer=new Server;
    connect(TheServer,SIGNAL(connectClient(int,QString,quint16)),this,SLOT(newClient(int,QString,quint16)));
    connect(TheServer,SIGNAL(readVariantMap(int,QString,quint16,QVariantMap)),this,SLOT(recvVariantMap(int,QString,quint16,QVariantMap)));
    if (TheServer->listen(QHostAddress::Any,port))
        Log("Server listening at port "+QString::number(port));
    else
        Log("Server error: cannot listen at port "+QString::number(port));
    TheWorld=new World;
    connect(TheWorld,SIGNAL(logSignal(QString)),this,SLOT(Log(QString)));
    Log("World initialized");
    PM=new PluginManager;
    int p=PM->ServerLoadFolder("plugins",*TheWorld);
    Log(QString("Plugin Manager initialized and loaded %1 plugin(s)").arg(p));
}

ServerWidget::~ServerWidget() {
    TheServer->close();
    delete ui;
}

void ServerWidget::Log(QString s) {
    ui->plainTextEdit->appendPlainText(s);
}

void ServerWidget::Process(QVector<QString> &v) {
    if (!v.size())
        return;
    if (v[0]=="exit") {
        close();
    } else if (v[0]=="help") {
        Log("help: \nexit: exit the server\nhelp: show this help");
    } else {
        Log("Unknown command. Try to type 'help'.");
    }
}

void ServerWidget::on_lineEdit_returnPressed() {
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
        Log("> "+comm);
        Process(command);
    }
}

void ServerWidget::newClient(int socket,QString ip,quint16 port) {
    Log("New connection: "+ip+':'+QString::number(port)+" as player "+QString::number(socket));
}

void ServerWidget::recvVariantMap(const int id, const QString &, const quint16, const QVariantMap &qvm) {
    if (qvm["type"].toString()=="login")
        Log(QString("Player %1 logged in with the name %2").arg(id).arg(qvm["name"].toString()));
}

#include "serveur.h"
#include "ui_serveur.h"

#include <QDebug>

Serveur::Serveur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serveur)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,58425)){
        ui->label_Statu->setText(tcpServer->errorString());
        QMessageBox::critical(this, tr("Fortune Server"), tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }

    ui->label_Statu->setText(tr("The server is running on port %1.\n""You can run the IRC program now.").arg(tcpServer->serverPort()));

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connection()));
}

Serveur::~Serveur()
{
    delete ui;   
}

void Serveur::connection()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, SIGNAL(disconnected()),clientConnection, SLOT(deleteLater()));

    Client * c = new Client(this,clientConnection);
    clients.append(c);

    connect(c,SIGNAL(sendMessage(QString)),this,SLOT(getMessage(QString)));
}

void Serveur::getMessage(QString mess)
{
    ui->textEdit->append(mess);

    QList<Client *>::iterator it;
    for(it=clients.begin();it != clients.end();it++){
        QString tmp = mess ;
        (*it)->getMessage(tmp);
    }
}

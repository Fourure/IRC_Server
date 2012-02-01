#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serveur)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        ui->label_Statu->setText(tcpServer->errorString());
        QMessageBox::critical(this, tr("Fortune Server"), tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }

    ui->label_Statu->setText(tr("The server is running on port %1.\n""Run the Fortune Client example now.").arg(tcpServer->serverPort()));

    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
                  << tr("You've got to think about tomorrow.")
                  << tr("You will be surprised by a loud noise.")
                  << tr("You will feel hungry again in another hour.")
                  << tr("You might have mail.")
                  << tr("You cannot kill time without injuring eternity.")
                  << tr("Computers are not intelligent. They only think they are.");

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
}

Serveur::~Serveur()
{
    delete ui;   
}

void Serveur::sendFortune()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << fortunes.at(qrand() % fortunes.size());
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, SIGNAL(disconnected()),clientConnection, SLOT(deleteLater()));

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

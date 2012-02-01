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

    //ui->label_Statu->setText("Server Connected");

    ui->label_Statu->setText(tr("The server is running on port %1.\n"
                                 "Run the Fortune Client example now.")
                              .arg(tcpServer->serverPort()));
}

Serveur::~Serveur()
{
    delete ui;   
}

void Serveur::on_pushButton_clicked()
{
}

//Test Git

#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QList>
#include "client.h"

namespace Ui {
class Serveur;
}

class Serveur : public QWidget
{
    Q_OBJECT
    
public:
    explicit Serveur(QWidget *parent = 0);
    ~Serveur();

private slots:
     void connection();
     void getMessage(QString mess);

private:
    Ui::Serveur *ui;
    QTcpServer *tcpServer;
    QList<Client *> clients;
};

#endif // SERVEUR_H

#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

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
     void sendFortune();

private:
    Ui::Serveur *ui;
    QTcpServer *tcpServer;
    QStringList fortunes;
};

#endif // SERVEUR_H

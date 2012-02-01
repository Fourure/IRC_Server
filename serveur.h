#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QTcpServer>
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
    void on_pushButton_clicked();

private:
    Ui::Serveur *ui;
    QTcpServer *tcpServer;
};

#endif // SERVEUR_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QWidget * parent,QTcpSocket * tcpSocket);
    void getMessage(QString mess);

private slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QWidget * parent;
    QTcpSocket * tcpSocket;
    QString currentFortune;
    quint16 blockSize;

signals:
    void sendMessage(QString mess);
};

#endif // CLIENT_H

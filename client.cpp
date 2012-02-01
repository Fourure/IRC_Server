#include "client.h"

#include <QDebug>

Client::Client(QWidget *parent, QTcpSocket *tcpSocket) : parent(parent), tcpSocket(tcpSocket)
{    
     connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
     connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
     connect(tcpSocket, SIGNAL(disconnected()),tcpSocket, SLOT(deleteLater()));

     blockSize = 0;
}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;
    QString nextFortune;
      in >> nextFortune;

      currentFortune = nextFortune;

      emit(sendMessage(currentFortune));
      blockSize = 0;

}

void Client::getMessage(QString mess)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << mess;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
}

void Client::displayError(QAbstractSocket::SocketError socketError)
 {
     switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     case QAbstractSocket::HostNotFoundError:
         QMessageBox::information(parent, tr("Server"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         QMessageBox::information(parent, tr("Server"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
     default:
         QMessageBox::information(parent, tr("Server"),
                                  tr("The following error occurred: %1.")
                                  .arg(tcpSocket->errorString()));
     }
 }

#include "qaggregator.h"

QAggregator::QAggregator(QObject *parent):
    QObject(parent)
{
    initLogger( "aggregator.log", ldebug);
    /*
    *L_(linfo) << "info";
    * # For QString need to convert
    * L_(linfo)  << "Connected to " << rec.Ip.toLatin1().data();
    * */
    L_(ldebug) << "Agg initialted";
    _Agg = new QTcpServer();
       if (!_Agg->listen(QHostAddress::Any,portnumber)) {
           L_(ldebug) << " Agg Server Unable to start the server: " << _Agg->errorString().toLatin1().data();
           _Agg->close();
           return;
       }
       QString ipAddress;
       QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
       // use the first non-localhost IPv4 address
       for (int i = 0; i < ipAddressesList.size(); ++i) {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               ipAddress = ipAddressesList.at(i).toString();
               break;
           }
       }

       // if we did not find one, use IPv4 localhost
         if (ipAddress.isEmpty())
             ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
         qDebug() << QString("The server is running on\n\nIP: %1\n\rport: %2\r\n\r\n"
                                 "Connect to DxCluster Nodes now")
                              .arg(ipAddress).arg(_Agg->serverPort());

       connect(_Agg, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

}

void QAggregator::addText(const char *data, int n)
{
    QString my_data(data);
    int nC=0;
    L_(linfo) << my_data.toLatin1().data();
    for (QTcpSocket* socket : _sockets) {
            L_(ldebug) << "Sending to Client " << ++nC;
            socket->write((my_data.trimmed()+"\r\n").toUtf8());  // Skoomlogger is fussy about \r\n ... Runlog does not care
    }
}

void QAggregator::onNewConnection()
{
    qDebug() << "Got a New Connection";
    QTcpSocket *clientSocket = _Agg->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

       _sockets.push_back(clientSocket);
       clientSocket->write(QString("Welcome to DU3TW Agg Node\n\n").toUtf8());
       qDebug() << "Welcome sent to client";
}

void QAggregator::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
       {
           QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
           _sockets.removeOne(sender);
            qDebug() << "Removing a Connection";
       }
}

void QAggregator::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
      QByteArray datas = sender->readAll();
      qDebug() << "Read Available";
      for (QTcpSocket* socket : _sockets) {
          if (socket != sender)
              socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
      }
}


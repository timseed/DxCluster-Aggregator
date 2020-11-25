#include "qaggregator.h"

QAggregator::QAggregator(QObject *parent):
    QObject(parent)
{
qDebug() << "Agg initialized";
}

void QAggregator::Setup()
{
    _Agg = new QTcpServer();
       if (!_Agg->listen(QHostAddress::Any,portnumber)) {
           qDebug() << " Agg Server Unable to start the server: " << _Agg->errorString();
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

}

void QAggregator::addText(const char *data, int n)
{
    QString my_data(data);
    qDebug() << "Agg got data" << my_data;
}

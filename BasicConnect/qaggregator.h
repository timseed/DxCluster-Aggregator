#ifndef QAGGREGATOR_H
#define QAGGREGATOR_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QList>

class QAggregator : public QObject
{
    Q_OBJECT
public:
    QAggregator(QObject *parent);
    void Setup();
    int portnumber=6060;
    QTcpServer *_Agg;
    QList<QTcpSocket*>  _sockets;

public slots:
    void addText(const char*,int n);

    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();
};

#endif // QAGGREGATOR_H

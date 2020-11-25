#include <QCoreApplication>
#include "qtelnetcluster.h"
#include "qaggregator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QTelnetCluster> clusters;
    QTelnetCluster *_telnet   = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet2  = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet3  = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet4  = new QTelnetCluster(a.parent());

    QAggregator *_Agg = new QAggregator(a.parent());


    // So the Aggrehator is now running.
    // We now connect to the Client(s)

    QObject::connect(_telnet, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    QObject::connect(_telnet2, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    QObject::connect(_telnet3, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    QObject::connect(_telnet4, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    _telnet->connectToHost("dxc.w9pa.net",7373);
    _telnet->SetAutoAns("DU3TW","set/dx/filter");
    _telnet2->connectToHost("kq8m.no-ip.org",7373);
    _telnet2->SetAutoAns("DU3TW","set/dx/filter");
    _telnet3->connectToHost("192.168.254.125",7550);
    _telnet3->SetAutoAns("DU3TW","sh/dx","You are client");
    _telnet4->connectToHost("9m2pju.hamradio.my",7300);
    _telnet4->SetAutoAns("a45wg","set/dx/filter");

    qDebug() << "Telnet connected completed";

    return a.exec();
}

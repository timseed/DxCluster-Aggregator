#include <QCoreApplication>
#include "qtelnetcluster.h"
#include "qaggregator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTelnetCluster *_telnet   = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet2  = new QTelnetCluster(a.parent());

    QAggregator *_Agg = new QAggregator(a.parent());
    _Agg->Setup();

    // So the Aggrehator is now running.
    // We now connect to the Client(s)

    // _telnet->connectToHost("192.168.254.125",7550);
    _telnet->connectToHost("dxc.w9pa.net",7373);
    _telnet2->connectToHost("kq8m.no-ip.org",7373);
   // _telnet->SetAutoAns("DU3TW","set dx filter spottercqzone = [18,19,22,23,24,25,26,27,28,29,30,31,32,1] and SkimDb > 10");
    _telnet->SetAutoAns("DU3TW","set/dx/filter");
    _telnet2->SetAutoAns("DU3TW","set/dx/filter");

    QObject::connect(_telnet, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    QObject::connect(_telnet2, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    qDebug() << "Telnet connected completed";

    return a.exec();
}

#include <QCoreApplication>
#include "qtelnetcluster.h"
#include "qaggregator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTelnetCluster *_telnet   = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet2  = new QTelnetCluster(a.parent());
    QTelnetCluster *_telnet3  = new QTelnetCluster(a.parent());

    QAggregator *_Agg = new QAggregator(a.parent());
    _Agg->Setup();

    // So the Aggrehator is now running.
    // We now connect to the Client(s)


    //_telnet->connectToHost("dxc.w9pa.net",7373);
    //_telnet2->connectToHost("kq8m.no-ip.org",7373);
      _telnet3->connectToHost("192.168.254.125",7550);
      _telnet3->SetAutoAns("DU3TW","sh/dx","You are client");
   // _telnet->SetAutoAns("DU3TW","set/dx/filter");
   // _telnet2->SetAutoAns("DU3TW","set/dx/filter");

  //  QObject::connect(_telnet, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
  //  QObject::connect(_telnet2, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    QObject::connect(_telnet3, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );

    qDebug() << "Telnet connected completed";

    return a.exec();
}

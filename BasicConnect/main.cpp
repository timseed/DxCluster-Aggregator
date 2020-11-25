#include <QCoreApplication>
#include "QTelnet.h"
#include "qaggregator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTelnet *_telnet  = new QTelnet();
    QAggregator *_Agg = new QAggregator(a.parent());
    _Agg->Setup();

    // So the Aggrehator is now running.
    // We now connect to the Client(s)

     _telnet->connectToHost("192.168.254.125",7550);
    QObject::connect(_telnet, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
    qDebug() << "Telnet connected completed";

    return a.exec();
}

#include <QCoreApplication>
#include "qtelnetcluster.h"
#include "qaggregator.h"
#include "qclusterdef.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QTelnetCluster *> clusters;
    QClusterDef *Cludef = new QClusterDef(a.parent(),":/clusters.tsv");
    QAggregator *_Agg = new QAggregator(a.parent());
    for (auto rec : Cludef->getClusterRecords())
    {
        qDebug() << rec.dump();
        QTelnetCluster *_telnet   = new QTelnetCluster(a.parent());
          QObject::connect(_telnet, SIGNAL(newData(const char*,int)), _Agg, SLOT(addText(const char*,int)) );
        _telnet->connectToHost(rec.Ip,rec.port);
        _telnet->SetAutoAns(rec.Call,rec.Filter, rec.Trigger);
        clusters.append(_telnet);
    }


    qDebug() << "Telnet connected completed";

    return a.exec();
}

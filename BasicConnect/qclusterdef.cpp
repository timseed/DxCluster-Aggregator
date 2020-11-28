#include "qclusterdef.h"

QClusterDef::QClusterDef(QObject *parent, QString fname) : QObject(parent)
{
    qDebug() << "ClusterDef trying to read " << fname;
    QSettings file_settings(fname,QSettings::IniFormat);
    int size = file_settings.beginReadArray("clusters");
    for (int i = 0; i < size; ++i) {
        file_settings.setArrayIndex(i);
        ClusterRecords.append(QClusterRec(file_settings.value("ip").toString(),
                                          file_settings.value("port").toInt(),
                                          file_settings.value("call").toString(),
                                          file_settings.value("filter").toString(),
                                          file_settings.value("trigger").toString()
                                          ));

    }
    file_settings.endArray();
}

void QClusterDef::CreateConfigFile(QString fname)
{
    // Create a Config file. And put 'n' records in it - with Sensible names.
    int i;
    QSettings settings(fname,QSettings::IniFormat);
    settings.beginWriteArray("clusters");
    for (i = 0; i < MAX_DUMMY_RECS; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("ip", QString("ip-address-%1").arg(i));
        settings.setValue("port", QString("123%1").arg(i).toInt());
        settings.setValue("call", QString("DU%1ABC").arg(i));
        settings.setValue("filter", QString("set dx filter"));
        settings.setValue("trigger", QString("enter your callsign:"));
    }
    settings.endArray();
    settings.sync();
    qDebug() << "Dummy Config file called " << fname << " created with " << i << " records";
}

QList<QClusterRec> QClusterDef::getClusterRecords() const
{
    return ClusterRecords;
}

void QClusterDef::dump()
{
    int i=0;
    for (auto n:ClusterRecords)
    {
        qDebug( )<< "Rec       " << ++i;
        qDebug( )<< "  IP      " << n.Ip;
        qDebug( )<< "  Port    " << n.port;
        qDebug( )<< "  Call    " << n.Call;
        qDebug( )<< "  Trigger " << n.Trigger;
        qDebug( )<< "  Filter  " << n.Filter;

    }
}

int QClusterDef::length()
{
    return ClusterRecords.length();
}

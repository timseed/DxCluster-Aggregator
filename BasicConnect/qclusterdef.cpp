#include "qclusterdef.h"

QClusterDef::QClusterDef(QObject *parent, QString fname) : QObject(parent)
{
    Filename=fname;
    QFile file(Filename);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Error opening file " << Filename;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line=in.readLine();
        if (line.length()>0)
        {
            if (!line.startsWith('#'))
            {
                QStringList fields=line.split('\t');
                if (fields.length()==5)
                {
                    ClusterRecords.append(QClusterRec(fields[0],fields[1].toInt(),
                            fields[2],fields[3],fields[4]));
                }
                else
                {
                    qDebug() << "Unable to parse line " << line;
                }
            }
        }
    }
}

QList<QClusterRec> QClusterDef::getClusterRecords() const
{
    return ClusterRecords;
}

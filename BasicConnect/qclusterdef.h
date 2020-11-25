#ifndef QCLUSTERDEF_H
#define QCLUSTERDEF_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>


class QClusterRec
  {
public:
    QString Ip;
    int     port;
    QString Call;
    QString Filter;
    QString Trigger;

    QClusterRec(QString ip,int prt, QString call,QString filter,QString trigger){
        Ip=ip;
        port=prt;
        Call=call;
        Filter=filter;
        Trigger=trigger;
       };

    QString dump(){
        return(QString("Ip: %1\nport: %2\nCall: %3\nFilter: %4\nTrigger: %5").arg(Ip).arg(port).arg(Call).arg(Filter).arg(Trigger));
    }
};


class QClusterDef : public QObject
{
    Q_OBJECT
public:
    QClusterDef(QObject *parent = nullptr,QString fname=":/Cluster.txt");
    QString Filename;
    QList<QClusterRec> ClusterRecords;

    QList<QClusterRec> getClusterRecords() const;

signals:

};

#endif // QCLUSTERDEF_H

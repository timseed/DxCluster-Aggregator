#ifndef QCLUSTERDEF_H
#define QCLUSTERDEF_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QSettings>
#define MAX_DUMMY_RECS 3


// All Lower case.
struct ClusterRec {
    QString ip;
    int     port;
    QString call;
    QString filter;
    QString trigger;
};


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
    void CreateConfigFile(QString fname);
    QList<QClusterRec> getClusterRecords() const;
    void dump();
    int length();

signals:

};

#endif // QCLUSTERDEF_H

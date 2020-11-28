#ifndef QTELNETCLUSTER_H
#define QTELNETCLUSTER_H
#include "QTelnet.h"
#include "log.h"

class QTelnetCluster : public QTelnet
{
public:
    QTelnetCluster(QObject *parent, QString logname);
    void SetAutoAns(QString call, QString filter, QString Trigger="enter your call:");
    QString CallSign;
    QString Filter;
    QString Trigger;
    void SendCallSign(void);
    void SendFilter(void);
    void Logger(QString data);

public slots:
    virtual void onReadyRead() override;
};

#endif // QTELNETCLUSTER_H

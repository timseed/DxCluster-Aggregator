#ifndef QTELNETCLUSTER_H
#define QTELNETCLUSTER_H
#include "QTelnet.h"

class QTelnetCluster : public QTelnet
{
public:
    QTelnetCluster(QObject *parent);
    void SetAutoAns(QString call, QString filter, QString Trigger="enter your call:");
    QString CallSign;
    QString Filter;
    QString Trigger;
    void SendCallSign(void);
    void SendFilter(void);

public slots:
    virtual void onReadyRead() override;
};

#endif // QTELNETCLUSTER_H

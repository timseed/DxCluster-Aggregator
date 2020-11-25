#ifndef QAGGREGATOR_H
#define QAGGREGATOR_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QNetworkInterface>

class QAggregator : public QObject
{
    Q_OBJECT
public:
    QAggregator(QObject *parent);
    void Setup();
    int portnumber=6060;
    QTcpServer *_Agg;


public slots:
    void addText(const char*,int n);
};

#endif // QAGGREGATOR_H

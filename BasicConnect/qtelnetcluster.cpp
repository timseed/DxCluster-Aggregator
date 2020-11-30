#include "qtelnetcluster.h"

QTelnetCluster::QTelnetCluster(QObject *parent, QString logname):
    QTelnet(parent)
{
    //connect( this, SIGNAL(readyRead()),		this, SLOT(onReadyRead()) );
    QString LogName=QString("%1.log").arg(logname);
    initLogger(LogName.toLatin1().data(), ldebug);

}

void QTelnetCluster::SetAutoAns(QString call, QString filter,QString trigger)
{
    // These will be needed if the Telnet Connection sends something back like
    // At the login prompt please enter your amateur radio callsign.\nPlease enter your call:
    // This "trigger" can be changed - but it is unusual.
    CallSign=call;
    Filter=filter;
    Trigger=trigger;
    qDebug() << QString("Call %1 Filter %2 Trigger %3").arg(CallSign).arg(Filter).arg(Trigger);
}

void QTelnetCluster::SendCallSign(void)
{
    sendData((CallSign+"\n").toUtf8());
    qDebug() << "Sent my call";
}

void QTelnetCluster::SendFilter(void)
{
    sendData((Filter+"\n").toUtf8());
    qDebug() << "Sent Filter";
}

void QTelnetCluster::Logger(QString data)
{
    L_(linfo) << data.toLatin1().data();
}

void QTelnetCluster::onReadyRead()
{
    qint64 readed;
    qint64 processed;

    while( (readed = read(m_buffIncoming, IncommingBufferSize)) != 0 )
    {
        switch( readed )
        {
        case -1:
            disconnectFromHost();
            break;
        default:
            processed = doTelnetInProtocol(readed);
            if( processed > 0 )
            {
                QString rxData(m_buffProcessed);
                if (rxData.contains(Trigger))  //Auto Login
                {
                    qDebug() << "Sending Callsign and filter";
                    SendCallSign();
                    SendFilter();
                }
                Q_EMIT(newData(m_buffProcessed, processed));
                Logger(rxData.trimmed());
                memset(m_buffProcessed,0,sizeof(m_buffProcessed));
            }
            break;
        }
    }
}

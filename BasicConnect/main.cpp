#include <QCoreApplication>
#include <QDateTime>
#include <QCommandLineParser>
#include <QDebug>

#include "qtelnetcluster.h"
#include "qaggregator.h"
#include "qclusterdef.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    switch (type)
    {
    case QtDebugMsg:
        txt += QString("{Debug} \t\t %1").arg(msg);
        break;
    case QtWarningMsg:
        txt += QString("{Warning} \t %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt += QString("{Critical} \t %1").arg(msg);
        break;
    case QtFatalMsg:
        txt += QString("{Fatal} \t\t %1").arg(msg);
        abort();
        break;
    default:
        txt += QString("{Unk} \t\t %1").arg(msg);
        break;
    }

    QFile outFile("BasicConnect.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&outFile);
    textStream << txt << Qt::endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("BasicConnect");
    QCoreApplication::setApplicationVersion("0.0.a");


    QCommandLineParser parser;
    parser.setApplicationDescription("Dx Cluster Aggregator. So you can feed multiple Dx Clusyter streams to your logger.");
    parser.addHelpOption();
    parser.addVersionOption();
    //parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to copy."));
    //parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));
    // A boolean option with a single name (-p)
    QCommandLineOption logToFileOption("l", QCoreApplication::translate("main", "Log output to BasicConnect.log"));
    parser.addOption(logToFileOption);

    // Process the actual command line arguments given by the user
     parser.process(a);

     const QStringList args = parser.positionalArguments();
     // source is args.at(0), destination is args.at(1)

    bool logToFile = parser.isSet(logToFileOption);
    if (logToFile)
    {
        qInstallMessageHandler(customMessageHandler);
    }


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

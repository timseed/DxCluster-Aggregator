#include <QCoreApplication>
#include <QDateTime>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>

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

    // Parse input commands
    QCommandLineParser parser;
    parser.setApplicationDescription("Dx Cluster Aggregator. So you can feed multiple Dx Clusyter streams to your logger.");
    parser.addHelpOption();
    parser.addVersionOption();

    // We will have two options to start with
    // -l to Log to a file (or not)
    // -f <Filename> So we can switch Cluster and filters easily

    // A boolean option with a single name (-l)
    QCommandLineOption logToFileOption("l", QCoreApplication::translate("main", "Log output to BasicConnect.log"));
    parser.addOption(logToFileOption);

    // A boolean option with a single name (-c)  CREATE a Definition template
    QCommandLineOption createFileOption("c", QCoreApplication::translate("main", "Create a config file. Will not run the aggregator"));
    parser.addOption(createFileOption);
    // A boolean option with a single name (-d)  Dump Definition template
    QCommandLineOption dumpFileOption("d", QCoreApplication::translate("main", "Dump definition template"));
    parser.addOption(dumpFileOption);

    // An option with a value -f filename
    QCommandLineOption fileOption(QStringList() << "f" << "file", QCoreApplication::translate("main", "Cluster Definition file"), QCoreApplication::translate("main", "address"), "0");
    parser.addOption(fileOption);

    // Process the actual command line arguments given by the user
    parser.process(a);
    bool createFile = parser.isSet(createFileOption);
    bool dumpFile = parser.isSet(dumpFileOption);
    const QStringList args = parser.positionalArguments();
    // source is args.at(0), destination is args.at(1)
    QString cluDefFile = parser.value(fileOption);
    QFileInfo fi(cluDefFile);
    if (dumpFile && createFile)
    {
        qDebug() << "Error: You can either Dump (-d) or Create (-c), but not both at the same time.";
        exit(0);
    }
    if (dumpFile)
    {
        QClusterDef *Cludef = new QClusterDef(a.parent(),cluDefFile);
        Cludef->dump();
        exit(0);
    }
    if (createFile)
    {
        if (cluDefFile.length()&&(cluDefFile!="0"))
        {
            if (fi.exists())
            {
                qDebug() << "Error: File " << cluDefFile << " already exists.";
                exit(0);
            }
            else
            {
                qDebug() << "Create: File does not exists. Create " << cluDefFile;
                // Lets try and create the correct format file.
                QClusterDef *Cludef = new QClusterDef(a.parent(),cluDefFile);
                Cludef->CreateConfigFile(cluDefFile);
                qDebug() << "Please edit the new config file " << cluDefFile << " and re-run without the -c option.";
                exit(0);
            }
        }
        else
        {
            qDebug() << "Create file option needs a filename. Please add -f <Filename>";
            exit(0);
        }
    }

    // We need to check if there is a value here - and if there is does the file Exist
    if (cluDefFile.length()&&(cluDefFile!="0"))
    {

        if (!fi.exists())
        {
            qDebug() << "Error: File specified " << cluDefFile << " does not exist";
            exit(1);
        }
        else
        {
            qDebug() << "Using Input file " << cluDefFile;
        }
    }
    else
    {
        // No File specified - do use default - but tell the user
        qDebug() << "-f No file specified. Using default file";
        cluDefFile = ":/clusters.tsv";
    }

    bool logToFile = parser.isSet(logToFileOption);
    if (logToFile)
    {
        qInstallMessageHandler(customMessageHandler);
    }




    // End of Command Parsing



    QList<QTelnetCluster *> clusters;
    QClusterDef *Cludef = new QClusterDef(a.parent(),cluDefFile);
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

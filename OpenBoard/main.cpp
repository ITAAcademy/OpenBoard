#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QTime>

QTime cut_time = QDateTime::currentDateTime().time();
QString log_time = QString("log ") + QString::number( cut_time.hour()) + QString("_") +
        QString::number(cut_time.minute())  + QString("_") + QString::number(cut_time.second()) + QString(".txt") ;
//const char * deb_file = log_time.toStdString().data();
#define DEBUG_TO_FILE  "log.txt"
//log_time.toStdString().c_str()
//"log.txt"
//currentDateTime().toString("h:m:s ap")



#ifdef DEBUG_TO_FILE


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
   // FILE *file = fopen(DEBUG_TO_FILE, "a");

    QFile file(log_time);

    char * stream = new char[500];
    //FILE *file = fopen(DEBUG_TO_FILE, "a");
    if(file.open(QIODevice::Append)  )//file != NULL)
    {
        switch (type) {
        case QtDebugMsg:
            sprintf(stream, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           // fprintf(file, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            printf("%s \n", localMsg.constData());
            break;
        case QtWarningMsg:
            sprintf(stream, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          //  fprintf(file, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            printf("%s \n", localMsg.constData());
            break;
        case QtCriticalMsg:
            sprintf(stream, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          //  fprintf(file, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            printf("%s \n", localMsg.constData());
            break;
        case QtFatalMsg:
            sprintf(stream, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          //  fprintf(file, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            printf("%s \n", localMsg.constData());
            abort();
        default:
           // fprintf(file, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            printf("%s \n", localMsg.constData());
            break;
        }
    file.write(stream);
    file.write("\n");
    delete stream;
    file.close();
    }
    //fclose(file);

}
#endif

int main(int argc, char *argv[])
{
    //  qApp->addLibraryPath("\libs");
    //   qApp->addLibraryPath("/plugins");
#ifdef DEBUG_TO_FILE
   // DEBUG_TO_FILE = QString("log.txt" + QDateTime::currentDateTime());
    qInstallMessageHandler(myMessageOutput);
    QFile file (log_time);
    file.open( QIODevice::WriteOnly);
    file.write("Begin log:\n");
    file.close();
            //fopen(deb_file, "w");
    //fclose(file);
#endif
    QString executable = argv[0];
    QString executablePath = executable.mid(0,executable.lastIndexOf("\\"));
    QString installPathPlugins = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    QCoreApplication::removeLibraryPath(installPathPlugins);
    QCoreApplication::addLibraryPath(installPathPlugins);
    QCoreApplication::addLibraryPath(executablePath);

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    paths.append("ssl");
    QCoreApplication::setLibraryPaths(paths);
    //    QCoreApplication::addLibraryPath("SSL");


    QApplication app(argc, argv);

    MainWindow window;
    window.resize(500, 500);
#ifdef DEBUG_TO_FILE
    window.setLogFileName(QString("log.txt"));
    window.setLogFileDateName(log_time);
#endif
    // app.addLibraryPath("/SSL");
    //  // // //qDebug() << app.libraryPaths();
    // qApp->addLibraryPath(qApp->applicationDirPath() + "/SSL");

    //  QtAV::Widgets::registerRenderers();
    //window.show();


    return app.exec();
}

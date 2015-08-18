#include "mainwindow.h"
#include <QApplication>
//#define DEBUG_TO_FILE "log.txt"

#ifdef DEBUG_TO_FILE

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    FILE *file = fopen(DEBUG_TO_FILE, "a");
    if(file != NULL)
    switch (type) {
    case QtDebugMsg:
        fprintf(file, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        printf("%s \n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(file, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        printf("%s \n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(file, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        printf("%s \n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(file, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        printf("%s \n", localMsg.constData());
        abort();
    }
    fclose(file);
}
#endif

int main(int argc, char *argv[])
{
  //  qApp->addLibraryPath("\libs");
 //   qApp->addLibraryPath("/plugins");
#ifdef DEBUG_TO_FILE
    qInstallMessageHandler(myMessageOutput);
    FILE *file = fopen(DEBUG_TO_FILE, "w");
    fclose(file);
#endif

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    paths.append("ssl");
    QCoreApplication::setLibraryPaths(paths);
    //    QCoreApplication::addLibraryPath("SSL");


    QApplication app(argc, argv);

   // app.addLibraryPath("/SSL");
  //  // // //qDebug() << app.libraryPaths();
   // qApp->addLibraryPath(qApp->applicationDirPath() + "/SSL");

    MainWindow window;
  //  QtAV::Widgets::registerRenderers();
    //window.show();

    return app.exec();
}

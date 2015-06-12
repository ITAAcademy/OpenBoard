#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  //  qApp->addLibraryPath("\libs");
 //   qApp->addLibraryPath("/plugins");
    QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("imageformats");
        paths.append("platforms");
        paths.append("sqldrivers");
        paths.append("ssl");
        QCoreApplication::setLibraryPaths(paths);
    //    QCoreApplication::addLibraryPath("SSL");


    QApplication a(argc, argv);

    a.addLibraryPath("/SSL");
    qDebug() << a.libraryPaths();
   // qApp->addLibraryPath(qApp->applicationDirPath() + "/SSL");

    MainWindow w;
  //  QtAV::Widgets::registerRenderers();
    w.show();

    return a.exec();
}

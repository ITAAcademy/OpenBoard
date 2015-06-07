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
        QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    MainWindow w;
  //  QtAV::Widgets::registerRenderers();
    w.show();

    return a.exec();
}

#include "listcontroll.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);\
    app.setOrganizationName("QtProject");\
    app.setOrganizationDomain("qt-project.org");\
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());\

    ListControll timeLine;
    timeLine.show();
    return app.exec();\
}

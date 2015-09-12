#include "filecontroll.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);\
    app.setOrganizationName("QtProject");\
    app.setOrganizationDomain("qt-project.org");\
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());\

    BrushManager timeLine;
    timeLine.show();

    return app.exec();\
}

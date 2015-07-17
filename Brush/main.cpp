#include "brushcontroll.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);\
    app.setOrganizationName("QtProject");\
    app.setOrganizationDomain("qt-project.org");\
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());\

    BrushMeneger timeLine;
    timeLine.show();

    return app.exec();\
}

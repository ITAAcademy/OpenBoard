#include "effectscontroll.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("QtProject");\
    app.setOrganizationDomain("qt-project.org");\
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());\

    EffectsManager timeLine;
    timeLine.show();

    return app.exec();\
}

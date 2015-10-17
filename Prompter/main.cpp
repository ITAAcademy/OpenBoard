#include "promptercontroll.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("QtProject");\
    app.setOrganizationDomain("qt-project.org");\
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());\

    PrompterManager prompterManager;
    prompterManager.show();

    return app.exec();\
}

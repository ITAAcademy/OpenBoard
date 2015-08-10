#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "projectcreator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ProjectCreator::getProjectSetting(false);
    return app.exec();
}

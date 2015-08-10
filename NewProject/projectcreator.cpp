#include "projectcreator.h"


ProjectStartupSetting ProjectCreator::getCurentSetting() const
{
    return curent;
}

void ProjectCreator::setCurentSetting(const ProjectStartupSetting &value)
{
    curent = value;
}

bool ProjectCreator::isVisible()
{
    return view.isVisible();
}

void ProjectCreator::show(bool fullScreen)
{
    if(fullScreen)
        view.showFullScreen();
    else
        view.show();
}

void ProjectCreator::close()
{
    view.close();
}

ProjectStartupSetting ProjectCreator::getProjectSetting(bool fullScreen)
{
    ProjectCreator creator;
    creator.show();
    while(creator.isVisible())
        qApp->processEvents();
    qDebug() << "close()";
    return creator.getCurentSetting();
}

void ProjectCreator::setProjectState(int state)
{
    curent.state = (VIEW_STATE) state;
}

void ProjectCreator::setAdvanceMode(bool state)
{
    curent.advance_mode = state;
}
ProjectCreator::ProjectCreator(QObject *parent) : QObject(parent)
{
    view.setWidth(300);
    view.setHeight(300);
    view.setModality(Qt::ApplicationModal);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setPersistentOpenGLContext(true);
    view.setColor("transparent");
    view.setMinimumWidth(750);
    view.setMinimumHeight(500);
    view.engine()->rootContext()->setContextProperty("projectControll", this);
    view.setSource(QUrl(QStringLiteral("qrc:/main_new_poject.qml")));
}

ProjectCreator::~ProjectCreator()
{

}


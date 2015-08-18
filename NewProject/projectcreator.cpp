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
   // curent.state = -1;
    view.setSource(QUrl(QStringLiteral("qrc:/main_new_poject.qml")));
    if(fullScreen)
        view.showFullScreen();
    else
        view.show();
}

void ProjectCreator::close()
{
    view.close();
}

ProjectStartupSetting ProjectCreator::getProjectSetting(bool isStart, bool fullScreen)
{
    ProjectCreator creator;
    creator.setStart(isStart);
    creator.show(fullScreen);
    while(creator.isVisible())
        qApp->processEvents();
    //qDebug() << "close()" << isStart;
    return creator.getCurentSetting();
}

void ProjectCreator::setProjectState(int state)
{
    curent.state =  state;
}

void ProjectCreator::setAdvanceMode(bool state)
{
    curent.advance_mode = state;
}

void ProjectCreator::textMode_SetFirstImage(QString path)
{
    curent.firstImage = path;
}

void ProjectCreator::textMode_SetFirstTime(QString time)
{
    curent.firsTime = time.toInt();
}

void ProjectCreator::textMode_SetLastImage(QString path)
{
    curent.lastImage = path;
}

void ProjectCreator::textMode_SetLastTime(QString time)
{
    curent.lastTime = time.toInt();
}

bool ProjectCreator::isForStart()
{
    return start;
}

QString ProjectCreator::fileDialog(int OPEN_SAVE)
{
    return QFileDialog::getOpenFileName(0, QString(), QString(), QString(), 0, QFileDialog::DontUseNativeDialog);
}

void ProjectCreator::setStart(bool value)
{
    start = value;
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
}

ProjectCreator::~ProjectCreator()
{

}


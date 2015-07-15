#include "listcontroll.h"


QString ListControll::getTest( int i) const
{
    return test[i];
}

void ListControll::addNewTest(QString str)
{
    test.append(str);
    testWight.append(200);
    qDebug() << "SIZE   " << test.size();
}

void ListControll::setTest(const QList<QString> &value)
{
    test = value;
}

int ListControll::getTestWight( int i ) const
{
    return testWight[i];
}

void ListControll::setTestWight(int value, int i)
{
    testWight[i] = value;
}
ListControll::ListControll(QObject *parent) : QObject(parent)
{
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
  //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);\
    view.setSource(QUrl("qrc:///main.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);



    test.append("KAKA1");
    test.append("KAKA2");
    test.append("KAKA3");
    testWight.append(200);
    testWight.append(200);
    testWight.append(200);
}

ListControll::~ListControll()
{

}

void ListControll::show()
{
    view.engine()->rootContext()->setContextProperty("timeControll", this);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

int ListControll::getTestSize() const
{
    return test.size();
}


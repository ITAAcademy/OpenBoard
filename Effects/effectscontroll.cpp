#include "effectscontroll.h"




void EffectsManager::update()
{
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);
    //createdBrush.color_img = BrushPainter::getInstance()->applyColor(createdBrush);
    // emit currentBrushChanged();
}

double EffectsManager::getCurrentEffectProperty(QString propertyName)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return 0;
    double result = dataListValues[currentEffectIndex].getPropetrie(propertyName);
     qDebug() << "get current effect property '"<<propertyName<<"'  value"<<result;
    return result;
}
void EffectsManager::setCurrentEffectProperty(QString propertyName, double val)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return ;
    dataListValues[currentEffectIndex].setPropetrie(propertyName,val);
    qDebug() << "set current effect property '"<<propertyName<<"' to value"<<val;
}




EffectsManager::EffectsManager(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{

    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
    //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);
    view.engine()->rootContext()->setContextProperty("effectsControll", this);
    //view.engine()->addImageProvider("loader", cloneImg);
    view.setSource(QUrl("qrc:/main.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //  view.setPersistentOpenGLContext(true);
    view.setColor("transparent");

    //addEffect("first",100,100);
    /* QStringList dataList;
        dataList.append("Item 1");
        QQmlContext *ctxt = view.rootContext();
        ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));*/


    //viewsetFont(QFont("Segoe Script"));


}

EffectsManager::~EffectsManager()
{
    close();
}


void EffectsManager::show()
{
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
            QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

void EffectsManager::hide()
{
    view.hide();
    //emit currentBrushChanged();
}

void EffectsManager::close()
{

    view.engine()->removeImageProvider("loader");
    view.close();

}

void EffectsManager::setPosition(QPoint pos)
{
    view.setPosition(pos);
}

void EffectsManager::addEffect(QString name,  int startTime,  int howLong)
{
    qDebug() << "begin add effect";
    QQmlContext *ctxt = view.rootContext();
    //dataList=ctxt->contextProperty("myModel").toStringList();
    Effect newEffect(name+QString::number(dataListLabels.length()),startTime,howLong);
    dataListLabels.append(newEffect.getName());
    dataListValues.append(Effect());
    ctxt->setContextProperty("myModel",dataListLabels);
    qDebug() << "end add effect";

}
void EffectsManager::removeEffect(int i)
{
    qDebug() << "begin remove effect:"<<i;
    QQmlContext *ctxt = view.rootContext();
    if (i<0 || i>=dataListLabels.length() || i>=dataListValues.length())
    {
        qDebug() << "end remove effect";
        return;

    }
    dataListValues.removeAt(i);
    qDebug() << "1";
    dataListLabels.removeAt(i);
    qDebug() << "2";
    ctxt->setContextProperty("myModel",dataListLabels);
    qDebug() << "end remove effect";

}

void EffectsManager::setCurrentEffectIndex(int n)
{
    qDebug() << "QT:setCurrentEffectIndex="<<n;
    currentEffectIndex= n;
}
/*
void EffectsManager::setStartTime(long time)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return;
    dataListValues[currentEffectIndex].setStartTime(time);
}
void EffectsManager::setEndTime(long time)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return;
    dataListValues[currentEffectIndex].setEndTime(time);

}
long EffectsManager::getEndTime(){
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return 0;
    return dataListValues[currentEffectIndex].getEndTime();
}

long EffectsManager::getStartTime()
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return 0;
    return dataListValues[currentEffectIndex].getStartTime();
}

void EffectsManager::setEffectType(int type)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return;
    dataListValues[currentEffectIndex].setEffectType(type);
}

void EffectsManager::setInversion(bool val)
{
    if (currentEffectIndex>=dataListValues.length() || currentEffectIndex<0)return;
    dataListValues[currentEffectIndex].setInversion(val);
    qDebug() << "setInversion";
}
*/


bool EffectsManager::isAbleToDraw(){
    return ableToDraw;
}
void EffectsManager::setAbleToDraw(bool isAble){
    ableToDraw=isAble;
    if (!isAble)
    {
        //qDebug() << "emit unableToDraw();";
    }
}

bool EffectsManager::isActive()
{
    return view.isActive();
}


void EffectsManager::setFocus()
{
    // view.setPosition(view.position());
    if(view.isVisible())
    {
        view.setVisible(false);
        view.setWindowState(Qt::WindowNoState);
        view.setVisible(true);
    }

}

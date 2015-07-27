#include "brushcontroll.h"



int BrushManager::getCurentBrush() const
{
    return curentBrush;
}

void BrushManager::setCurentBrush(int value)
{
    curentBrush = value;
    createdBrush.img = imageStack[value];
   createdBrush.color_img = painter.applyColor(createdBrush);
    emit currentBrushChanged();
    qDebug()<<"emit currentBrushChanged();";
}

Brush BrushManager::getCreatedBrush()
{

    return createdBrush;
}

void BrushManager::setCreatedBrush(const Brush &value)
{
    createdBrush = value;
}
BrushManager::BrushManager(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    mask = QImage(":/Content/brush_skeen.png");

    // open file
    openBrushLibrary();

    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
  //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);\
    view.engine()->rootContext()->setContextProperty("brushControll", this);
    view.engine()->addImageProvider("loader", this);
    view.setSource(QUrl("qrc:/main_brush.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setPersistentOpenGLContext(true);
    view.setColor("transparent");
    //viewsetFont(QFont("Segoe Script"));


}

BrushManager::~BrushManager()
{

}

int BrushManager::getBrushCount()
{
    return imageStack.size();
}

void BrushManager::show()
{
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

void BrushManager::hide()
{
    view.hide();
}

void BrushManager::close()
{
    view.close();
        painter.close();
}

void BrushManager::setPosition(QPoint pos)
{
    view.setPosition(pos);
}

QImage BrushManager::requestImage(const QString &id, QSize *size, const QSize& requestedSize)
{
 //   qDebug() << "REQUEST IMAGE" << id;
    if(id[0] == 'a')
    {
        int i = id.rightRef(id.length() - 1).toInt();
        qDebug() << i;
        return imageStack[i];
    }

    if(id[0] == 'h')
    {
       return painter.drawBrush(createdBrush);
    }
}

bool BrushManager::openBrushLibrary(QString path)
{
    QString new_path = brushDir.currentPath()+path;
    QDir dir(new_path);
    QStringList list = dir.entryList(QDir::Files);
    for(int i = 0; i < list.length(); i++)
    {
        QImage img = QImage(new_path + "\\" + list[i]);
        if(!img.isNull())
            imageStack.push(img);
    }
    qDebug() << "Image found    " << imageStack.length();
    qDebug() << list;
}


void BrushManager::setSize(float value)
{
    createdBrush.size = value;
}

void BrushManager::setOpacity(float value)
{
    createdBrush.opacity = value;
}

void BrushManager::setBlur(float value)
{
    createdBrush.blur = value;
}

void BrushManager::setDisepers(float value)
{
    createdBrush.dispers = value;
}

void BrushManager::setSizeMax(float value)
{
    createdBrush.delta_count = value;
}

void BrushManager::setCount(float value)
{
    createdBrush.count = value;
}

void BrushManager::setSizeDelta(float value)
{
    createdBrush.size_delta = value;
}

void BrushManager::setAngleDelta(float value)
{
    createdBrush.angle_delta = value;
}

void BrushManager::setAffine(float value)
{
    createdBrush.afinn = value;
}

void BrushManager::setColor(QColor value)
{
    //qDebug() << value;
    createdBrush.color_main = value;
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);
    createdBrush.color_img = painter.applyColor(createdBrush);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);

    emit colorChanged();
  //    ;
}

float BrushManager::getSize()
{
    return createdBrush.size;
}

float BrushManager::getOpacity()
{
    return createdBrush.opacity;
}

float BrushManager::getBlur()
{
    return createdBrush.blur;
}

float BrushManager::getDisepers()
{
    return createdBrush.dispers;
}

float BrushManager::getSizeMax()
{
    return createdBrush.delta_count;
}

float BrushManager::getCount()
{
return createdBrush.count;
}

float BrushManager::getSizeDelta()
{
return createdBrush.size_delta;
}

float BrushManager::getAngleDelta()
{
return createdBrush.angle_delta;
}

int BrushManager::getAffine()
{
return createdBrush.afinn;
}

QColor BrushManager::getColor()
{
return createdBrush.color_main;
}


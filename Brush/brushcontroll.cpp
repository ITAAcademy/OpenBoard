#include "brushcontroll.h"



int BrushMeneger::getCurentBrush() const
{
    return curentBrush;
}

void BrushMeneger::setCurentBrush(int value)
{
    curentBrush = value;
    createdBrush.img = imageStack[value];
}
BrushMeneger::BrushMeneger(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

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
    view.setSource(QUrl("qrc:///main.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setPersistentOpenGLContext(true);
    //viewsetFont(QFont("Segoe Script"));

}

BrushMeneger::~BrushMeneger()
{

}

int BrushMeneger::getBrushCount()
{
    return imageStack.size();
}

void BrushMeneger::show()
{
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

QImage BrushMeneger::requestImage(const QString &id, QSize *size, const QSize& requestedSize)
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
       return BrushPainter::drawBrush(createdBrush);
    }
}

bool BrushMeneger::openBrushLibrary(QString path)
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


void BrushMeneger::setSize(float value)
{
    createdBrush.size = value;
}

void BrushMeneger::setOpacity(float value)
{
    createdBrush.opacity = value;
}

void BrushMeneger::setBlur(float value)
{
    createdBrush.blur = value;
}

void BrushMeneger::setDisepers(float value)
{
    createdBrush.dispers = value;
}

void BrushMeneger::setSizeMax(float value)
{
    createdBrush.delta_count = value;
}

void BrushMeneger::setCount(float value)
{
    createdBrush.count = value;
}

void BrushMeneger::setSizeDelta(float value)
{
    createdBrush.size_delta = value;
}

void BrushMeneger::setAngleDelta(float value)
{
    createdBrush.angle_delta = value;
}

void BrushMeneger::setAffine(float value)
{
    createdBrush.afinn = value;
}

void BrushMeneger::setColor(QColor value)
{
    //qDebug() << value;
    createdBrush.color_main = value;
}

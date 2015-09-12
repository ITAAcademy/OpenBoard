#include "filecontroll.h"
#include <QSound>
#include <QAudioFormat>



void FileManager::update()
{
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);
    //createdBrush.color_img = BrushPainter::getInstance()->applyColor(createdBrush);
   // emit currentBrushChanged();
}

QStack<QString> FileManager::getMusicStack() const
{
    return musicStack;
}

void FileManager::setMusicStack(const QStack<QString> &value)
{
    musicStack = value;
}

QStack<QString> FileManager::getVideoStack() const
{
    return videoStack;
}

int FileManager::getVideoStackSize() const
{
    return videoStack.size();
}

 int FileManager::getMusicStackSize() const
 {
     return musicStack.size();
 }

  QString FileManager::getMusicStackAt(int index)
  {
      if (index > -1 && index <  musicStack.size())

          return musicStack[index];
  }

  QString FileManager::getImageStackAt(int index)
  {
      if (index > -1 && index <  imageStackPath.size())
          return imageStackPath[index];
      else
          return "";
  }

  int FileManager::getImageStackSize()
  {
          return imageStackPath.size();
  }

  QString FileManager::getMusicStackOnlyFilenameAt(int index)
  {
      if (index > -1 && index <  musicStackName.size())
             return musicStackName[index];
  }

  QString FileManager::getVideoStackOnlyFilenameAt(int index)
  {
      if (index > -1 && index <  videoStackName.size())
             return videoStackName[index];
  }

  QString FileManager::getVideoStackAt(int index)
  {
      if (index > -1 && index <  videoStack.size())

          return videoStack[index];
  }

void FileManager::setVideoStack(const QStack<QString> &value)
{
    videoStack = value;
}

QString FileManager::getFilePathName() const
{
    return filePathName;
}

void FileManager::setFilePathName(const QString &value)
{
    filePathName = value;
    emit filePathNameChanged(value);
}
QDir FileManager::getBrushDir(){
    return brushDir;
}

void FileManager::setColorize(bool val)
{
    colorize=val;
}

FileManager::FileManager(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    mask = QImage(":/Content/brush_skeen.png");
    createdBrush.img.fill(Qt::black);
    // open file
    openBrushLibrary();
    qDebug() << "A6";

    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
    qDebug() << "A7";
  //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);
    cloneImg = new ImageClone(this);
      qDebug() << "A8";

    view.engine()->addImageProvider("loader", cloneImg);
     view.engine()->rootContext()->setContextProperty("brushControll", this);
      qDebug() << "A9";
    view.setSource(QUrl("qrc:/main_filemanager.qml")); \
    qDebug() << "A13";
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    qDebug() << "A14";
    view.setPersistentOpenGLContext(true);
      qDebug() << "A10";
    view.setColor("transparent");
    //viewsetFont(QFont("Segoe Script"));


qDebug() << "A5";
}

FileManager::~FileManager()
{
    close();
}

int FileManager::getBrushCount()
{
    return imageStack.size();
}

void FileManager::show()
{
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

void FileManager::hide()
{
    view.hide();
    emit currentBrushChanged();
}

void FileManager::close()
{

        view.engine()->removeImageProvider("loader");
        view.close();

}

void FileManager::setPosition(QPoint pos)
{
    view.setPosition(pos);
}

QImage FileManager::requestImage(const QString &id, QSize *size, const QSize& requestedSize)
{
    //qDebug() << "REQUEST IMAGE" << id;
    if(id[0] == 'a')
    {
        int i = id.rightRef(id.length() - 1).toInt();
        //qDebug() << i;
        return imageStack[i];
    }

   /* if(id[0] == 'h')
    {
       return FilePainter::getInstance()->drawBrush(createdBrush);
    }*/

    return QImage(requestedSize, QImage::Format_ARGB32);
}

bool FileManager::openBrushLibrary(QString path)
{
    QString new_path = brushDir.currentPath()+path;
    qDebug () << "OPENG BRUSH LIBRARY   "   ;

    QDir dir(new_path);
    brushPathsList = dir.entryList(QDir::Files);
    for(int i = 0; i < brushPathsList.length(); i++)
    {
       QString temp_path = new_path + "\\" + brushPathsList[i];

      QString extension = QFileInfo(temp_path).suffix();

      qDebug() << "Ext " << extension;
        if (extension == "mp3" || extension == "wav" || extension == "flac")
        {
              musicStack.push(temp_path);
              musicStackName.push(brushPathsList[i]);
        }
        else
          if (extension == "avi" || extension == "mp4" || extension == "mkv")
          {
                videoStack.push(temp_path);
                videoStackName.push(brushPathsList[i]);
          }
        else
          {
              extension = QImageReader::imageFormat(temp_path);
            if (extension != "")
            {
               QImage img = QImage(temp_path);
              if(!img.isNull())
              {
                  imageStack.push(img);
                  imageStackPath.push(temp_path);
              }
            }
          }
    }
    qDebug() << "Image found    " << imageStack.length();
     qDebug() << "Music found    " << musicStack.length();
      qDebug() << "Video found    " << videoStack.length();
   // qDebug() << brushPathsList;
}



bool FileManager::isActive()
{
    return view.isActive();
}

void FileManager::setFocus()
{
   // view.setPosition(view.position());
    if(view.isVisible())
    {
        view.setVisible(false);
        view.setWindowState(Qt::WindowNoState);
        view.setVisible(true);
    }

}

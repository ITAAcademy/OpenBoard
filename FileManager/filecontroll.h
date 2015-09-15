#ifndef FILECONTROL_H
#define FILECONTROL_H
#include <QObject>
#include <QQuickImageProvider>
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView> //Not using QQmlApplicationEngine because many examples don't have a Window{}
#include <QQmlContext>
#include <QList>
#include <QStack>
#include <QDebug>
#include <QFont>
#include "filepainter.h"
#include "../Brush/imageclone.h"

#define TEXTURE_INDEX_BRUSH 1



class FileManager : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    QList <QString> image_extensions;
    QQuickView view;
    QList <QString> test;
    QList <int> testWight;
    QDir brushDir;
    QStack <QImage> imageStack;
    QStack <QString> imageStackPath;
    QStack <QString> musicStack;
    QStack <QString> musicStackName;
    QStack <QString> videoStackName;
    QStack <QString> videoStack;
    QImage mask;
    int curentBrush;
    FileBrush createdBrush;
    ImageClone *cloneImg;
    bool colorize = true;
    QPoint framaMousePosition;
     QPoint prevMousePosition;

    /*
     *
 */
    int size;

    QString filePathName = "-1";
public:
    QDir getBrushDir();
    void setColorize(bool val);
      QStringList brushPathsList;
    explicit FileManager(QObject *parent = 0);
    ~FileManager();
    Q_INVOKABLE int getBrushCount();
    void show();
    Q_INVOKABLE void hide();
    void close();
    void setPosition(QPoint pos);




    /*
     * G/S
    */




    Q_INVOKABLE void update();



    bool isActive();
    QStack<QString> getMusicStack() const;

    void setMusicStack(const QStack<QString> &value);

    Q_INVOKABLE  QStack<QString> getVideoStack() const;
    Q_INVOKABLE int getVideoStackSize() const;
    Q_INVOKABLE int getMusicStackSize() const;
    Q_INVOKABLE QString getMusicStackAt(int index);
    Q_INVOKABLE QString getImageStackAt(int index);
    Q_INVOKABLE int getImageStackSize();
    Q_INVOKABLE QString getMusicStackOnlyFilenameAt(int index);
     Q_INVOKABLE QString getVideoStackOnlyFilenameAt(int index);
    Q_INVOKABLE QString getVideoStackAt(int index);
    Q_INVOKABLE   void setVideoStack(const QStack<QString> &value);

    Q_INVOKABLE QString getFilePathName() const;
    Q_INVOKABLE void setFilePathName(const QString &value);
    Q_INVOKABLE void setFramaMousePosition(int mouseX, int mouseY);
    Q_INVOKABLE void setFramaMousePosition( const QPoint x);
    Q_INVOKABLE void setPrevMousePosition();
    Q_INVOKABLE void moveWindow();
    Q_INVOKABLE void resizeWindowWidth(bool left);
    Q_INVOKABLE void resizeWindowHeight(bool up);

signals:
    //void colorChanged();
    void currentBrushChanged();
    void filePathNameChanged(QString value);
public slots:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
void setFocus();
private:
bool ableToDraw=true;
    bool openBrushLibrary( QString path = "\\Preset\\Brushes");
};

#endif // LISTCONTROLL_H

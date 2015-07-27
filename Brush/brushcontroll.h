#ifndef BRUSHCONTROL_H
#define BRUSHCONTROL_H
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
#include "brushpainter.h"
#define TEXTURE_INDEX_BRUSH 1
class BrushManager : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    QQuickView view;
    QList <QString> test;
    QList <int> testWight;
    QDir brushDir;
    QStack <QImage> imageStack;
    QImage mask;
    int curentBrush;
    Brush createdBrush;
    BrushPainter painter;
    /*
     *
 */
    int size;
public:
    explicit BrushManager(QObject *parent = 0);
    ~BrushManager();
    Q_INVOKABLE int getBrushCount();
    void show();
    void hide();
    void close();
    void setPosition(QPoint pos);

    Q_INVOKABLE int getCurentBrush() const;
    Q_INVOKABLE void setCurentBrush(int value);


    /*
     * G/S
    */

    Q_INVOKABLE void setSize(float value);
    Q_INVOKABLE void setOpacity(float value);
    Q_INVOKABLE void setBlur(float value);
    Q_INVOKABLE void setDisepers(float value);
    Q_INVOKABLE void setSizeMax(float value);
    Q_INVOKABLE void setCount(float value);
    Q_INVOKABLE void setSizeDelta(float value);
    Q_INVOKABLE void setAngleDelta(float value);
    Q_INVOKABLE void setAffine(float value);
    Q_INVOKABLE void setColor(QColor value);

    Q_INVOKABLE float getSize();
    Q_INVOKABLE float getOpacity();
    Q_INVOKABLE float getBlur();
    Q_INVOKABLE float getDisepers();
    Q_INVOKABLE float getSizeMax();
    Q_INVOKABLE float getCount();
    Q_INVOKABLE float getSizeDelta();
    Q_INVOKABLE float getAngleDelta();
    Q_INVOKABLE int getAffine();
    Q_INVOKABLE QColor getColor();

    Brush getCreatedBrush();
    void setCreatedBrush(const Brush &value);

    Q_INVOKABLE QString toHex(QColor col);
    Q_INVOKABLE float getHue(QString col);
    Q_INVOKABLE float getSaturation(QString col);
    Q_INVOKABLE float getLightness(QString col);
    Q_INVOKABLE bool isColorValid(QString value);
    Q_INVOKABLE void update();


signals:
void colorChanged();
void currentBrushChanged();
public slots:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
private:
    bool openBrushLibrary( QString path = "\\Preset\\Brushes");
};

#endif // LISTCONTROLL_H

#ifndef LISTCONTROLL_H
#define LISTCONTROLL_H

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

class BrushMeneger : public QObject, public QQuickImageProvider
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
    /*
     *
 */
    int size;
public:
    explicit BrushMeneger(QObject *parent = 0);
    ~BrushMeneger();
    Q_INVOKABLE int getBrushCount();
    void show();

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
signals:

public slots:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
private:
    bool openBrushLibrary( QString path = "\\Preset\\Brushes");
};

#endif // LISTCONTROLL_H

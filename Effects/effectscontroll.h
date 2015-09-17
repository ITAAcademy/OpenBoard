#ifndef EFFECTSCONTROL_H
#define EFFECTSCONTROL_H
#include <QObject>
#include <QQuickImageProvider>
#include <QDir>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView> //Not using QQmlApplicationEngine because many examples don't have a Window{}
#include <QQmlContext>
#include <QList>
#include <QStack>
#include <QDebug>
#include <QFont>
#include <effect.h>
#define TEXTURE_INDEX_BRUSH 1



class EffectsManager : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    QQuickView view;
    /*
     *
 */
    int size;
    int currentEffectIndex = -1;
public:
    explicit EffectsManager(QObject *parent = 0);
    ~EffectsManager();
    void show();
    void hide();
    void close();
    void setPosition(QPoint pos);
    Q_INVOKABLE void addEffect(QString name,  int startTime, int howLong);
    Q_INVOKABLE void removeEffect(int i);
    Q_INVOKABLE void update();
    Q_INVOKABLE void setCurrentEffectIndex(int n);

   /* Q_INVOKABLE void setStartTime(long time);
    Q_INVOKABLE long getStartTime();
    Q_INVOKABLE void setEndTime(long time);
    Q_INVOKABLE long getEndTime();
    Q_INVOKABLE void setEffectType(int type);
    Q_INVOKABLE void setInversion(bool val);*/
    Q_INVOKABLE double getCurrentEffectProperty(QString propertyName);
    Q_INVOKABLE void setCurrentEffectProperty(QString propertyName, double val);
    /*
     * G/S
    */


    bool isAbleToDraw();
    void setAbleToDraw(bool val);
    bool isActive();





signals:
    //void colorChanged();
public slots:
    void setFocus();
private:
    QStringList dataListLabels;
    QVector<Effect> dataListValues;
    bool ableToDraw=true;
    bool openBrushLibrary( QString path = "\\Preset\\Brushes");
};

#endif // LISTCONTROLL_H

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
#include "effect.h"
#include <QQuickItem>
#define TEXTURE_INDEX_BRUSH 1



class EffectsManager : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    public:
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
    QQmlContext* getRootContext();
    setBlockTime(int n);
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





    QVector<Effect> getDataListValues() const;
    void setDataListValues(const QVector<Effect> &value);

    void clearEffects();
    void addEffect(Effect effect);


    QPoint getCurrentBlockIndex() const;
    void setCurrentBlockIndex(const QPoint &value);

signals:
    //void colorChanged();
    void showSignal();
    void hideSignal();
    void setBlockTimeSignal(int val);
public slots:
    void setFocus();
private:
     QPoint currentBlockIndex;
    int blockTime = 0;
    bool showed=false;
    QStringList dataListLabels;
    QVector<Effect> dataListValues;
    bool ableToDraw=true;
    bool openBrushLibrary( QString path = "\\Preset\\Brushes");
};

#endif // LISTCONTROLL_H

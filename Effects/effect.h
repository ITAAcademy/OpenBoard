#ifndef EFFECT_H
#define EFFECT_H
#include <qstring.h>
#include <qmap.h>
#include <qpoint.h>
class Effect
{
    QString name;
    //long int startTime=0;
    //long int endTime=0;
  //  bool inversion;
   // int effectType = EFFECT_ALPHA;
    QMap<QString,double> propetries;

public:
    Effect();
    Effect(QString name, int startTime, int endTime);
    QString getName() const;
    void setName(const QString &value);
    /*long getStartTime() const;
    void setStartTime(long value);
    long getEndTime() const;
    void setEndTime(long value);
    void setEffectType(int val);
    void setInversion(bool val);*/
    QMap<QString, double> getPropetries() const;
    void setPropetries(const QMap<QString, double> &value);
    void setPropetrie(QString propertieName, double value);
    double getPropetrie(QString propertieName);
};

#endif // EFFECT_H

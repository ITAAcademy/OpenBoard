#include "effect.h"
#include <qdebug.h>

QString Effect::getName() const
{
    return name;
}

void Effect::setName(const QString &value)
{
    name = value;
}

/*long Effect::getStartTime() const
{

    if (endTime>startTime)
        return startTime;
    else return endTime;
}

void Effect::setStartTime(long value)
{
    startTime=value;
}

long Effect::getEndTime() const
{
    if (endTime>startTime)
        return endTime;
    else return startTime;
}

void Effect::setEndTime(long value)
{
    endTime = value;
}

void Effect::setEffectType(int val)
{
    effectType=val;
    qDebug() << "set effect type:"<<effectType;
}

void Effect::setInversion(bool val)
{
    inversion=val;
}
*/
QMap<QString, double> Effect::getPropetries() const
{
    return propetries;
}

void Effect::setPropetries(const QMap<QString, double> &value)
{
    propetries = value;
}
void Effect::setPropetrie(QString propertieName, int value)
{
    propetries[propertieName] = value;
}
double Effect::getPropetrie(QString propertieName){
    return propetries[propertieName];
}

Effect::Effect()
{

}

Effect::Effect(QString name, int startTime, long endTime)
{
    this->name=name;
    this->startTime=startTime;
    this->endTime=endTime;
}

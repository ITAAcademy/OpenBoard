#include "mouserecorder.h"

MouseRecorder::MouseRecorder()
{
    //add first group of points;
 QVector<QPoint>  qPoints;
coordGroup.append(qPoints);
}

MouseRecorder::MouseRecorder(Brush brush)
{
    this->brush=brush;
     //add first group of points;
    QVector<QPoint>  qPoints;
   coordGroup.append(qPoints);
}

QVector<QPoint> MouseRecorder::getMouseCoord(int group)
{
    return coordGroup[group];
}

QVector<QPoint> MouseRecorder::getMouseCoord()
{
    return getMouseCoord(currentPointsGroup);
}

void MouseRecorder::nextGroup()
{
    currentPointsGroup++;
    if (coordGroup.length()<=currentPointsGroup)
    {
        QVector<QPoint>  qPoints;
       coordGroup.append(qPoints);
    }
}

int MouseRecorder::SPEED_OF_RECORDING_MS = 5;

void MouseRecorder::addCoord(int x, int y,int group)
{
     QPoint pt;
     pt.setX(x);
     pt.setY(y);
     coordGroup[group].append(pt);
}

void MouseRecorder::addCoord(int x, int y)
{
    addCoord(x,y,currentPointsGroup);
}

void MouseRecorder::addCoord( QPoint pt,int group)
{
    coordGroup[group].append(pt);
}

void MouseRecorder::addCoord(QPoint pt)
{
    addCoord(pt,currentPointsGroup);
}

void MouseRecorder::clear(int group)
{
    coordGroup[group].clear();
}

QVector<QVector<QPoint> > MouseRecorder::getCoordGroup()
{
    return coordGroup;
}

void MouseRecorder::clear()
{
    clear(currentPointsGroup);
}

void MouseRecorder::setBrush(Brush brush)
{
    this->brush=brush;
}
Brush MouseRecorder::getBrush(){
    return brush;
}


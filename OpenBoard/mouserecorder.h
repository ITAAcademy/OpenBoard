#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H
#include <qvector.h>
#include <QPoint>
#include "../Brush/brushpainter.h"


class MouseRecorder
{
    int currentPointsGroup = 0;
QVector< QVector<QPoint> > coordGroup;
//QVector <QPoint> mouseCoord;
Brush brush;
public:
 static int SPEED_OF_RECORDING_MS;
    MouseRecorder();
    MouseRecorder(Brush brush);
   QVector <QPoint> getMouseCoord(int group);
   QVector <QPoint> getMouseCoord();
   void nextGroup();
   void addCoord(int x,int y,int group);
    void addCoord(int x,int y);
   void addCoord(QPoint pt,int group);
    void addCoord(QPoint pt);
   void clear(int group);
   QVector< QVector<QPoint> > getCoordGroup();
   void clear();
   void setBrush(Brush brush);
   Brush getBrush();
};

#endif // MOUSERECORDER_H

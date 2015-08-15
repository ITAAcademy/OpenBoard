#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H
#include <qvector.h>
#include <QPoint>
#include "../Brush/brushpainter.h"
struct BrushBeginingIndex{
    Brush brush;
    int pointIndex;
};

class MouseRecorder
{
    int currentPointsGroup = 0;
QVector< QVector<QPoint> > coordGroup;
//QVector <QPoint> mouseCoord;
QVector<QVector<BrushBeginingIndex> > brushBeginingIndexes;
public:
 static int SPEED_OF_RECORDING_MS;
    MouseRecorder();
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
   void addBrush(Brush brush);
   QVector<BrushBeginingIndex> getBrushBeginings(int group);
   QVector<BrushBeginingIndex> getBrushBeginings();
};

#endif // MOUSERECORDER_H

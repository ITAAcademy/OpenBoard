#ifndef DrawBrush_H
#define DrawBrush_H
#pragma once
#include <qvector.h>
#include <QPoint>
#include "../Brush/brushpainter.h"
#include "drawelement.h"

struct BrushBeginingIndex{
    Brush brush;
    int pointIndex;
};



class DrawBrushElm  : public DrawElement
{
     Q_OBJECT
    int currentPointsGroup = 0;
QVector<QPoint> coords;
Brush brush;
GLuint currentTexture;
//QVector <QPoint> mouseCoord;
QVector<BrushBeginingIndex> brushes;
QStringList brushesPaths;
bool ableToDraw = true;
public:
 static int SPEED_OF_RECORDING_MS;
   DrawBrushElm(OGLWidget *drawWidget, QObject *parent);
    void addCoord(int x,int y);
    void addCoord(QPoint pt);
   void clear();
QVector<QPoint> getCoords();
    void draw();
   void addBrush(Brush brush);
   QVector<BrushBeginingIndex> getBrushes();
   bool load_add(QDataStream &stream);
   bool save_add(QDataStream &stream);
   void setLifeTime(int value);


};



#endif // DRAWMOUSE


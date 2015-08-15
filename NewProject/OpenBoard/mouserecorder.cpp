#include "mouserecorder.h"

MouseRecorder::MouseRecorder()
{
    //add first group of points;
 QVector<QPoint>  qPoints;
coordGroup.append(qPoints);

 QVector<BrushBeginingIndex> brushBeginings;
brushBeginingIndexes.append(brushBeginings);
}


QVector<QPoint> MouseRecorder::getMouseCoord(int group)
{
    return coordGroup[group];
}
QVector<BrushBeginingIndex> MouseRecorder::getBrushBeginings(int group){
    return brushBeginingIndexes[group];
}
QVector<BrushBeginingIndex> MouseRecorder::getBrushBeginings(){
    return getBrushBeginings(currentPointsGroup);
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
    brushBeginingIndexes[group].clear();
}

QVector<QVector<QPoint> > MouseRecorder::getCoordGroup()
{
    return coordGroup;
}

void MouseRecorder::clear()
{
    clear(currentPointsGroup);
}

void MouseRecorder::addBrush(Brush brush)
{
    for (int i=0;i<brushBeginingIndexes[currentPointsGroup].length();i++){
         // qDebug()<<"brushBeginingIndexes["<<currentPointsGroup<<"].length:"<<brushBeginingIndexes[currentPointsGroup].length();
        if (i==0) continue;
       // // qDebug() <<"brushBeginingIndexes[currentPointsGroup]["<<i<<"].pointIndex:"<<
         //          brushBeginingIndexes[currentPointsGroup][i].pointIndex;
       // // qDebug() << "coordGroup[currentPointsGroup].length())"<<coordGroup[currentPointsGroup].length()-1;

        // qDebug() << "brushBeginingIndexes[currentPointsGroup]["<<i<<"].pointIndex:"<<
                    brushBeginingIndexes[currentPointsGroup][i].pointIndex;
        // qDebug() << "brushBeginingIndexes[currentPointsGroup]["<<i-1<<"].pointIndex:"<<
                    brushBeginingIndexes[currentPointsGroup][i-1].pointIndex;

        if (brushBeginingIndexes[currentPointsGroup][i].pointIndex==coordGroup[currentPointsGroup].length()-1){
            brushBeginingIndexes[currentPointsGroup][i].brush=brush;
            return;
        }
    }
    BrushBeginingIndex beginIndex;
    beginIndex.brush=brush;
    beginIndex.pointIndex=coordGroup[currentPointsGroup].length();
brushBeginingIndexes[currentPointsGroup].append(beginIndex);
}



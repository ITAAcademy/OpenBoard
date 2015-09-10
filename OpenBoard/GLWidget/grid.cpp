#include "grid.h"

Grid::Grid(int cellSize,int winWidth,int winHeight)
{
setSize(cellSize);
windowWidth=winWidth;
windowHeight=winHeight;
processLCP();
}
Grid::Grid()
{
}

void Grid::setSize(int size)
{
    cellWidth=size;
    cellHeight=size;
}

void Grid::setCellWidth(int w)
{
    cellWidth=w;
}

void Grid::setCellHeight(int h)
{
    cellHeight=h;
}
void Grid::processLCP()
{
    int stepsX = windowWidth/cellWidth;
    int stepsY = windowHeight/cellHeight;
   for (int i=0;i<=stepsY;i++)
       for (int j=0;j<=stepsX;j++)
           leftCornerPoints.append(QPoint(cellWidth*j,windowHeight-cellHeight-cellHeight*i));
}

QVector<QPoint> Grid::getLCP()
{
    return leftCornerPoints;
}
QPoint Grid::closeToLCP(QPoint pt){
    int minDistance=10000;
    QPoint closestPt;
    for (QPoint cornerPoint : leftCornerPoints )
    {
        int dist = sqrt(pow(cornerPoint.x()-pt.x(),2)+pow(cornerPoint.y()-pt.y(),2));
        if (dist < minDistance){
            minDistance = dist;
            closestPt=cornerPoint;
        }
    }
    return closestPt;
}

int Grid::getWidth()
{
    return cellWidth;
}

int Grid::getHeight()
{
    return cellHeight;
}


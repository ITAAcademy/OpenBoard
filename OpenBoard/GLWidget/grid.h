#ifndef GRID_H
#define GRID_H
#include <QPoint>
#include <QVector>

class Grid
{
    int cellWidth;
    int cellHeight;
    int windowWidth;
    int windowHeight;
    QVector<QPoint> leftCornerPoints;
public:
    Grid(int cellSize, int winWidth, int winHeight);
    Grid();
    void setSize(int size);
    int getWidth();
    int getHeight();

    void processLCP();
    QVector<QPoint> getLCP();
    QPoint closeToLCP(QPoint pt);
};

#endif // GRID_H

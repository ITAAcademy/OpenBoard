#ifndef GRID_H
#define GRID_H


class Grid
{
    int cellWidth;
    int cellHeight;
public:
    Grid(int cellSize);
    Grid();
    void setSize(int size);
    int getWidth();
    int getHeight();
};

#endif // GRID_H

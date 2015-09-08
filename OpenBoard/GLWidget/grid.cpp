#include "grid.h"

Grid::Grid(int cellSize)
{
setSize(cellSize);
}
Grid::Grid()
{
}

void Grid::setSize(int size)
{
    cellWidth=size;
    cellHeight=size;
}


int Grid::getWidth()
{
    return cellWidth;
}

int Grid::getHeight()
{
    return cellHeight;
}


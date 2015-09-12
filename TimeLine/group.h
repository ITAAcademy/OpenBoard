#ifndef GROUP_H
#define GROUP_H
#pragma once
//#include <../OpenBoard/drawSystem/drawelement.h>
#include <QMap>
#include <QRect>

class DrawElement;
typedef QMap<int, DrawElement*> BlockType;

class Group
{

    QMap<int, BlockType > members;
    QRect bound_rec;
    int first_col = 0;
    int blockHeight = 100;
    int spacing_blocks = 2;
    bool isGroupRecalculated = false;
    bool bValid = false;

    void setBoundRec(QRect);
    void setBoundRec(int , int , int, int);
    void setBoundRec(int , int );
    void calcBoundRec(QList<DrawElement *> first, QList<DrawElement *> last);
    void calcNotNullMembers();

public:
    int getMembersSize();
    void clear();
    void setBlocksBorderColor(QString color);
    bool isGroupValid();
    void initGroupBlocks();
    void deInitGroupBlocks();
    QRect getBoundRec();

    bool addTo(DrawElement *element);
    bool removeFromGroup(int col,int ind);
    bool removeFromGroup(DrawElement *element);
    int getSpacingBlocks() const;
    void setSpacingBlocks(int value);

    Group();
    ~Group();
};

#endif // GROUP_H

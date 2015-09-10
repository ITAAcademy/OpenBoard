#ifndef GROUP_H
#define GROUP_H
#pragma once
//#include <../OpenBoard/drawSystem/drawelement.h>
#include <QMap>
#include <QRect>

class DrawElement;


class Group
{

   QMap<int, QMap <int, DrawElement*> > members;
    QRect bound_rec;
    int first_col = 0;
    int blockHeight = 100;
    int spacing_blocks = 2;

    int* first_ind_not_null;
    int* last_ind_not_null;
    int first_col_not_null = -1;
    int last_col_not_null = -1;
public:
    int getMembersSize();
    void setBlocksBorderColor(QString color);
    bool isGroupValid();
    void calcNotNullMembers();
    void calcGroupBlocks();
    QRect getBoundRec();
    void setBoundRec(QRect);
    void setBoundRec(int , int , int, int);
    void setBoundRec(int , int );
    void calcBoundRec();
    bool addTo(DrawElement *element);
    bool removeFromGroup(int col,int ind);
    bool removeFromGroup(DrawElement *element);

    bool isElementColIndexValid(int, int);
    int getSpacingBlocks() const;
    void setSpacingBlocks(int value);

    Group();
    ~Group();
};

#endif // GROUP_H

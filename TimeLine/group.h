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

    int index = -1;
    QMap<int, BlockType > members;
    QMap<int, BlockType > members_buckup;
    QRect bound_rec;
    QPoint left;
    QPoint right;
    bool able_to_do_rebackup = false;
    QList<QPoint> membersPositionList;

    QList <DrawElement*> first;
    QList <DrawElement*> last;

    int first_col = 0;
    int blockHeight = 100;
    int spacing_blocks = 0;
    bool isGroupRecalculated = false;
    bool bValid = false;


    void calcNotNullMembers();
    unsigned long calcMaxMemberTime(int col, int index);
public:
    void makeBackup();
    void reloadFromBuckup();
    bool ablelRebuckup();
    void setBoundRec(QRect);
    bool setBoundRec(int , int , int, int);
    bool setBoundRec(int , int );
    void calcBoundRec();
    int getMembersSize();
    void clear();
    void setBlocksBorderColor(QString color);
    bool isGroupValid();
    void initGroupBlocks();
    void deInitGroupBlocks();
    long int tryGroupResize( long int shift);
    long int tryMemberResize( long int shift, int col, int index );
    bool tryMemberReverce(DrawElement* in, DrawElement *out);
    QRect getBoundRec();

    bool addTo(DrawElement *element);
    bool removeFromGroup(int col,int ind);
    bool removeFromGroup(DrawElement *element);
    int getSpacingBlocks() const;
    void setSpacingBlocks(int value);

    Group();
    ~Group();
    QMap<int, BlockType> getMembers() const;
    QList<QPoint> getMembersPosition();
    QPoint getMembersPosition( int index );
    QList<DrawElement *> getFirst() const;
    QList<DrawElement *> getLast() const;
    int getIndex() const;
    void setIndex(int value);
};

#endif // GROUP_H

#ifndef GROUP_H
#define GROUP_H
#include <../OpenBoard/drawSystem/drawsystem.h>

class Group
{
   QList< QList <DrawElement*> > members;
    INT64 sum_length;
    QRect bound_rec;
    int first_col = 0;
public:
    void calcGroupBlocks();
    QRect getBoundRec();
    void setBoundRec(QRect);
    void setBoundRec(int , int , int, int);
    void setBoundRec(int , int );
    INT64 calcMaxLength();
    void addTo(int, DrawElement *);
    void removeAt(int, int);

    bool isElementColIndexValid(int, int);
    Group();
    ~Group();
};

#endif // GROUP_H

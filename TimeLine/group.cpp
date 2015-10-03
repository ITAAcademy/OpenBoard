#include "group.h"
#include <../OpenBoard/drawSystem/drawelement.h>
#include "listcontroll.h"

Group::Group()
{

}

Group::~Group()
{

}

QList <DrawElement*> members;
INT64 sum_length;
QRect bound_rec;

bool Group::setBoundRec(int x1, int y1, int width  , int height)
{
   bound_rec = QRect(x1,y1,width,height);
}

bool Group::setBoundRec(int x1 ,int width)
{
    bound_rec.setX(x1);
    bound_rec.setWidth(width);
}

QRect Group::getBoundRec()
{
    qDebug() << bound_rec;
    return bound_rec;
}


int Group::getSpacingBlocks() const
{
    return spacing_blocks;
}

void Group::setSpacingBlocks(int value)
{
    spacing_blocks = value;
}

 int Group::getMembersSize()
 {
     return members.size();
 }

 void Group::clear()
 {
    members.clear();
    first.clear();
    last.clear();
    membersPositionList.clear();
 }

void Group::setBlocksBorderColor(QString color)
{
    //QMap<int, QMap<int, DrawElement*>>::iterator first = members.begin();
    foreach ( BlockType value, members) {
        foreach ( DrawElement *elm, value)
        {
            elm->setBlockBorderColor(color);
        }
    }

}

void Group::initGroupBlocks()
{
    if(!bValid)
        return;

    foreach ( BlockType value, members) {
        foreach ( DrawElement *elm, value)
        {
            elm->setGroupWichElBelong(this);
        }
    }
}

void Group::deInitGroupBlocks()
{
  /*  if(!bValid)
        return;
*/
    foreach ( BlockType value, members) {
        foreach ( DrawElement *elm, value)
        {
            elm->setGroupWichElBelong(NULL);
        }
    }
}

long Group::tryGroupResize(long shift)
{
    unsigned long maxCount_MinSize = 0;
    foreach ( BlockType value, members) {
        if(value.size() > maxCount_MinSize)
            maxCount_MinSize = value.size();
    }

    maxCount_MinSize *= minBlockTime;
    qDebug() << bound_rec.width() + shift;
    if(bound_rec.width() + shift < maxCount_MinSize)
    {
        bound_rec.setWidth(maxCount_MinSize);
        foreach ( BlockType value, members) {
            foreach ( DrawElement *elm, value)
            {
                elm->setLifeTime(maxCount_MinSize/value.size(), true);
            }
        }
        return maxCount_MinSize;
    }
    unsigned long int res = 0;
    foreach ( BlockType value, members) {

        int not_null = 0;
        foreach ( DrawElement *elm, value)
            if(elm->getLifeTime() > minBlockTime || shift > 0)
                not_null++;
        if(not_null == 0)
            continue;

        int localShift = shift/not_null;
        foreach ( DrawElement *elm, value)
        {
            elm->setLifeTime(elm->getLifeTime() + localShift, true);
            res += elm->getLifeTime();
        }
    }
    res /= members.size();
    bound_rec.setWidth(res);
    return res;
}

 long Group::tryMemberResize(long shift, int col, int index)
{
    BlockType list = members[col];
    QList<int> keys = list.keys();

    int after = 1;
    unsigned long afterTime = 0;
    qStableSort(keys.begin(), keys.end());
    foreach ( int key, keys)
        if(key == index)
            break;
        else
            after++;
    qDebug() << "AFTER  " << after;

    unsigned long allTime = list[index]->getLifeTime();
    for(int i = after; i < list.size(); i++)// zaminutu na for z kluchiv
    {
        allTime += list[keys[i]]->getLifeTime();
    }

    allTime -= (list.size() - after)*minBlockTime;
    qDebug() << list[index]->getLifeTime() + shift << "MAX_Block_TIME " << allTime;
    if(list[index]->getLifeTime() + shift < minBlockTime || allTime <= list[index]->getLifeTime() + shift)
    {
        return 0;
    }
///////////////////////////////////////////////////////////
    unsigned long int res = 0;
    int not_null = 0;
    for(int i = after; i < list.size(); i++)// zaminutu na for z kluchiv
        if(list[keys[i]]->getLifeTime() > minBlockTime || shift < 0)
            not_null++;

    if(not_null == 0)
        return 0;

    int localShift = qFloor(shift/not_null);
    int ka = 0;
    for(int i = after; i < list.size(); i++)// zaminutu na for z kluchiv
    {
        if(list[keys[i]]->getLifeTime() - localShift >= minBlockTime || shift < 0)
        {
            list[keys[i]]->setLifeTime(list[keys[i]]->getLifeTime() - localShift, true);
            ka  += localShift;
        }
    }

    //qDebug() << localShift*not_null;
    list[index]->setLifeTime(ka + list[index]->getLifeTime());
    return ka;
 }

 bool Group::tryMemberReverce(DrawElement *in, DrawElement *out)
 {
     out->setGroupWichElBelong(in->getGroupWichElBelong());
     in->setGroupWichElBelong(NULL);
     members[in->getBlockColumn()][in->getBlockIndex()] = out;
     membersPositionList.clear();
     isGroupValid();
 }


 QMap<int, BlockType> Group::getMembers() const
 {
     return members;
 }

 QPoint Group::getMembersPosition(int index)
 {
     return getMembersPosition()[index];
 }

 QList<QPoint> Group::getMembersPosition()
 {
     if(!membersPositionList.isEmpty())
         return membersPositionList;

     foreach ( BlockType value, members) {
         foreach ( DrawElement *elm, value)
             membersPositionList.append(QPoint(elm->getBlockColumn(), elm->getBlockIndex()));
     }

     return membersPositionList;
 }

 QList<DrawElement *> Group::getFirst() const
 {
     return first;
 }

 QList<DrawElement *> Group::getLast() const
 {
     return last;
 }
 void Group::calcNotNullMembers()
 {


 }

 unsigned long Group::calcMaxMemberTime(int col, int index)
{

}

bool variantLessThan(const int &v1, const int &v2)
{
    return v1 < v2;
}

bool Group::isGroupValid()
{
    first.clear();
    last.clear();
    membersPositionList.clear();
    bValid = false;

    if(members.size() == 0)
        return false;

    bool isRealValid = true;
    QList<int> columns = members.keys();
    qStableSort(columns.begin(), columns.end());

    int first_try = 0;
    while(first_try < columns.size() && isRealValid)
    {
        QList<int> indexs = members[columns[first_try]].keys();
        qStableSort(indexs.begin(), indexs.end());

        int start_index = indexs.first();// load first elm
        for(int i = 1; i < indexs.size(); i++)
        {
            if(indexs[i] - start_index == 1)
            {
                start_index = indexs[i];
            }
            else
            {
                isRealValid = false;
                break;
            }
        }
        first.append(members[columns[first_try]][indexs.first()]);
        last.append(members[columns[first_try]][indexs.last()]);

        first_try++;
    }

    bValid = isRealValid;
    if(!isRealValid)
        return false;

    unsigned long int startTime = first.first()->getStartDrawTime();
    unsigned long int stopTime = last.first()->getStartDrawTime() + last.first()->getLifeTime();

    for(int i = 1; i < first.size(); i++)
    {
        if(first[i]->getStartDrawTime() == startTime && last[i]->getStartDrawTime() + last[i]->getLifeTime() == stopTime)
            continue;

        isRealValid = false;
        break;
    }

    calcBoundRec();

    bValid = isRealValid;
    return isRealValid;
}


void Group::setBoundRec(QRect value)
{
    bound_rec = value;
}

void Group::calcBoundRec()
{
    //qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAA    777 " << this;
    if (this == NULL)
        return;
    if(!bValid || first.size() == 0)
        return;

    left.setX(first.first()->getStartDrawTime());
    left.setY(first.first()->getBlockColumn() * ListControll::blockHeightPlusSpacing);//@BAG@

    right.setX(last.last()->getStartDrawTime() + last.last()->getLifeTime() - left.x());
    right.setY((last.last()->getBlockColumn() + 1)* ListControll::blockHeightPlusSpacing - left.y());//@BAG@

    bound_rec.setRect(left.x(), left.y(), right.x(), right.y());

}

bool Group::addTo(DrawElement *element)
{
    membersPositionList.clear();

    qDebug() << "Size " << members.size() << "  element    " << element;
    if(members.contains(element->getBlockColumn()) && members[element->getBlockColumn()].contains(element->getBlockIndex()))
    {
        removeFromGroup(element);
        return false;
    }

    members[element->getBlockColumn()][element->getBlockIndex()] = element;
    return true;

    qDebug() << "Size " << members.size();
}


bool Group::removeFromGroup(int col, int ind)
{
    //need test
}


bool Group::removeFromGroup(DrawElement *element)
{
    membersPositionList.clear();
    if(members.contains(element->getBlockColumn()) && members[element->getBlockColumn()].contains(element->getBlockIndex()))
    {
        members[element->getBlockColumn()].remove(element->getBlockIndex());
        if(members[element->getBlockColumn()].size() == 0)
            members.remove(element->getBlockColumn());
        return true;
    }
    return false;

}






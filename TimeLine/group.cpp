#include "group.h"
#include <../OpenBoard/drawSystem/drawelement.h>

Group::Group()
{

}

Group::~Group()
{

}

QList <DrawElement*> members;
INT64 sum_length;
QRect bound_rec;

void Group::setBoundRec(int x1, int y1, int width  , int height)
{
   bound_rec = QRect(x1,y1,width,height);
}

void Group::setBoundRec(int x1 ,int width)
{
    bound_rec.setX(x1);
    bound_rec.setWidth(width);
}

QRect Group::getBoundRec()
{
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
    if(!bValid)
        return;

    foreach ( BlockType value, members) {
        foreach ( DrawElement *elm, value)
        {
            elm->setGroupWichElBelong(NULL);
        }
    }
}

void Group::calcNotNullMembers()
{


}

bool variantLessThan(const int &v1, const int &v2)
{
    return v1 < v2;
}

bool Group::isGroupValid()
{
    if(members.size() == 0)
        return false;

    bool isRealValid = true;
    QList<int> columns = members.keys();
    qStableSort(columns.begin(), columns.end());

    QList <DrawElement*> first;
    QList <DrawElement*> last;
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

    bValid = isRealValid;
    return isRealValid;
}


void Group::setBoundRec(QRect value)
{
    bound_rec = value;
}

void Group::calcBoundRec(QList<DrawElement*> first, QList<DrawElement*> last)
{

}

bool Group::addTo(DrawElement *element)
{
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
    if(members.contains(element->getBlockColumn()) && members[element->getBlockColumn()].contains(element->getBlockIndex()))
    {
        members[element->getBlockColumn()].remove(element->getBlockIndex());
        if(members[element->getBlockColumn()].size() == 0)
            members.remove(element->getBlockColumn());
        return true;
    }
    return false;

}






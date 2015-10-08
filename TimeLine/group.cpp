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
//QRect bound_rec;

bool Group::setBoundRec(int x1, int y1, int width  , int height)
{
    // bound_rec = QRect(x1,y1,width,height);
}

bool Group::setBoundRec(int x1 ,int width)
{
    /* bound_rec.setX(x1);
    bound_rec.setWidth(width);*/
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
            if (elm != NULL)
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
    unsigned long int res = 0;
    /* unsigned long maxCount_MinSize = 0;
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
    bound_rec.setWidth(res);*/
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
    //isGroupValid();
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

int Group::getIndex() const
{
    return index;
}

void Group::setIndex(int value)
{
    index = value;
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

bool Group::isGroupValid(QList< QList < QRect > > tracks) //QPoint = block type, life_time; width == 1 mean block is in this group,else 0
{
    first.clear();
    last.clear();
    membersPositionList.clear();
    bValid = false;

    if(members.size() < 1)
        return false;
    else
        if(members.size() == 1)
        {
            // BlockType btype2 = members[0];
            BlockType btype = *(members.begin());
            if (btype.size() <2)
                return false;
        }

    bool isRealValid = true;

    bValid = true;
    return bValid;

    QList<int> columns = members.keys();
    qStableSort(columns.begin(), columns.end());

    /* int first_try = 0;
    while(first_try < columns.size())
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
                //break;
                return false;
            }
        }
        first.append(members[columns[first_try]][indexs.first()]);
        last.append(members[columns[first_try]][indexs.last()]);

        first_try++;
    }*/

    DrawElement * temp = NULL;
    //BlockType
    int x2 = 0;
    int x1 = 65534;
    int y2 = 0;
    int y1 = 65534;

    foreach(BlockType blokType, members)
    {
        foreach(DrawElement * elm, blokType)
            /* for (int i = 0; i < members.size(); i++)
             for (int k = 0; k < members[i].size(); k++)*/
        {
            int start_time = elm->getStartDrawTime();
            int end_time = start_time + elm->getLifeTime();
            if (x1 > start_time)
                x1 = start_time;

            if (x2 < end_time )
                x2 = end_time;

            int col_e = elm->getBlockColumn();
            int top = col_e * 70;
            if (y1 > top )
                y1 = top;
            int bottom = top + 70;
            if (y2 < bottom)
                y2 = bottom;

            // DrawElement * elm =  members[i][k];
            //qDebug() << "col = " << elm->getBlockColumn()<< "  ind = " << elm->getBlockIndex()  << " type = " << elm->getTypeId();
            if (temp != NULL)
            {
                int col_t = temp->getBlockColumn();

                if (col_t == col_e)
                {
                    int ind_t = temp->getBlockIndex();
                    int ind_e = elm->getBlockIndex();

                    if (ind_t + 1 != ind_e)
                        return false;
                }
                /*else
                {
                    if (col_t + 1 != col_e)
                    {
                        return false;
                    }
                }*/
            }
            temp = elm;



        }
    }


    /*int cnt = 0;
    foreach(DrawElement * elm, first)
    {
        int col = elm->getBlockColumn();
        int ind0 = elm->getBlockIndex();
        int ind1 =  last[cnt]->getBlockIndex();
        for (int i=ind0 ; i <= ind1; i++ )
        {
            if ()
        }
    }*/

    // bValid = isRealValid;
    /* if(!isRealValid)
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

    bValid = isRealValid;*/
    int col1 = members.first().first()->getBlockColumn();
    int col2 = members.last().first()->getBlockColumn();
    for (int i = col1; i <=col2; i++)
    {
        int prev_end = 0;
        for (int k = 0; k < tracks[i].size(); k++)
        {
            int life = tracks[i][k].y();
            if (tracks[i][k].x() != Element_type::Empty && tracks[i][k].width() == 0)
            {

                int cur_end = prev_end + life;
                if ( ( x1 <= prev_end && prev_end < x2) || ( x1 <= cur_end && cur_end < x2))
                {
                    return false;
                }

            }
            prev_end += life;
        }
    }







            bValid = true;
    bound_rec.setTopLeft(QPoint(x1,y1));
    bound_rec.setBottomRight(QPoint(x2,y2));
    qDebug() << "bool Group::isGroupValid()  TRUEEEEEEEEEEEE   " << bound_rec.x() << " " <<
                bound_rec.y() << " " << bound_rec.width() << " " << bound_rec.height();
    return true;
}

void Group::makeBackup()
{
    members_buckup = members;
    able_to_do_rebackup = true;
}

bool Group::ablelRebuckup()
{
    return able_to_do_rebackup;
}

void Group::reloadFromBuckup()
{
    members = members_buckup;
}

void Group::setBoundRec(QRect value)
{
    bound_rec = value;
}

void Group::calcBoundRec()
{
    //qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAA    777 " << this;
    /* int aa = -1;
    if(!bValid || first.size() == 0)
        return;

    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAA    777 " ;
    left.setX(first.first()->getStartDrawTime());
    left.setY(first.first()->getBlockColumn() * ListControll::blockHeightPlusSpacing);//@BAG@

    right.setX(last.last()->getStartDrawTime() + last.last()->getLifeTime() - left.x());
    right.setY((last.last()->getBlockColumn() + 1)* ListControll::blockHeightPlusSpacing - left.y());//@BAG@

    bound_rec.setRect(left.x(), left.y(), right.x(), right.y());
*/
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
    element->setGroupWichElBelong(this);
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
        {
            members.remove(element->getBlockColumn());

        }
        element->setGroupWichElBelong(NULL);
        //element->setBlockBorderColor("white");
        return true;
    }
    return false;

}






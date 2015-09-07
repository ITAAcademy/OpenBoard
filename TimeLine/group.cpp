#include "group.h"

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

 void Group::calcGroupBlocks()
 {
     //for (int y=0; y< tracks.size(); y++)
     {
         int prev_blocks_width_sum = 0;
       /*  for (int i=0; i < tracks[y].block.size(); i++)
         {
             DrawElement\ *draw_el = members[i];
             int x_1 =  prev_blocks_width_sum;
             int x_2 = draw_el->getStartDrawTime() + x_1;
             int y_1 = y * blockHeightPlusSpacing;
             int y_2 = blockHeightPlusSpacing + y1;
             int x2 = x + width;
             int y2 = y + height;
             //for future counting
             prev_blocks_width_sum = x_2;
             if (((vmeg(x_1, x, x_2) || vmeg(x, x_1,x2)) && (vmeg(y_1, y,y_2) || vmeg(y, y_1, y2))) //peretyn
                  || (vmeg(x_1, x, x_2) && vmeg(x_1, x2, x_2) && vmeg(y_1, y,y_2) && vmeg(y_1, y2,y_2)))
                 tracks[y].block[i].block_cross_with_yellow_rec = true;
             else
             {
                 tracks[y].block[i].block_cross_with_yellow_rec = false;
                 break;
             }

         }*/
     }
 }

void Group::setBoundRec(QRect value)
{
    bound_rec = value;
}

INT64 Group::calcSumLength()
{
    // for (int i = 0; i < members.size(); i++)/////////////
        // sum_length += members[i]->getLifeTime();
}

void Group::addTo(int col,DrawElement *element)
{
       if (members.size() == 0)
       {
           //first_col
       }
    members[col - first_col].append(element);
  // element->setGroupIndex(members.size() - 1);
}

void Group::removeAt(int col, int ind)
{
   /* members[ind]->setGroupIndex(-1);
    members.removeAt(ind);
    for (int i = ind; i < members.size(); i++)
        members[i]->setGroupIndex(i);*/
}

bool  Group::isElementColIndexValid(int col, int ind)
{
    //if (!(col > -1 && col < members.size() && ind > -1 && ind  < members[col].size()))
    if ((col < 0 || ind < 0) && !(col < members.size() && ind < members[col].size()))
        return false;
    return true;
}





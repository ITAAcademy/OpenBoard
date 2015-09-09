#include "group.h"
#include <../OpenBoard/drawSystem/drawelement.h>

Group::Group()
{

    qDebug() << "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU " << members.size();
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

void Group::calcBoundRec()
{///--=-=-=-=
   // bound_rec
     for (int i = 0; i < members.size(); i++)/////////////
     {
         for (int y = 0; y < members[i].size(); i++)
         {
             DrawElement * draw_el = members[i][y];
             int startX =  draw_el->getStartDrawTime();
             int startY = draw_el->getBlockColumn()*(spacing_blocks + blockHeight);
             int bottomY = startY + spacing_blocks + blockHeight;
             if (bound_rec.x() > startX)
                 bound_rec.setX(startX);
             int rightX = startX +  draw_el->getLifeTime() + spacing_blocks - bound_rec.x();
             if (bound_rec.width() < rightX)
                       bound_rec.setWidth(rightX);

             if (bound_rec.y() > startY)
                 bound_rec.setY(startY);

             if (bound_rec.height() < bottomY)
                       bound_rec.setHeight(bottomY);
         }
     }
}

bool Group::addTo(DrawElement *element)
{
    if (element == NULL)
        return false;
    int block_col = element->getBlockColumn();
    int block_ind = element->getBlockIndex();
    int diff = block_col  - members.size() + 1;
    if (diff > 0)
    {
        for (int i=block_col; i <  members.size() + diff; i++ )
        {

            int diff_ind = block_ind  - members[i].size() + 1;
            if (diff_ind > 0)
            {
                for (int k=block_ind; k <  members[i].size() + diff_ind; k++ )
                {
                    members[i][k] = NULL;
                }
            }
        }
    }
    qDebug() << "PPPPPPPPPPPPPPPPPPP -1";
      if (members.size() == 0)
      {
          members[block_col][block_ind] = (element);
          element->setGroupWichElBelong(this);
          qDebug() << "PPPPPPPPPPPPPPPPPPP --0";
           return false;
      }
       qDebug() << "PPPPPPPPPPPPPPPPPPP 0";
    int first_not_empty_col_ind = -1;
    int last_not_empty_col_ind = -1;
     DrawElement *mamb =  NULL;
    //for (int k=0; k< members.size(); k++)
       for (int i=0; i< members[block_col].size(); i++)
        {
           mamb =  members[block_col][i];
            if (mamb == NULL)
                continue;
            if (first_not_empty_col_ind == -1)
            {
                first_not_empty_col_ind = i;
                last_not_empty_col_ind = i;
            }
            else
            {
                last_not_empty_col_ind = i;
                break;
            }
       }
       if (first_not_empty_col_ind == -1)
           return false;
                    //int mamb_ind = mamb->getBlockIndex();
                    int el_ind = element->getBlockIndex();
                    if ( el_ind == first_not_empty_col_ind - 1  )
                    {
                        members[block_col][block_ind] = (element);
                        element->setGroupWichElBelong(this);
                        qDebug() << "PPPPPPPPPPPPPPPPPPP 1";
                        return true;
                    }   \
                    if (el_ind == last_not_empty_col_ind + 1  )
                    {
                        members[block_col][block_ind] = (element);
                        element->setGroupWichElBelong(this);
                        qDebug() << "PPPPPPPPPPPPPPPPPPP 2";
                        return true;
                    }



    if (bound_rec.x() <= element->getStartDrawTime() &&
            bound_rec.width() + bound_rec.x() <= element->getStartDrawTime() + element->getLifeTime())
    {
       // int el_col = element->getBlockColumn();
        if ( block_col == first_not_empty_col_ind - 1)
        {
           /* QList<DrawElement*> temp_list;
            temp_list.append(element);*/
            members[block_col][block_ind] = (element);
            element->setGroupWichElBelong(this);
            qDebug() << "PPPPPPPPPPPPPPPPPPP 3";
            return true;
        }
        else
        if (block_col == last_not_empty_col_ind + 1)
        {
            /*QList<DrawElement*> temp_list;
            temp_list.append(element);*/
            members[block_col][block_ind] = (element);
            element->setGroupWichElBelong(this);
            qDebug() << "PPPPPPPPPPPPPPPPPPP 4";
            return true;
        }
    }

}

bool Group::removeFromGroup(int col, int ind)
{
     qDebug() << "MMMMMMMM000000 col = " << col << " ind = " << ind << "\n\t\t members.size() = "
              << members.size();
   /* members[ind]->setGroupIndex(-1);
    members.removeAt(ind);
    for (int i = ind; i < members.size(); i++)
        members[i]->setGroupIndex(i);*/
    if (col > -1 && ind > -1 )
        //if (col <members.size() && ind < members[col].size())
        {
           qDebug() << "MMMMMMMM1111 getGroupWichElBelong = " << members[col][ind]->getGroupWichElBelong();
            members[col][ind]->setGroupWichElBelong(NULL);
            members[col][ind]->setBlockBorderColor("white");
            members[col][ind] = NULL;
            qDebug() << "MMMMMMMM222 getGroupWichElBelong = " << members[col][ind]->getGroupWichElBelong();
            return true;
        }
    return false;

}


bool Group::removeFromGroup(DrawElement *element)
{
    int col = element->getBlockColumn();
    int ind = element->getBlockIndex();
   return removeFromGroup(col,ind);
}

bool  Group::isElementColIndexValid(int col, int ind)
{
    //if (!(col > -1 && col < members.size() && ind > -1 && ind  < members[col].size()))
    if ((col < 0 || ind < 0) && !(col < members.size() && ind < members[col].size()))
        return false;
    return true;
}





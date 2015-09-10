#include "group.h"
#include <../OpenBoard/drawSystem/drawelement.h>

Group::Group()
{

    qDebug() << "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU " << members.size();
    for (int i=0; i < members.size(); i++ )
    {
        int mem_i_size = members[i].size();
            for (int k=0; k < mem_i_size; k++ )
            {
                members[i][k] = NULL;
            }
        }
}

Group::~Group()
{
    delete first_ind_not_null;
    delete last_ind_not_null;
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

void Group::setBlocksBorderColor(QString color)
{
    for (int k = first_col_not_null; k <last_col_not_null + 1; k++ )
    {
        for (int i= first_ind_not_null[k]; i<  last_ind_not_null[k] + 1; i++)
        {
            if (members[k][i] != NULL) //protection of crash
                members[k][i]->setBlockBorderColor(color);
        }
    }
}

void Group::calcNotNullMembers()
{
    int mem_size = members.size();
    if (mem_size == 0)
    {
        qDebug() << "Group::isGroupValid\t members.size() = 0";
        return;
    }
    delete first_ind_not_null;
    delete last_ind_not_null;

     first_ind_not_null = new int[mem_size];
     last_ind_not_null = new int[mem_size];
     first_col_not_null = -1;
     last_col_not_null = -1;

     for (int k = 0; k <mem_size; k++ )
         {
             first_ind_not_null[k] = -1;
             last_ind_not_null[k] = -1;
         }
     for (int k = 0; k <mem_size; k++ )
     {
         bool not_null = false;
         for (int i=0; i< members[k].size(); i++)
         {
             if (members[k][i] != NULL)
             {
                 if (!not_null)
                 {
                  first_ind_not_null[k] = i;
                  first_col_not_null = k;

                  not_null = true;
                 }
                 last_col_not_null = k;
             }
             else
             {
                 if (not_null)
                 {
                  last_ind_not_null[k] = i;
                  last_col_not_null = k;
                  i = members[k].size() + 5;
                 }
             }
         }
     }


}

bool Group::isGroupValid()
{
    int mem_size = members.size();
    if (mem_size == 0)
    {
        qDebug() << "Group::isGroupValid\t members.size() = 0";
        return false;
    }
   /* int first_ind_not_null[mem_size];
    int last_ind_not_null[mem_size];
    int first_col_not_null = -1;
    int last_col_not_null = -1;

    for (int k = 0; k <mem_size; k++ )
        {
            first_ind_not_null[k] = -1;
            last_ind_not_null[k] = -1;
        }



    for (int k = 0; k <mem_size; k++ )
    {
        bool not_null = false;
        for (int i=0; i< members[k].size(); i++)
        {
            if (members[k][i] != NULL)
            {
                if (!not_null)
                {
                 first_ind_not_null[k] = i;
                 first_col_not_null = k;

                 not_null = true;
                }
                last_col_not_null = k;
            }
            else
            {
                if (not_null)
                {
                 last_ind_not_null[k] = i;
                 last_col_not_null = k;
                 i = members[k].size() + 5;
                }
            }
        }
    }*/

    int start_time = members[first_col_not_null][first_ind_not_null[first_col_not_null]]->getStartDrawTime();
    int end_time = members[first_col_not_null].last()->getStartDrawTime();
   int prev_block_index = first_ind_not_null[first_col_not_null];
    if (members[first_col_not_null].size() > 0)
    for (int k = 1; k <members[first_col_not_null].size(); k++ )
    {
     int mem_i_k_index =  members[first_col_not_null][k]->getBlockIndex();
        if (prev_block_index + 1 != mem_i_k_index)
        {
            qDebug() << "Group::isGroupValid\t members[0] blocks dont in sequence";
            return false;
        }
        prev_block_index = mem_i_k_index;
    }
    for (int i= first_col_not_null + 1; i< last_col_not_null; i++)
    {
        int mem_i_size = last_ind_not_null[i]+1;
        if (mem_i_size == 0)
        {
            qDebug() << "Group::isGroupValid\t members[" << i << "].size() = 0";
            return false;
        }
        if (start_time != members[i][0]->getStartDrawTime())
        {
            qDebug() << "Group::isGroupValid\t members[" << i << "].getStartDrawTime() != start_time";
            return false;
        }
        if (end_time != members[i].last()->getStartDrawTime())
        {
            qDebug() << "Group::isGroupValid\t members.last()->getStartDrawTime() != end_time";
            return false;
        }
        int prev_block_index = 0;
        if (mem_i_size > 0)
        for (int k = first_ind_not_null[i]; k <mem_i_size; k++ )
        {
         int mem_i_k_index =  members[i][k]->getBlockIndex();
            if (prev_block_index + 1 != mem_i_k_index)
            {
                qDebug() << "Group::isGroupValid\t members[0] blocks dont in sequence";
                return false;
            }
            prev_block_index = mem_i_k_index;
        }
    }
    return true;
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
    int block_ind = element->getBlockIndex();//-=-=-=


    int mem_size = members.size();
   /* qDebug() << "block_col = " <<block_col <<", block_ind = " <<block_ind
             <<",\nmembers.size() = " << mem_size<<",diffcol = " << diff ;*/
    if (block_col + 2 > mem_size )
    {
        qDebug() <<"BBBBBBBBBBBBilshe";
        for (int i=0; i <  block_col+1; i++ )
        {

            int mem_i_size = members[i].size();
            /*int diff_ind = block_ind  - mem_i_size + 1;
            qDebug() << "diff_ind = " <<diff_ind ;
            qDebug() << "  mem_i_size = "<< mem_i_size;
         /*   qDebug() << "block_ind = " <<block_ind ;
            qDebug() << "members[i].size() = " << mem_i_size ;*/

            if (block_ind + 1 > mem_i_size)
            {
                qDebug() <<"BBBBBBBBBBBBilshe mem_i_size = " << mem_i_size;
                for (int k=mem_i_size; k < block_ind  + 1; k++ )
                {
                    //qDebug() << "k = " <<k ;
                    members[i][k] = NULL;
                }
            }
        }
    }
    ///all empty zanuleny
    members[block_col][block_ind] = (element);
    Group *to_this = this;
    qDebug() << "ssssssssssss   to_this = " << to_this;
    element->setGroupWichElBelong(to_this);
    return true;


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
            //qDebug() << "MMMMMMMM222 getGroupWichElBelong = " << members[col][ind]->getGroupWichElBelong();
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





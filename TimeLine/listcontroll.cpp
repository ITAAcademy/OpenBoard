#include "listcontroll.h"
#include <QVariant>
#include <QCoreApplication>

QPoint ListControll::getSelectedBlockPoint() const
{

    if (tracks.size() > 0 && selectedBlockPoint.x() >= 0 && tracks.length() > selectedBlockPoint.x()  && tracks[selectedBlockPoint.x()].block.length() > selectedBlockPoint.y())
        return selectedBlockPoint;
    return QPoint(-1,-1); // ALL BAD
}

QString ListControll::getBlockBorderColor(int col,int ind)
{
    if (!blockValid(col,ind))
        return QString("-1");
    return getBlock(col,ind)->getBlockBorderColor();
}

void ListControll::setSelectedBlockPoint(const QPoint &value)
{

             // qDebug() << "AAAAAAAAAAAAAAAAAAAAAAA  ListControll::setSelectedBlockPoint  " <<(int)  getBlock(value)->getTypeId();
    emit updateSelectedBlock(value);
    //if (false)
    if (ctrl_pressed)
     if ( value.x() != -1) //glWindInited &&
         if ( blockValid(value.x(), value.y()))  //crash
    {


             //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIII ";
             group_changed = true;
        DrawElement * draw_el = getBlock(value);
        QString colora("red");
        Group * bl_group = draw_el->getGroupWichElBelong();
        if (bl_group == NULL)
        {
            //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIII 111111111111";

           if (addBlockToGroup(draw_el))
           {
               isGroupChanged = true;
               draw_el->setBlockBorderColor(colora);
               //emit borderColorChangedSignal(value.x(), value.y(), colora);
               qDebug() << "ListControll::setSelectedBlockPoint adding block to group succesfull";
           }
           else
           {
               draw_el->setBlockBorderColor("white");
               qDebug() << "AAAAAAA adding block to group failed!!!!!!!!!!";
           }
           // draw_el->setGroupWichElBelong(bl_group);
        }
        else
        {
            colora = "white";
            if(curent_group == bl_group)
            if (test_group.removeFromGroup(draw_el))
            {
                    draw_el->setBlockBorderColor("white");
                    qDebug() << "ListControll::setSelectedBlockPoint removing block to group succesfull";
                    emit borderColorChangedSignal(value.x(), value.y(), colora);

            }
            else
                qDebug() << "AAAAAAA removing block to group failed!!!!!!!!!!";
            //addBlockToGroup(draw_el);
            //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIII 222222222222222222";
        }
        //qDebug() << "AAAAAAAAAAAAAAAA bl_group = " << draw_el->getGroupWichElBelong();
        qDebug() << "\n\n";

    }

    if(value != selectedBlockPoint)
    {

        if(!ctrl_pressed)
        {
            DrawElement *elm = getBlock(selectedBlockPoint);
            if(elm != NULL  && elm->getGroupWichElBelong() != NULL)
            {
                elm->getGroupWichElBelong()->setBlocksBorderColor("white");
                removeRectangle();
            }

            elm = getBlock(value);

            if(elm != NULL && elm->getGroupWichElBelong() != NULL)
            {
                elm->getGroupWichElBelong()->setBlocksBorderColor("blue");
                curent_group = elm->getGroupWichElBelong();
                drawYellowRectangle(curent_group->getBoundRec());
            }
            else
            {
                qDebug() << NULL;
                curent_group = NULL;
            }

        }

        selectedBlockPoint = value;

    }

}

void ListControll::setSelectedBlockPoint(int col, int ind)
{
      //if(testIndexs(col, ind))

    setSelectedBlockPoint(QPoint(col,ind));

    // //qDebug() <<"FFFFFFFFFFFF: col = " << selectedBlockPoint.x() << " ind = " << selectedBlockPoint.y();
}



float ListControll::getScaleScrollChildren() const
{
    return scale_scroll_children;
}

void ListControll::setScaleScrollChildren(const float &value)
{
    scale_scroll_children = value;
    if (scale_scroll_children <zoom_speed)
        scale_scroll_children = zoom_speed;
}

void ListControll::changeScaleScrollChildren(const float &value)
{
    scale_scroll_children += value;
    if (scale_scroll_children <zoom_speed)
        scale_scroll_children = zoom_speed;
}



float ListControll::getZoomSpeed() const
{
    return zoom_speed;
}

void ListControll::setZoomSpeed(float value)
{
    zoom_speed = value;
}

bool ListControll::getIsEditBlockShow() const
{
    return isEditBlockShow;
}

void ListControll::setIsEditBlockShow(bool value)
{
    isEditBlockShow = value;
}

int ListControll::getBlockHeightPlusSpacing() const
{
    return blockHeightPlusSpacing;
}


bool ListControll::getCurent_group() const
{
    bool res;
    if(curent_group == NULL)
        res =  false;
    else
        res = true;
 //   qDebug() << "RESSSSSSSS_GROUP   " << res;
    return res;
}
bool ListControll::getCurent_group(int col, int index)
{
    bool res;
    DrawElement *elm = getBlock(col, index);
    if(elm == NULL)
        return false;

    if(elm->getGroupWichElBelong() == NULL)
        res =  false;
    else
        res = true;
   // qDebug() << "RESSSSSSSS_GROUP   " << res;
    return res;
}

long ListControll::tryResizeCurentGroup(int shift)
{
    return curent_group->tryGroupResize(shift);
}

long ListControll::tryResizeMemberInCurentGroup(int shift, int col, int index)
{
    if(curent_group == NULL)
        return 0;

    return curent_group->tryMemberResize(shift, col, index);
}

QPoint ListControll::getCurent_groupMembers( int index )
{
    QPoint qwe;
    if(curent_group == NULL)
        return qwe;

    return curent_group->getMembersPosition(index);
}

int ListControll::getCurent_groupMembersSize()
{
    return curent_group->getMembersPosition().size();
}



void ListControll::recountMaxTrackTime()
{
    maxTrackTime = 0;
    for (int i=0; i < tracks.size(); i++)
    {
        long temp_time = tracks[i].getTime();
        if (maxTrackTime < temp_time)
        {
            maxTrackTime = temp_time;
        }
    }
}

void ListControll::showF_manager(QPoint pos)
{
    f_manager.show();
    f_manager.setPosition(pos);
}

void ListControll::showF_manager()
{
    f_manager.show();
}

void ListControll::setPosF_manager(QPoint pos)
{
    f_manager.setPosition(pos);
}

void ListControll::showF_manager(int x, int y)
{
    showF_manager(QPoint (x,y));
}


void ListControll::setPosF_manager(int x,int y)
{
   setPosF_manager(QPoint (x,y));
}

void ListControll::setPosDefaultF_manager()
{
    QPoint mouse_pos =  getMousePosition();
    QSize f_man_size = f_manager.getSize();
    QPoint pos(mouse_pos.x() - f_man_size.width()/2,
               mouse_pos.y() - f_man_size.height()/2);
   setPosF_manager(pos);
}




void ListControll::hideF_manager()
{
    f_manager.hide();
}

bool ListControll::getGlWindInited() const
{
    return glWindInited;
}

void ListControll::setGlWindInited(bool value)
{
    glWindInited = value;
}


QString ListControll::getBlockKey(int col, int i)
{
    if(!testIndexs(col, i))
        return QString();
    return tracks[col].block[i]->getKey();
}

void ListControll::setBlockKey(int col, int i, QString name)
{
    tracks[col].block[i]->setKey(name);
   // test[col][i] = name;
}

bool ListControll::removeBlock(int col, int i )
{
    qDebug() << "ListControll::removeBlock(int col, int i)";
    curent_group = NULL;
    test_group.clear();
    removeRectangle();

    if ((tracks.size()==0 ||  tracks[col].block.size() == 0 ))
        return false;
    if (!(col < tracks.size() && i < tracks[col].block.size()) )
        return false;

    setBlocked(true);
    bool block_in_group = false;
    if (tracks[col].block[i]->getGroupWichElBelong() != NULL)
    {
        removeBlockFromGroup(tracks[col].block[i]);
        block_in_group  = true;
    }
    setSelectedBlockPoint(QPoint(-1,-1));
    if (tracks[col].block.size() > i)
    {
       int temp = tracks[col].block[i]->getLifeTime();
      delete tracks[col].block[i];

       tracks[col].block.removeAt(i);
        tracks[col].addTime(-temp);

   // testColumnWidth[col] -= temp;

      if (!block_in_group)
      {
         if(!balanceBlocksIfIsGroups(col,i))
       {
             updateBlocksIndexFrom(col,i);
             updateBlocksStartTimesFrom(col, i,true);
       }
      }
      else
      {
          updateBlocksIndexFrom(col,i);
          updateBlocksStartTimesFrom(col, i,true);
      }
    recountMaxTrackTime();
    }


    calcPointedBlocks();
    setBlocked(false);
    return true;
}

void ListControll::addNewBlock(int col, QString str, DrawElement *element)
{
  /*  QString open = QFileDialog::getOpenFileName();
    DrawElement *elm = GenerationDrawElement(open);
    if(elm == NULL)
        return;
    // //qDebug() << "9999999999999999999999999999999999999999999999" << elm->getType();*/
    setSelectedBlockPoint(QPoint(-1,-1));
   /* DrawElement * temp;
    temp.key = str;
    if(element != NULL)
    {
        temp.draw_element = element;
    }
    //temp.draw_element->setLifeTime(def_min_block_width);
    if(temp.draw_element->getLifeTime() < def_min_block_width)
        temp.draw_element->setLifeTime(def_min_block_width);
    temp.draw_element->setZ(col);*/




    if (element == NULL)
        element = new DrawElement(NULL,NULL);

    if(element->getLifeTime() < def_min_block_width)
        element->setLifeTime(def_min_block_width);
    element->setKey(str);


    int last_block_ind = tracks[col].block.size();


    element->setBlockColumn(col);
    element->setBlockIndex(last_block_ind);
    connect(element, SIGNAL(borderColorChangedSignal(int,int,QString)),
            this, SIGNAL(borderColorChangedSignal(int,int,QString)));
    connect(element, SIGNAL(sizeChangedSignal(int,int, int, bool)),
        this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));
    qDebug() << "ListControll::addNewBlock     last_block_ind = " << last_block_ind;


    updateBlocksStartTimesFrom(col,last_block_ind);
    tracks[col].block.append(element);

    tracks[col].addTime(element->getLifeTime());
    long temp_time = tracks[col].getTime();
    if (maxTrackTime <  temp_time)
        maxTrackTime =  temp_time;
    calcPointedBlocks();

    for (int i=0;i<tracks.size();i++)
        for (int y=0;y < tracks[i].block.size(); y++)
            qDebug() << " GGGGGGGGGGGGGGGGGGGGGG    " << tracks[i].block[y]->getBlockColumn() <<
                        "  " << tracks[i].block[y]->getBlockIndex();
}



 void ListControll::addBlockAt(int col, int ind,  DrawElement *element, int life_time ,bool need_balance)
 {
     setSelectedBlockPoint(QPoint(-1,-1));
    /* Element temp;
     temp.key = QString("block" + QString::number(qrand()));
     if(element != NULL)
     {
         temp.draw_element = element;
     }
     if(temp.draw_element->getLifeTime() < def_min_block_width)
         temp.draw_element->setLifeTime(def_min_block_width);
     temp.draw_element->setZ(col);
     */
     if (element == NULL)
     {
         element = new DrawElement(NULL,NULL);
     }
     if(element->getKey().isNull())
        element->setKey( QString("block" + QString::number(qrand())));

     element->setLifeTime(life_time);

     tracks[col].block.insert(ind,element);


     element->setBlockColumn(col);
         element->setBlockIndex(ind);

        if(need_balance && element->getGroupWichElBelong() == NULL)
         balanceBlocksIfIsGroups(col,ind + 1);

            updateBlocksIndexFrom(col,ind + 1);
           updateBlocksStartTimesFrom(col,ind + 1);

     tracks[col].addTime(element->getLifeTime());
     long temp_time = tracks[col].getTime();
     if (maxTrackTime <  temp_time)
         maxTrackTime =  temp_time;
     calcPointedBlocks();
 }




void ListControll::addNewTrack( )
{
    QList <DrawElement * >  temp;
   // temp.append(Element());
 //   temp.append(Element());
  //  temp.append(Element());
       int  temp_traclwidth =   def_min_block_width*temp.size();
       Track trak(temp_traclwidth,temp);
        tracks.append(trak);


        int last_track_ind = tracks.size() - 1;
        for (int k = 0; k < tracks[last_track_ind].block.size(); k++)
        {
               tracks[last_track_ind].block[k]->setBlockIndex(k);
               tracks[last_track_ind].block[k]->setBlockColumn(last_track_ind);
        }

   if (maxTrackTime < temp_traclwidth)
       maxTrackTime = temp_traclwidth; //1234
   calcPointedBlocks();
}

void ListControll::loadFromFile(QString path)
{
  //  emit loadFromFileSignal();
     setBlocked(true);
     qApp->processEvents();
    QPoint p = getSelectedBlockPoint();
  /*  if (p.x() > -1)
       tracks[p.x()].time -= tracks[p.x()].block[p.y()].draw_element->getLifeTime();*/
   //QString open = QFileDialog::getOpenFileName();
    QString open;
    if ( path == "")
        open =  QFileDialog::getOpenFileName(0, QString(), QString(), QString(), 0, QFileDialog::DontUseNativeDialog);
    else
        open = path;
   DrawElement *elm = GenerationDrawElement(open);
   if(elm == NULL)
   {
       qDebug() << "loadFromFile(): elm == NULL";
       return;
   }

    if (elm->getTypeId() == Element_type::Image)
    {
      QSize image_size = QPixmap(open).size();
       emit imageLoadedPictureSizeSignal(image_size);
    }

   DrawElement* temp = tracks[p.x()].block[p.y()];
   temp->setBlockIndex(p.y());
   temp->setBlockColumn(p.x());
   int life_time = temp->getLifeTime();
   int new_life_time = elm->getLifeTime();
   int start_time = temp->getStartDrawTime();

   if(temp->getGroupWichElBelong() != NULL)
   {
       temp->getGroupWichElBelong()->tryMemberReverce(temp, elm);
   }
   delete temp;

   tracks[p.x()].block[p.y()] = elm;
   temp = elm;
   temp->setLifeTime(life_time);
   qDebug() << "LIFE_TIME" << life_time;
   if(life_time == 1000)
       setBlockTime(p.x(), p.y(), new_life_time);
   temp->setStartDraw(start_time);
   temp->setZ(p.x());

   int col0 = p.x();
   int ind0 = p.y();


   elm->setBlockColumn(col0);
   elm->setBlockIndex(ind0);
   connect(elm,SIGNAL(borderColorChangedSignal(int,int,QString)),
           this,SIGNAL(borderColorChangedSignal(int,int,QString)));

   QFileInfo file_info(path);

   elm->setKey(file_info.fileName());

    updateBlocksStartTimesFrom(col0,ind0);

   calcPointedBlocks();
// int new_life_time = elm->getLifeTime();
   emit updateSelectedBlock(selectedBlockPoint);
   sendUpdateModel();

   setBlocked(false);
  // qApp->processEvents();
   //emit loadFromFileSignal();
   //emit loadFromFileSignal();
/*
   if(new_life_time > 1000)
   {
       setBlockTime(p.x(),p.y(), new_life_time);
   }
*/
}

bool ListControll::removeLastBlock(int col)
{/*
    setBlocked(true);
    setSelectedBlockPoint(QPoint(-1,-1));
    if (tracks[col].block.size())
    {
  // tracks[col].block.pop_back();

   if (maxTrackTime == tracks[col].time)
   {
       int temp = tracks[col].block.last().draw_element->getLifeTime();
       tracks[col].block.last().clear();
      tracks[col].block.pop_back();
    tracks[col].time -= temp;
    recountMaxTrackTime();

   }
   else
   {
       int temp = tracks[col].block.last().draw_element->getLifeTime();
       tracks[col].block.last().clear();
      tracks[col].block.pop_back();
    tracks[col].time -= temp;
   }
  // if (selectedBlockPoint.x() == col)       selectedBlock = NULL;
   pointed_block.clear();
   setBlocked(false);
    return true;
    }
    setBlocked(false);

    return false;
    */

 return removeBlock(col,tracks[col].block.size() - 1);

}

bool ListControll::removeLastTrack()
{
    curent_group = NULL;
    test_group.clear();
    removeRectangle();

    setBlocked(true);
    if (tracks.size())
    {
    int lastColTime = tracks.last().getTime();

    int last_ind = tracks.size()-1;
//tracks[last_ind].deleteClearBlocks();
    tracks[last_ind].clear();
 tracks.pop_back();
    if(last_ind == 0)
    {
        maxTrackTime = 0;
        pointed_block.clear();
        setSelectedBlockPoint(QPoint(-1,-1));
    }
   else
    {
   // if (maxTrackTime == lastColTime)
        //recountMaxTrackTime();
    this->calcPointedBlocks();
    }
recountMaxTrackTime();


  // if (selectedBlockPoint.x() == tracks.size() - 1)        selectedBlock = NULL;
    setBlocked(false);
    return true;
    }
    setBlocked(false);
    return false;
}

bool ListControll::removeTrack(int col)
{
    curent_group = NULL;
    test_group.clear();
    removeRectangle();

    isBlocked = true;
    if (tracks.size()>col)
    {
    long lastColTime = tracks[col].getTime();
    tracks[col].clear();
    tracks.removeAt(col);

    for (int i = col; i < tracks.size(); i++)
       for (int k = 0; k < tracks[i].block.size(); k++)
           {
                  tracks[i].block[k]->setBlockColumn(i);
           }

    if (maxTrackTime == lastColTime)
        recountMaxTrackTime();

  //  if (selectedBlockPoint.x() == tracks.size() - 1)     selectedBlock = NULL;
    calcPointedBlocks();
    setBlocked(false);
    return true;
    }
    setBlocked(false);
    return false;
}

 void ListControll::reverseBlocks(int col, int init_pos, int end_pos)
 {
   DrawElement* temp = tracks[col].block[init_pos];
   int init_pos_block_index = temp->getBlockIndex();
   int end_pos_block_index = tracks[col].block[init_pos]->getBlockIndex();

   tracks[col].block[init_pos] = tracks[col].block[end_pos];
   tracks[col].block[end_pos] = temp;

   temp->setBlockIndex(init_pos_block_index);
   tracks[col].block[init_pos]->setBlockIndex(end_pos_block_index);
 }

 void  ListControll::moveBlockFromTo(int col0,int ind0, int ind1)
 {
     if (!blockValid(col0,ind0))
         return ;
     if  (!blockValid(col0,ind1))
         return ;

     tracks[col0].block.move(ind0,ind1);

     bool bilshe = false;
     if (ind0 > ind1)
     {
         bilshe = true;
         int temp = ind0;
         ind0 = ind1;
         ind1 = temp;
     }

     updateBlocksIndexFrom(col0,ind0);
     updateBlocksStartTimesFrom(col0,ind0);

     Group * grupa = NULL;
      int time_change = tracks[col0].block[ind0]->getLifeTime();
     for (int i=ind0; i<ind1; i++ )
     {
         grupa = tracks[col0].block[i]->getGroupWichElBelong();
         tracks[col0].setTimeChange(time_change);
         DrawElement * elm =  tracks[col0].block[i];
         if (grupa != NULL)
         {
             if (bilshe)
             {
                balanceBlocksIfIsGroups(col0,ind0,false);
              //  if ()
                addBlockAt(col0, ind1, NULL, time_change,false);
                 updateBlocksIndexFrom(col0,ind0);
                 updateBlocksStartTimesFrom(col0,ind0);
             }
             else
             {

                addBlockAt(col0, ind0, NULL, time_change,false);
                balanceBlocksIfIsGroups(col0,ind1,true);
                updateBlocksIndexFrom(col0,ind0);
                updateBlocksStartTimesFrom(col0,ind0);
             }
             break;
         }
     }


 }

 void  ListControll::moveBlockFromTo(int col0,int ind0,int col1, int ind1)
 {
     DrawElement* temp =  tracks[col0].block[ind0];
     tracks[col0].addTime( -temp->getLifeTime());
    tracks[col0].block.removeAt(ind0);
    for (int k = ind0; k < tracks[col0].block.size(); k++)
    {
        tracks[col0].block[k]->setBlockIndex(k);
    }


            tracks[col1].block.append(temp);
            tracks[col1].addTime(temp->getLifeTime());
            tracks[col1].block.move(tracks[col1].block.size()-1,ind1);

            tracks[col1].block[ind1]->setBlockColumn(col1);

            updateBlocksIndexFrom(col0,ind0);
             updateBlocksStartTimesFrom(col0,ind0);
             updateBlocksIndexFrom(col1,ind1);
             updateBlocksStartTimesFrom(col1,ind1);

             balanceBlocksIfIsGroups(col0,ind0);

 }

 void ListControll::cloneBlock(DrawElement *origin, DrawElement *clone)
 {
    QBuffer buff;
    buff.open(QBuffer::ReadWrite);
    origin->save(&buff);
    QPoint p = QPoint(clone->getBlockColumn(), clone->getBlockIndex());
   // maxTrackTime -= clone->getLifeTime() + origin->getLifeTime();

    if(clone != NULL)
        delete clone;
    buff.seek(0);
    clone = loadDrawElement(&buff);
    clone->setDrawWidget(origin->getDrawWidget());
    tracks[p.x()].block[p.y()] = clone;
    calcPointedBlocks();
    recountMaxTrackTime();
 }

void ListControll::setBlocks(int col,const QList <DrawElement *> &value)
{
     tracks[col].clear();
    tracks[col].block = value;
}

void ListControll::setBlockTime(int col, int i,int value)
{
  //   = value;
    qDebug() << "SET_TIME";
    if(def_min_block_width > value)
        value = def_min_block_width;

        tracks[col].addTime(value - tracks[col].block[i]->getLifeTime());
      tracks[col].block[i]->setLifeTime(value);

      int col0 = col;
      int ind0 = i;
   updateBlocksStartTimesFrom(col,i);
   if ( tracks[col].block[i]->getGroupWichElBelong() == NULL)
         balanceBlocksIfIsGroups(col,i);


      recountMaxTrackTime();
      // //qDebug() << "DDDDD  tracks[col].block[i].draw_element->getLifeTime()=" <<   tracks[col].block[i].draw_element->getLifeTime();
}

void ListControll::setBlockTimeWithUpdate(int col, int i, int value, bool visual)
{
    setBlockTime(col, i, value);
    if(visual)
        emit blockTimeSignel(col, i, value);
}


bool ListControll::balanceBlocksIfIsGroups(int col0, int ind0 , bool calc_time_change)
{
    if (!blockValid(col0,ind0))
        return false;
     long delta;
     if (calc_time_change)
        delta =  tracks[col0].calcTimeChange();
     else
          delta =  tracks[col0].getTimeChange();
    for (int i=ind0; i < tracks[col0].block.size(); i++)
    {
       Group *groupa = tracks[col0].block[i]->getGroupWichElBelong();
        if (groupa == NULL)
        {
            continue;
        }


        if (delta < 0)
        {
            foreach(DrawElement* elm, groupa->getFirst())
            {
                if(elm->getBlockColumn() == col0/* &&  elm->getBlockIndex() == ind0*/)
                {
                    DrawElement *deltaElm = new DrawElement();
                   // deltaElm->setLifeTime(-delta);
                    qDebug() << "UUUUUUUUUUUUUUU delta = "<< delta;
                    addBlockAt(col0, ind0, deltaElm, -delta,false);
                    updateTrackAt(col0);
                    return true;
                }
            }
            break;
        }
        else if (delta > 0)
        {
            int temp_col  = -1;
            int i = 0;
            foreach(DrawElement* elm, groupa->getFirst())
            {
                qDebug() << "i = " << i++;
                if(elm->getBlockColumn() != col0/* &&  elm->getBlockIndex() == ind0*/)
                {
                    //DrawElement *deltaElm = new DrawElement();
                    int cur_col = elm->getBlockColumn();
                    if (temp_col == cur_col)
                        continue;
                    temp_col = cur_col;
                    qDebug() << "UUUUUUUUUUUUUUU delta = "<< delta;
                    addBlockAt(cur_col, elm->getBlockIndex()-1, NULL, delta,false);

                }
            }
             updateModel();
            break;

        }
    }
    return false;
}

void ListControll::updateBlocksStartTimesFrom(int col0,int ind0, bool withGroup)
{
    if (!blockValid(col0,ind0))
        return;

    if (ind0 == 0)
    {
        tracks[col0].block[ind0]->setStartDraw(0);
        ind0++;
    }
    Group *updatedGroup = NULL;
    long delta =  tracks[col0].calcTimeChange();

    for (int i=ind0; i < tracks[col0].block.size(); i++)
    {

        DrawElement *temp_el = tracks[col0].block[i - 1];
        int draw_time = temp_el->getStartDrawTime()  + temp_el->getLifeTime();
        tracks[col0].block[i]->setStartDraw(draw_time);
    }

    if(false) //-=-=-
        for (int i=ind0; i < tracks[col0].block.size(); i++)
        {
            if(updatedGroup != tracks[col0].block[i]->getGroupWichElBelong() && tracks[col0].block[i]->getGroupWichElBelong() != NULL && !tracks[col0].block[i]->getGroupWichElBelong()->isGroupValid())
            {
                updatedGroup = tracks[col0].block[i]->getGroupWichElBelong();
                /*if( updatedGroup->getMembers().contains(col0) &&  updatedGroup->getMembers()[col0].contains(ind0))
                    continue;*/

                if(delta > 0)
                {
                    DrawElement *deltaElm = new DrawElement();
                    deltaElm->setLifeTime(delta);
                    deltaElm->setKey("NULL2");
                    addBlockAt(col0, i - 1, deltaElm);
                    updateBlocksStartTimesFrom(col0, 0, false);
                }
                else
                {
                    foreach(DrawElement* elm, updatedGroup->getFirst())
                    {
                        if(elm->getBlockColumn() != col0)
                        {
                            qDebug() << "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU ";
                            DrawElement *deltaElm = new DrawElement();
                            deltaElm->setLifeTime(-delta);
                            deltaElm->setKey("NULL");
                            addBlockAt(elm->getBlockColumn(), elm->getBlockIndex() - 1, deltaElm);
                        }
                        updateBlocksStartTimesFrom(elm->getBlockColumn(), 0, false);
                    }
                }
            }
        }
 //   sendUpdateModel();
}

void ListControll::updateBlocksIndexFrom(int col, int ind)
{
    if (!blockValid(col,ind))
        return;
    for (int k = ind; k < tracks[col].block.size(); k++)
                tracks[col].block[k]->setBlockIndex(k);
}

void ListControll::setBlockStartTime(int col, int i,int value)
{
   if(testIndexs(col, i))
    tracks[col].block[i]->setStartDraw(value);
}

int ListControll::getBlockStartTime(int col, int i)
{
    if(!testIndexs(col, i))
        return -1;
    return tracks[col].block[i]->getStartDrawTime();
}


void ListControll::setBlockIcon(int col, int i, QImage icon)
{
     tracks[col].block[i]->setIcon(icon);
}

QImage ListControll::getBlockIcon(int col, int i)
{
    if(!testIndexs(col, i))
        return QImage();
    return   tracks[col].block[i]->getIcon();
}



 void ListControll::setDrawX(int col, int i, int value)
 {
     tracks[col].block[i]->setX(value);

 }

 int ListControll::getDrawX(int col, int i)
 {
     if(!testIndexs(col, i))
         return -1;
     return tracks[col].block[i]->getX() ;
 }

 void ListControll::setDrawY(int col, int i, int value)
 {
    tracks[col].block[i]->setY (value);
 }

 int ListControll::getDrawY(int col, int i)
 {
     if(!testIndexs(col, i))
         return -1;
     return tracks[col].block[i]->getY();
 }

 void ListControll::setDrawZ(int col, int i, int value)
 {
     tracks[col].block[i]->setZ(value);
 }

 int ListControll::getDrawZ(int col, int i)
 {
     if(!testIndexs(col, i))
         return -1;
     return tracks[col].block[i]->getZ() ;
 }

 void ListControll::setDrawSize(int col, int i, int width, int height)
 {
     tracks[col].block[i]->setSize(width,height);

 }
 void  ListControll::emitBlockEditedSignal()
 {
  emit blockEditedSignal();
 }

  void  ListControll::emitPlaySignal()
  {
      emit playSignal();
  }
  void  ListControll::emitUpdateTrackAt(int col)
  {
   emit updateTrackAt(col);
  }

  void  ListControll::emitPauseSignal()
  {
      emit pauseSignal();
  }
  void  ListControll::emitStopSignal()
  {
      emit stopSignal();
  }

 QSize ListControll::getDrawSize(int col, int i)
 {
     if(!testIndexs(col, i))
         return QSize(0, 0);
     return tracks[col].block[i]->getSize() ;
 }

 QRect ListControll::getDrawRect(int col, int i)
 {
     if(!testIndexs(col, i))
         return QRect();
     return tracks[col].block[i]->getRect();
 }




int ListControll::getBlockTime(int col, int i )
{
    if(!testIndexs(col, i))
        return -1;
    return tracks[col].block[i]->getLifeTime();
}

DrawElement * ListControll::getBlock(int col, int i)
{
    // //qDebug() << "getBlock(int col, int i)" << col << " " << i;
    if(!blockValid(col, i))
        return NULL;
    return tracks[col].block[i];
}

DrawElement * ListControll::getBlock(QPoint point)
{
    if(!blockValid(point.x(),point.y()))
        return NULL;
    return getBlock(point.x(), point.y());
}

int ListControll::getTrackTime( int col)
{
    if(!testIndexs(col, -1))
        return -1;
    return tracks[col].getTime();
}

int ListControll::getMaxTrackTime( )
{
    return maxTrackTime;
}

int ListControll::getTrackSize(int col)
{
    if(!testIndexs(col, -1))
        return -1;

    int temp = tracks[col].block.size();
    // //qDebug()  << "FHFHHFHFHFHFH getTrackSize = " << temp;
    return temp;
}

 bool ListControll::isProjectChanged()
 {
     return isProjectChange;
 }

 bool ListControll::addBlockToGroup(int col,int ind)
 {
     if (!blockValid(col,ind))
         return false;
   return addBlockToGroup(tracks[col].block[ind]);
 }

 bool  ListControll::addBlockToGroup(DrawElement* block)
 {
     if (block == NULL)
     {
         qDebug() << " ListControll::addBlockToGroup failed: block is null";
         return false;
     }
     if (block->getGroupWichElBelong() !=  NULL)
     {
          qDebug() << " ListControll::addBlockToGroup failed: block group not null";
          return false;
     }

         qDebug() << " ListControll::addBlockToGroup          block->getGroupWichElBelong() == NULL";
         /*if (curent_block_group_num == -1)
         {
             Group temp_group;
            block_groups.append(temp_group);
            block_groups.last().addTo(block);
            curent_block_group_num = block_groups.size() - 1;
            qDebug() << " ListControll::addBlockToGroup 1";

         }
         else
         {
             block_groups[curent_block_group_num].addTo(block);
             qDebug() << " ListControll::addBlockToGroup 2";
         }*/
        if(test_group.addTo(block))
        {
            qDebug() << " ListControll::addBlockToGroup success " << test_group.getMembersSize();
            return true;
        }
        else
        {
            qDebug() << " ListControll::addBlockToGroup failed";
            return false;
        }


     return false;

 }

 bool  ListControll::removeBlockFromGroup(DrawElement* block)
 {
     if (block->getGroupWichElBelong() == NULL)
         return false;
     return (block->getGroupWichElBelong()->removeFromGroup(block));
 }

 void ListControll::setCtrlPressed(bool value)
 {
    if (group_changed)
         if (ctrl_pressed && !value)
     {
                    qDebug() <<"2222222222  test_group START";
         group_changed = false;

         if (test_group.isGroupValid())
         {
             qDebug() <<"2222222222  test_group.isGroupValid() = true";
             if(curent_group != NULL)
                 curent_group->deInitGroupBlocks();

             curent_group = new Group(test_group);
             curent_group->setBlocksBorderColor("blue");
             curent_group->initGroupBlocks();
             drawYellowRectangle(curent_group->getBoundRec());
         }
         else
         {
             test_group.setBlocksBorderColor("white");
             if(curent_group != NULL && test_group.getMembersSize() == 0)
             {
                 curent_group->deInitGroupBlocks();//@BAG@
                 delete curent_group;
                 curent_group = NULL;
             }
qDebug() <<"2222222222  test_group.isGroupValid() = false";
//curent_group.setBlocksBorderColor("green");
         }
         isGroupChanged = false;
     }

    if (!ctrl_pressed && value)
    {
        removeRectangle();
        if(curent_group == NULL)
        {
            qDebug() << "NEW GROUP TEST";
            test_group.clear();
        }
        else
        {
            qDebug() << "CONTINUE ADD TO GROUP";
            test_group = *curent_group;
        }
    }
qDebug() << test_group.getMembersSize();

     ctrl_pressed = value;
 }

 bool ListControll::getCtrlPressed()
 {
     return ctrl_pressed;
 }

 bool ListControll::setSpacingBtwBlocks(int value)
 {
     if (value < 0)
         return false;
     spacing_btw_blocks = value;
 }

 int ListControll::getSpacingBtwBlocks()
 {
     return spacing_btw_blocks;
 }

 bool ListControll::attachBlock(int col, int index, int value)
 {
     if (!blockValid(col,index))
         return false;
     value *=scale_scroll_children;
     qDebug() << "DOVODKA start";
     DrawElement *draw_el = tracks[col].block[index];
     int from_width = draw_el->getLifeTime() + draw_el->getStartDrawTime();
      qDebug() << "from_width =   "<< from_width;
     int dovod_value = 65534;
     bool value_setted = false;

     for (int i=0; ;  i++)
     {
         if (i == col)
             i++;
         if (i >= tracks.size())
             break;
         for (int y=0; y < tracks[i].block.size(); y++)
         {
             DrawElement *draw_el2 = tracks[i].block[y];
             int temp_dovodka = from_width - draw_el2->getLifeTime() - draw_el2->getStartDrawTime();
              //qDebug() << "temp_dovodka =   "<< temp_dovodka;
             if (abs(temp_dovodka) <=  abs(value) && (abs(temp_dovodka) <  abs(dovod_value) ))
             {
                 dovod_value = temp_dovodka;
                 qDebug() << "dovodka value =   "<< dovod_value;
                 value_setted = true;
             }


         }
     }
     dovod_value += draw_el->getStartDrawTime();
     from_width -= dovod_value; //- draw_el->getStartDrawTime();
     if (value_setted)
         draw_el->setLifeTime(from_width );
     qDebug() << "DOVODKA finish "<< dovod_value;
 }

 QRect ListControll::getYellowRect()
 {
     return yellow_rec;
 }

 void ListControll::setIsProjectChanged(bool value)
 {
     isProjectChange = value;
 }


ListControll::ListControll(/*OGLWidget *drawWidget ,*/QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    buffer_is_full = false;
    setSelectedBlockPoint(QPoint(-1,-1));
   resetProjectToDefault();
   /*Group temp_group;
   block_groups.append(temp_group);*/

this->drawWidget = drawWidget;


    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
    //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);\
    view.engine()->rootContext()->setContextProperty("timeControll", this);
    view.engine()->rootContext()->setContextProperty("viewerWidget", &view);
    cloneImg = new ImageClone(this);
    view.engine()->addImageProvider("imageProvider", cloneImg);//&image_provider);
    view.setSource(QUrl("qrc:/main.qml"));
     view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setPersistentOpenGLContext(false);
    view.setColor("transparent");
    view.setMinimumHeight(230);
    view.setMinimumWidth(500);
    view.setHeight(view.minimumHeight());
    view.setWidth(800);
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

  connect(&f_manager, SIGNAL(filePathNameChanged(QString)),this,SLOT(loadFromFile(QString)));

//view.setMaximumHeight(215);
    //loadCurrentTextInTheFirstBlockWhenInit();


}

volatile bool ListControll::getBlocked() const
{
    return isBlocked;
}

void ListControll::setBlocked(volatile bool value)
{
    if(value = true)
        countBlocked++;
    else
        countBlocked--;
    if(countBlocked < 1)
        isBlocked = value;
}

void ListControll::addMsToTimerValue(int ms)
{
  //  qDebug() << "SLOT addMsToTimerValue:"<<ms;
    if(isPlayPauseStop == 1)
        timerValue+=ms;
}




void ListControll::moveWindow()
{
    QPoint posMouse = QCursor::pos();
    view.setPosition( posMouse - framaMousePosition);
}

 void ListControll::resizeWindowWidth(bool left)
 {
     QPoint posMouse = QCursor::pos();
     if (!left )
     {
         int tt = posMouse.x() - view.x();
         if (tt < view.minimumWidth())
             tt = view.minimumWidth();
       view.setWidth(tt)  ;
     }
     else
     {
         int tt = view.x();
       view.setX(posMouse.x());

       tt = view.width() + tt - view.x();
        if (tt < view.minimumWidth())
        {
            view.setX(view.x() + (tt - view.minimumWidth()));
            tt = view.minimumWidth();
        }

       view.setWidth(tt);
     }
 }

 void ListControll::resizeWindowHeight(bool up)
 {
     QPoint posMouse = QCursor::pos();
     if (!up )
     {
         int tt = posMouse.y() - view.y();
         if (tt < view.minimumHeight())
             tt = view.minimumHeight();
       view.setHeight(tt)  ;
     }
     else
     {
         int tt = view.y();
       view.setY(posMouse.y());

       tt = view.height() + tt - view.y();
        if (tt < view.minimumHeight())
        {
            view.setY(view.y() + (tt - view.minimumHeight()));
            tt = view.minimumHeight();
        }

       view.setHeight(tt);
     }
 }

 void  ListControll::setPrevMousePosition()
 {
     prevMousePosition = QCursor::pos();
 }

 void  ListControll::setBlockAnimation(int col, int ind,int state, int time)
 {
     if (state <0 || time < 0 || !blockValid(col, ind))
         return;
     tracks[col].block[ind]->setAnimStateTime(QPoint(state,time));
     //qDebug() << "ListControll::setBlockAnimation = " << time;
 }

 void   ListControll::setBlockAnimationTime(int col, int ind, int time)
 {
     if ( time < 0 || !blockValid(col, ind))
         return;
     int lifeTime=tracks[col].block[ind]->getLifeTime();
     if (time > lifeTime/2)time =lifeTime/2;
     tracks[col].block[ind]->setAnimTime(time);
     qDebug() << "ListControll::setBlockAnimationTime " << time ;
 }

 void   ListControll::setBlockAnimationState(int col, int ind,int state)
 {
     if (state <0  || !blockValid(col, ind))
         return;
     tracks[col].block[ind]->setAnimState((state));
 }

 QPoint  ListControll::getBlockAnimation(int col, int ind)
 {
     if ( !blockValid(col, ind))
         return QPoint (-1,-1);
    return  tracks[col].block[ind]->getAnimStateTimePoint();
 }

 QPoint  ListControll::getMousePosition()
 {
    return QCursor::pos();
 }

    QPoint  ListControll::getPrevMousePosition()
    {
        return prevMousePosition;
    }


 void  ListControll::setFramaMousePosition( const int x,const int y)
 {
     framaMousePosition.setX(x);
     framaMousePosition.setY(y);
 }

 void  ListControll::setFramaMousePosition( const QPoint x)
 {
     framaMousePosition = x;
 }

ListControll::~ListControll()
{

}

void ListControll::show()
{
     setSelectedBlockPoint(-1,-1);
    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();
        \
    }\
}

bool ListControll::save(QIODevice* device)
{
    QDataStream stream(device);
    stream << tracks.size() ;
    QSet<Group*> allGroups;

    for (int i=0; i< tracks.size(); i++)
    {
       tracks[i].save(device);

       for(DrawElement* elm : tracks[i].block)
       {
           if(elm->getGroupWichElBelong() != NULL)
               allGroups.insert(elm->getGroupWichElBelong());
       }
    }

    stream << allGroups.size();
    for(Group* val : allGroups)
    {
        stream << val->getMembersPosition();
    }
   // qDebug() << "Num of saved tracks: " << tracks.size();
    mess_box.setText("Project saved");
    mess_box.show();
    return true;
}

bool ListControll::load(QIODevice* device)
{
    //QDataStream stream(device);

    tracks.clear();
    int tracks_size;
    QDataStream stream(device);
    stream >> tracks_size ;
  //  qDebug() << "Num of loaded tracks: " << tracks_size;
    for (int i=0; i< tracks_size; i++)
    {
        Track temp;
         temp.load(device);
         //qDebug() << "load blocks size in track" << temp.block.size();
         tracks.append(temp);

    }
    //@ CRASH IN RELEASE BUT WORK IN DEBUG @
  //  qApp->processEvents(QEventLoop::AllEvents,10000);
    for (int k=0; k< tracks.size(); k++)
    for (int i=0; i< tracks[k].block.size(); i++)
    {
        connect(tracks[k].block[i],SIGNAL(borderColorChangedSignal(int,int,QString)),
            this,SIGNAL(borderColorChangedSignal(int,int,QString)));
        connect(tracks[k].block[i],SIGNAL(sizeChangedSignal(int,int, int, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));
    }
    // add group
    int numGroups;
    stream >> numGroups;

    for(int i = 0; i < numGroups; i++)
    {
        QList<QPoint> groupPos;
        stream >> groupPos;
        Group *group = new Group();
        for(QPoint pos : groupPos)
        {
            group->addTo(getBlock(pos));
        }
        group->isGroupValid();
        group->initGroupBlocks();
    }

    recountMaxTrackTime();
    calcPointedBlocks();
    setSelectedBlockPoint(-1, -1);
    return true;
}

void ListControll::close()
{
        view.close();
        f_manager.close();
}

void ListControll::hide()
{
    view.hide();
    f_manager.hide();
}

void ListControll::setFocus()
{
   // view.setPosition(view.position());
    if(view.isVisible())
    {
        view.setVisible(false);
        view.setWindowState(Qt::WindowNoState);
        view.setVisible(true);
    }

}

void ListControll::setViewPosition(QPoint pos)
{
    if(view.isVisible())
        view.setPosition(pos);
}

QPoint ListControll::getViewPosition()
{
    return view.position();
}

bool ListControll::isVisible()
{
    return view.isVisible();
}

bool ListControll::isActiveWindow()
{
    return view.isActive();
}



 void ListControll::setScalePointerPos( int x)
 {
     scale_pointer_pos = x;
     calcPointedBlocks();
 //// //qDebug() << "RRRRRRRRRRRRRRR scale_pointer_pos=" << scale_pointer_pos;
 }

 int ListControll::getScalePointerPos( )
 {
     return scale_pointer_pos;
 }

 QList <DrawElement *> ListControll::getPointedBlocks( )
 {
     return pointed_block;
 }
 QList <DrawElement*> ListControll::getPointedBlocksDE( )
 {
     QList <DrawElement*> res;
     for(auto elm : pointed_block)
         res.append(elm);

 //   //qDebug() << "Curent            count of element in scene   =   " << pointed_block.size();
     return res;
 }

 void ListControll::calcPointedBlocks( )
 {

     calcPointedBlocksAtTime(scale_pointer_pos);
      //  //qDebug() << "qweqweqweqweqweqw";
/*
	*		show curent play element
*/
      // //qDebug() << "FFFFFFFFFFFFFFF getPointedBlocks size" << pointed_block.size()
               //<< " scale_pointer_pos " << scale_pointer_pos;
     /* for(int i = 0; i <pointed_block.size(); i++)
      {
          // //qDebug() << i <<  "   " << pointed_block[i].draw_element->getType();
      }*/

 }

 void ListControll::calcPointedBlocksAtTime(int ms )
 {
     pointed_block.clear();
     for (int i=0; i<tracks.size(); i++)
     {
         int blockXstart = 0;
         for (int y=0; y<tracks[i].block.size(); y++ )
         {
             int blockXend = blockXstart + tracks[i].block[y]->getLifeTime();
             if (ms <= blockXend)
             {
                 pointed_block.append(tracks[i].block[y]);
                 //// //qDebug() << "POP: " << i<< " "<<y;
                break;
             }
             blockXstart = blockXend;
         }
     }
 }

void ListControll::calcPointedBlocksAtTime( )
 {
     calcPointedBlocksAtTime(getPlayTime());
 }

 QList <DrawElement*> ListControll::getPointedBlocksAtTime( )
 {
     return pointed_block;
 }

 void  ListControll::play()
 {
    // // //qDebug() << "FFFFFFFFFFFFFFF  emit playSignal();";
     //timer.restart();
     //timerValue=0;
    emit playSignal();
     if (isPlayPauseStop==3)
             time_sum = 0;
     isPlayPauseStop = 1;

 }
 void  ListControll::pause()
 {
     //qDebug() << "AAAAAAAAAAAAAA " << getPlayTime();
     time_sum = getPlayTime();// timer.elapsed();
     isPlayPauseStop = 2;
   // emit pauseSignal();
 }

void  ListControll::stop()
{
   time_sum = 0;
   timerValue=0;
    isPlayPauseStop = 3;
    calcPointedBlocks();
   // qDebug() << "stop                       TIMELINE";

}

qint64 ListControll::getPlayTime()
{
   return timerValue;
   /* if (isPlayPauseStop ==1 )
        //return timer.elapsed() + time_sum;
        return timerValue;
    else
        if (isPlayPauseStop ==2 )
        return  time_sum ;
            else
                return 0;*/
}

void ListControll::setPlayTime(qint64 value)
{
    //time_sum = value;
    timerValue = value;
}

QImage ListControll::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

   // QUrl url("http://lorempixel.com/" + id);
    //QNetworkReply* reply = manager->get(QNetworkRequest(url));
   // QEventLoop eventLoop;
   // QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
   // eventLoop.exec();
 //   if (reply->error() != QNetworkReply::NoError)
 //       return QImage();
    /*if(getSelectedBlock().draw_element->getIcon().isNull())
        return QImage(":/0.png");

    return getSelectedBlock().draw_element->getIcon();*/

            //= QImage::fromData(reply->readAll());
    /*size->setWidth(image.width());
    size->setHeight(image.height());*/
    // //qDebug() << "

    if(!isBlocked)
    {
        QVector <QStringRef> argv = id.splitRef('+');
        DrawElement* elm = getBlock(argv[0].toInt(), argv[1].toInt());
        QImage img = elm->getIcon();
       ////qDebug() << "IMAGE  pp " << getBlock(argv[0].toInt(), argv[1].toInt()).draw_element->getKey();

        if(img.isNull())
        {
                   // //qDebug() << "AAAAAAAAAAAAAAAAAA  id = " << id ;
            if(elm->getTypeId() == Text)
                return QImage(":/iphone_toolbar_icons/Document-Icon.png");

            if(elm->getTypeId() == Video)
                return QImage(":/iphone_toolbar_icons/Video.png");
            if(elm->getTypeId() == Audio)
                return QImage(":/iphone_toolbar_icons/Audio.png");

            return QImage(":/iphone_toolbar_icons/0.png");
        }



        return img;
    }

}

 void ListControll::update()
 {
     emit updateSignal();
  //   qDebug() << getPlayTime()  << "        " << getMaxTrackTime();
     if (this->getMaxTrackTime() < getPlayTime()-40 && getPlayTime() != 0) //1234
     {
         emit stopSignal();
         isPlayPauseStop = 3;

     }
 }

  void ListControll:: emitUpdateSignal()
  {
      emit updateSignal();
  }



 int  ListControll::getTracksNumber()
 {
     return tracks.size();
 }

 void ListControll::sendUpdateModel()
 {
     emit updateModel();
 }

  void ListControll::emitNewProject()
  {
      emit newProjectSignel();
  }

  void ListControll::emitOpenEffects()
  {
      emit showEffectsSignal();
  }

  void ListControll::emitHideEffects()
  {
      emit hideEffectsSignal();
  }

  void  ListControll::copyBlockToBuffer()
  {
      QPoint sel_block = this->getSelectedBlockPoint();
      if (sel_block.x() == -1)
          return;

           block_in_buffer = this->getBlock(sel_block);
         /* DrawElement *blocK_draw_el =  block_in_buffer.draw_element;
          DrawElement *draw_el = new DrawElement(blocK_draw_el->getDrawWidget(),this) ; //();

         // draw_el->setDrawWidget(blocK_draw_el->getDrawWidget());
          draw_el->copy(blocK_draw_el);
          draw_el->setTypeId(blocK_draw_el->getTypeId()); //999999999999

          //block_in_buffer.draw_element->copy(block_in_buffer.draw_element);
          block_in_buffer.draw_element = draw_el;

          */
          life_time_in_buffer = block_in_buffer->getLifeTime();
          buffer_is_full = true;

            qDebug() << "Block copied in buffer";
  }


  void ListControll::pasteBlockFromBuffer()
  {
      if (!buffer_is_full)
          return;
      /*QPoint sel_block = this->getSelectedBlockPoint();
      if (sel_block.x() == -1)
          return;

      tracks[sel_block.x()].appendBlockAt(sel_block.y()+1, block_in_buffer);
      long temp_time = tracks[sel_block.x()].getTime();
      if (maxTrackTime <  temp_time)
          maxTrackTime =  temp_time;
     // calcPointedBlocks();
    */
      cloneBlock(block_in_buffer, getBlock(getSelectedBlockPoint()));
      emit updateTrackAt(getSelectedBlockPoint().x());


  }

   void ListControll::setBlockTimeFromBuffer()
  {
       if (!buffer_is_full)
           return;
       QPoint sel_block = this->getSelectedBlockPoint();
       if (sel_block.x() == -1)
           return;

       setBlockTime(sel_block.x(),sel_block.y(),life_time_in_buffer);
       emit updateTrackAt(sel_block.x());
   }


    void ListControll::emitOpenProject()
    {
        emit openProjectSignel();
        //qDebug() <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    }

    void ListControll::emitSaveProject()
    {
        emit saveProjectSignel();
    }

    void ListControll::emitResetProject()
    {
        emit resetProjectSignel();
    }

    void ListControll::emitFocusLostSignal()
    {
        emit focusLostSignal();
    }

    void ListControll::emitFocusFoundSignal()
    {
        emit focusFoundSignal();
    }

    void ListControll::zoomMinus()
    {
        this->changeScaleScrollChildren(-zoom_speed);
        emit updateModel();
    }

    void  ListControll::zoomPlus()
    {
        this->changeScaleScrollChildren(zoom_speed);
         emit updateModel();
    }

    void  ListControll::drawYellowRectangle(int x,int y, int width, int height)
    {
        yellow_rec = QRect(x,y,width,height);

       emit drawRectangleSignal();
        qDebug() << "ListControll::drawRectangle emitted ";
    }

    bool ListControll::updateYellowRectangle(int x, int y, int width, int height)
    {
        if(!curent_group->setBoundRec(x, y, width, height))
            return false;

        yellow_rec = QRect(x, y, width, height);
        return true;
    }
    void  ListControll::drawYellowRectangle(QRect rect)
    {
        yellow_rec = rect;

       emit drawRectangleSignal();
        qDebug() << "ListControll::drawRectangle emitted ";
    }

   /*void ListControll::calcBlockHighliteViaYellowRec()
   {
       for (int y=0; y< tracks.size(); y++)
       {
           int prev_blocks_width_sum = 0;
           for (int i=0; i < tracks[y].block.size(); i++)
           {
               DrawElement\ *draw_el = tracks[y].block[i].draw_element;
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

           }
       }
   }*/

    bool vmeg(int i1,int i2,int i3) // i1 <=i2 <= i3
    {
        return (i1<= i2 && i2<= i3);
    }

    void ListControll::removeRectangle()
    {
        emit removeRectangleSignal();
    }


    int  ListControll::resetProjectToDefault()
    {
        setBlocked(true);
qDebug() << "1";
        for (int i=0; i< tracks.size(); i++)
            tracks[i].clear();
        qDebug() << "2";
        tracks.clear();
        qDebug() << "3";
        maxTrackTime = 0;
        time_sum = 0;
        setSelectedBlockPoint(QPoint(-1,-1));
        addNewTrack( );
        qDebug() << "4";
        recountMaxTrackTime();
        qDebug() << "5";
        calcPointedBlocks();
        qDebug() << "6";
        setBlocked(false);
    }

    void ListControll::convertCurentBlockToText()
    {
        setBlocked(true);
        DrawElement* elm = tracks[selectedBlockPoint.x()].block[selectedBlockPoint.y()];
        DrawTextElm *text = new DrawTextElm(NULL);
        text->copy(elm);
        delete elm;
        tracks[selectedBlockPoint.x()].block[selectedBlockPoint.y()] = text;
        emit updateSelectedBlock(selectedBlockPoint);
        calcPointedBlocks();
        setBlocked(false);
    }

    bool ListControll::testIndexs(const int col, const int index)
    {
        if(col < tracks.size() && (index < tracks[col].block.size() || index == -1))
            return true;

        return false;
    }

    bool ListControll::blockValid(const int col, const int index)
    {
        if( col > -1 && index > -1 && col < tracks.size() && index < tracks[col].block.size()  )
            return true;
        return false;
    }


    bool ListControll::blockValid(QPoint point)
    {
        return blockValid(point.x(),point.y());
    }




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
    // tracks[0].block[99999]->getLifeTime();

    // qDebug() << "AAAAAAAAAAAAAAAAAAAAAAA  ListControll::setSelectedBlockPoint  " <<(int)  getBlock(value)->getTypeId();
    //if (false)
    //ctrl_pressed = false;
    if (ctrl_pressed)
        if ( value.x() != -1) //glWindInited &&
            if ( blockValid(value.x(), value.y()))  //crash
            {
                group_changed = true;
                DrawElement * draw_el = getBlock(value);
                int el_ind = draw_el->getBlockIndex();
                int el_col = draw_el->getBlockColumn();
                QString colora("red");
                Group * bl_group = draw_el->getGroupWichElBelong();
                bool need_calc_bound_rec = false;
                if (bl_group == NULL)
                {
                    //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIII 111111111111";
                    // curent_group = &test_group;
                    if (curent_group != NULL) ///3456
                        if (curent_group->addTo(draw_el))
                        {
                            need_calc_bound_rec = true;
                            isGroupChanged = true;
                            // curent_group = &test_group;
                            draw_el->setBlockBorderColor(colora);
                            //emit borderColorChangedSignal(value.x(), value.y(), colora);
                            qDebug() << "ListControll::setSelectedBlockPoint adding block to group succesfull";

                            /* if (el_ind > 1)
                        {
                            DrawElement *prev = tracks[el_col].block[el_ind - 1];
                            DrawElement *prev_p =  tracks[el_col].block[el_ind - 2];

                            if (prev != NULL && prev_p != NULL)
                            {
                                int prev_type = prev->getTypeId() ;
                                int prev_p_type = prev_p->getTypeId() ;
                                Group * prev_group = prev->getGroupWichElBelong();
                                Group * prev_p_group = prev_p->getGroupWichElBelong();
                                if (prev_type == Element_type::Empty && prev_group  == NULL
                                        && prev_p_type != Element_type::Empty  && prev_p_group == curent_group)
                                {
                                    addBlockToCurentGroup(prev);
                                }
                            }
                        }
                        if (el_ind < tracks[el_col].block.size() - 2 )
                        {
                            DrawElement *next = tracks[el_col].block[el_ind + 1];
                            DrawElement *next_p =  tracks[el_col].block[el_ind + 2];

                            if (next != NULL && next_p != NULL)
                            {
                                int next_type = next->getTypeId() ;
                                int next_p_type = next_p->getTypeId() ;
                                Group * next_group = next->getGroupWichElBelong();
                                Group * next_p_group = next_p->getGroupWichElBelong();
                                if (next_type == Element_type::Empty && next_group  == NULL
                                        && next_p_type != Element_type::Empty  && next_p_group == curent_group)
                                {
                                    addBlockToCurentGroup(next);
                                }
                            }
                        }*/


                        }
                        else
                        {
                            draw_el->setBlockBorderColor("white");
                            if (el_ind > 0)
                            {
                                DrawElement *prev = tracks[el_col].block[el_ind - 1];
                                if (prev != NULL)
                                {
                                    if (prev->getTypeId() == Element_type::Empty && prev->getGroupWichElBelong()  == curent_group)
                                    {
                                        removeBlockFromGroup(prev);
                                        need_calc_bound_rec = true;
                                    }
                                }
                            }
                            if (el_ind < tracks[el_col].block.size() - 1 )
                            {
                                DrawElement *next = tracks[el_col].block[el_ind + 1];
                                if (next != NULL)
                                {
                                    if (next->getTypeId() == Element_type::Empty && next->getGroupWichElBelong()  == curent_group)
                                    {
                                        removeBlockFromGroup(next);
                                        need_calc_bound_rec = true;
                                    }
                                }
                            }
                        }
                    // draw_el->setGroupWichElBelong(bl_group);
                }
                else
                {
                    colora = "white";
                    //Group * temp = draw_el->getGroupWichElBelong();
                    /* if(&test_group == bl_group)
                    {
                        if (test_group.removeFromGroup(draw_el))
                        {
                            draw_el->setBlockBorderColor("white");
                            // emit borderColorChangedSignal(value.x(), value.y(), colora);
                            if (el_ind > 0)
                            {
                                DrawElement *prev = tracks[el_col].block[el_ind - 1];
                                if (prev != NULL)
                                {
                                    int prev_type = prev->getTypeId() ;
                                    //Group * prev_group = prev->getGroupWichElBelong();
                                    //Group *p_test_group = &test_group;
                                  //  qDebug() << "draw_el gr = " << temp << " prev gr = "<< prev->getGroupWichElBelong();
                                    if (prev_type == Element_type::Empty)
                                        if (prev->getGroupWichElBelong() == bl_group)
                                        {
                                            if ( test_group.removeFromGroup(prev) )
                                                need_calc_bound_rec = true;
                                        }
                                }
                            }
                            if (el_ind < tracks[el_col].block.size() - 1 )
                            {
                                DrawElement *next = tracks[el_col].block[el_ind + 1];
                                if (next != NULL)
                                {
                                    if (next->getTypeId() == Element_type::Empty)
                                        if (next->getGroupWichElBelong() == bl_group)
                                        {
                                            if ( test_group.removeFromGroup(next) )
                                                need_calc_bound_rec = true;
                                        }
                                }
                            }

                        }
                    }*/
                    //else
                    if(curent_group == bl_group)
                    {
                        if (curent_group->removeFromGroup(draw_el))
                        {
                            draw_el->setBlockBorderColor("white");
                            // emit borderColorChangedSignal(value.x(), value.y(), colora);
                            if (el_ind > 0)
                            {
                                DrawElement *prev = tracks[el_col].block[el_ind - 1];
                                if (prev != NULL)
                                {
                                    int prev_type = prev->getTypeId() ;
                                    //Group * prev_group = prev->getGroupWichElBelong();
                                    //Group *p_test_group = &test_group;
                                    //qDebug() << "draw_el gr = " << temp << " prev gr = "<< prev->getGroupWichElBelong();
                                    if (prev_type == Element_type::Empty)
                                        if (prev->getGroupWichElBelong() == bl_group)
                                        {
                                            if ( curent_group->removeFromGroup(prev) )
                                            {
                                                need_calc_bound_rec = true;
                                            }
                                        }
                                }
                            }
                            if (el_ind < tracks[el_col].block.size() - 1 )
                            {
                                DrawElement *next = tracks[el_col].block[el_ind + 1];
                                if (next != NULL)
                                {
                                    if (next->getTypeId() == Element_type::Empty)
                                        if (next->getGroupWichElBelong() == bl_group)
                                        {
                                            if ( curent_group->removeFromGroup(next) )
                                            {
                                                need_calc_bound_rec = true;
                                            }
                                        }
                                }
                            }

                        }
                    }
                    else
                        qDebug() << "AAAAAAA removing block to group failed!!!!!!!!!!";
                    //addBlockToGroup(draw_el);
                    //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIII 222222222222222222";
                }
                //qDebug() << "AAAAAAAAAAAAAAAA bl_group = " << draw_el->getGroupWichElBelong();
                qDebug() << "\n\n";
                if (need_calc_bound_rec)
                {
                    // if (test_group.isGroupValid())
                    // curent_group->calcBoundRec();
                    /* else
                    {
                        test_group.setBlocksBorderColor("white");
                        test_group.deInitGroupBlocks();
                        test_group.clear();


                    }*/
                }

            }
    \
    if(value != selectedBlockPoint)
    {

        if(!ctrl_pressed)
        {

            if (curent_group != NULL)
            {
                removeRectangle();
                curent_group->setBlocksBorderColor("white");
            }

            curent_group = NULL;
            //if (blockValid(value))
            {
                //DrawElement *select =  tracks[value.x()].block[value.y()];
                DrawElement *elm = getBlock(value);
                if (elm != NULL)
                {
                    Group * t_group  = elm->getGroupWichElBelong();
                    if (t_group != NULL)
                    {
                        curent_group = t_group;
                        // if (t_group->isGroupValid())
                        {


                            //DrawElement *elm = getBlock(selectedBlockPoint);
                            if(elm != NULL  && elm->getGroupWichElBelong() != NULL)
                            {
                                elm->getGroupWichElBelong()->setBlocksBorderColor("white");
                                removeRectangle();
                            }

                            elm = getBlock(value);

                            if(elm != NULL && elm->getGroupWichElBelong() != NULL)
                            {
                                elm->getGroupWichElBelong()->setBlocksBorderColor("blue");
                                drawYellowRectangle(curent_group->getBoundRec());
                                //curent_group = elm->getGroupWichElBelong();
                                // t_group->calcBoundRec(); !!!!!!!!!!!!!!!!
                                //drawYellowRectangle(curent_group->getBoundRec());
                                qDebug() << "rawYellowRectangle(curent_group->getBoundRec());";
                            }
                        }
                        /* else
                        {
                            t_group->setBlocksBorderColor("white");
                            t_group->deInitGroupBlocks();
                            t_group->clear();


                        }*/
                    }
                }
            }

        }

        selectedBlockPoint = value;
        emit updateSelectedBlock(value);
        emit updateSelectBlock();

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
/*
bool ListControll::redrawYellowRect()
{
    curent_group->calcBoundRec();
    drawYellowRectangle(curent_group->getBoundRec());
}*/

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

QList<DrawElement *> ListControll::getBlocksInCurrentGroup()
{
    QList<DrawElement *> res;
    QMap<int, BlockType> members =  curent_group->getMembers(); //1313
    foreach ( BlockType value, members) {
        foreach ( DrawElement *elm, value)
        {
            res.append(elm);
        }
    }
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
    //curent_group->calcBoundRec();
    return curent_group->getMembersPosition().size();

}




OGLWidget *ListControll::getP_drawWidget() const
{
    return p_drawWidget;
}

void ListControll::setP_drawWidget(OGLWidget *value)
{
    p_drawWidget = value;
}
void ListControll::recountMaxTrackTime()
{
    maxTrackTime = 0;
    for (int i=0; i < tracks.size(); i++)
    {
        quint64 temp_time = tracks[i].getTime();
        if (maxTrackTime < temp_time)
            maxTrackTime = temp_time;
    }
    emit maxTrackTimeChanged(maxTrackTime);
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

void ListControll::setLoadF_manager(bool file_or_library)
{
    this->load_from_file_or_library = file_or_library;
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
/*
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
    clone = loadDrawElement(&buff, VERSION);
    clone->setDrawWidget(origin->getDrawWidget());
    tracks[p.x()].block[p.y()] = clone;
    calcPointedBlocks();
    recountMaxTrackTime();
}
*/
void ListControll::cloneDrawElement (DrawElement *origin, DrawElement *clone)
{
    /* QBuffer buff;
    buff.open(QBuffer::ReadWrite);
    origin->save(&buff);
    // QPoint p = QPoint(clone->getBlockColumn(), clone->getBlockIndex());
    // maxTrackTime -= clone->getLifeTime() + origin->getLifeTime();

    if(clone != NULL)
        delete clone;
    buff.seek(0);
    clone = loadDrawElement(&buff, VERSION);
    clone->setDrawWidget(origin->getDrawWidget());
    // tracks[p.x()].block[p.y()] = clone;
    //calcPointedBlocks();
    // recountMaxTrackTime();*/
}



bool ListControll::removeBlock(int col, int i, bool copy_in__buffer, bool del_last_empty , bool del_draw_el )
{
    qDebug() << "ListControll::removeBlock(int col, int i)";
    removeRectangle();

    if ((tracks.size()==0 ||  tracks[col].block.size() == 0 ))
        return false;
    if (!(col < tracks.size() && i < tracks[col].block.size()) )
        return false;

    setBlocked(true);
    bool block_in_group = false;

    DrawElement *elm = tracks[col].block[i];

    if (copy_in__buffer)
    {
        /* if (block_in_buffer != NULL)
            delete block_in_buffer;*/
        // cloneDrawElement( elm, block_in_buffer);
    }

    if (elm->getGroupWichElBelong() != NULL)
    {
        removeBlockFromGroup(elm);
        block_in_group  = true;
    }
    setSelectedBlockPoint(QPoint(-1,-1));

    int l_time = elm->getLifeTime();
    DrawElement * temp = new DrawElement(NULL,NULL);

    /*  delete elm;
    elm = temp;*/
    temp->copy(elm);
    temp->setBlockColumn(col);
    temp->setBlockIndex(i);
    tracks[col].block[i] = temp;
    if (del_draw_el)
        delete elm;
    // elm = tracks[col].block[i];

    if (i > 0)
    {
        DrawElement *prev = tracks[col].block[i -1];
        if (prev != NULL)
        {
            int type = prev->getTypeId();
            if (type == Element_type::Empty )
            {
                int p_time = prev->getLifeTime();
                prev->setLifeTime( p_time + l_time,false,true, false );
                // tracks[col].addTime(l_time);
                tracks[col].block.removeAt(i);
                delete temp;
                temp = prev;

                i--; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                updateBlocksIndexFrom(col,i);

            }
        }
    }

    if (i +1 < tracks[col].block.size() )
    {
        DrawElement * next_el = tracks[col].block[i + 1];
        if (next_el != NULL)
            if (next_el->getTypeId() == Element_type::Empty)
            {
                l_time = temp->getLifeTime();
                temp->setLifeTime(next_el->getLifeTime() + l_time,false,true, false);
                // tracks[col].addTime(l_time);
                tracks[col].block.removeAt(i + 1);
            }
    }
    if (del_last_empty)
    {
        DrawElement *tmp = tracks[col].block.last();
        if (tmp->getTypeId() ==  Element_type::Empty)
        {
            //tracks[col].addTime(-tmp->getLifeTime());
            delete tmp;
            tmp = NULL;
            tracks[col].block.removeLast();
            tracks[col].updateTime();
        }

    }
    recountMaxTrackTime();

    //int track_size = tracks[col].block.size();
    updateBlocksStartTimesFrom(col, 0,true);
    updateBlocksIndexFrom(col,0);
    balanceBlocksIfIsGroups(col,i);

    calcPointedBlocks();
    setBlocked(false);
    return true;
}

int ListControll::getBlockTypeId(int col,int ind)
{
    if (!blockValid(col,ind))
        return -1;
    return tracks[col].block[ind]->getTypeId();
}

int ListControll::getBlockTypeIdInt(int col,int ind)
{
    int value =( int) getBlockTypeId(col,ind);
    //qDebug() << "int ListControll::getBlockTypeIdInt(int col,int ind) = " << value;
    return value;
}


bool ListControll::createEmptyBlock(int col)
{

    // qDebug() << "bool ListControll::createEmptyBlock(int col,int ind)";

    if (col < 0 || col >= tracks.size())
        return false;
    isBlocked = true;

    updateBlocksIndexFrom(col,0);

    int prev_end = 0;
    int added_time = 0;
    QMap <quint64,int> start_ind;
    for (int i=0 ; i < tracks[col].block.size(); i++)
    {
        DrawElement* elm = tracks[col].block[i];
        quint64 start = elm->getStartDrawTime();
        start_ind.insert(start,i);
    }
    int time_bonus = 0;
    int na_siky_zmensh = 0;
    DrawElement *prev_elm = NULL;
    foreach(int index, start_ind)
    {
        DrawElement* elm = tracks[col].block[index];
        quint64 cur_start = elm->getStartDrawTime();
        int diff = cur_start - prev_end;





        if (diff > 0)
        {


            if (prev_elm == NULL)
            {
                if (elm->getTypeId() !=  Element_type::Empty)
                {
                    DrawElement* element = new DrawElement(NULL,NULL);
                    addBlockAt(col,index,element,diff );
                }
                else
                {
                    elm->setStartDraw(prev_end + 1);
                    setBlockTime(col,elm->getBlockIndex(),diff ); //+ prev_elm->getLifeTime()
                }
            }
            else
            {
                if (prev_elm->getTypeId() !=  Element_type::Empty)
                {
                    DrawElement* element = new DrawElement(NULL,NULL);
                    addBlockAt(col,index,element,diff );
                }
                else
                {
                    setBlockTime(col,prev_elm->getBlockIndex(),diff + prev_elm->getLifeTime() );
                }
            }
        }
        else
            if (diff < 0)
            {

                /*if (prev_elm == NULL) // it possible???
                {

                    if (elm->getTypeId() != 5)
                    {
                        DrawElement* element = new DrawElement(NULL,NULL);
                        addBlockAt(col,index,element,diff );
                    }
                    else
                    {
                        elm->setStartDraw(prev_end + 1);
                        setBlockTime(col,elm->getBlockIndex(),diff ); //+ prev_elm->getLifeTime()
                    }
                }
                else*/
                {
                    if (prev_elm->getTypeId() != Element_type::Empty)
                    {
                        /* DrawElement* element = new DrawElement(NULL,NULL);
                        addBlockAt(col,index,element,diff);*/
                        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!      tak ne maye buty" ;
                    }
                    else
                    {
                        setBlockTime(col,prev_elm->getBlockIndex(),diff + prev_elm->getLifeTime());

                        na_siky_zmensh = diff;
                    }
                }
                /* if (na_siky_zmensh < 0)
                {
                    foreach(int inda, start_ind)
                    {
                        if (inda <= index)
                            continue;
                        DrawElement *this_elm = tracks[col].block[inda];
                        if (this_elm->getTypeId() == 5)
                        {
                            int this_time = this_elm->getLifeTime();
                            this_time += na_siky_zmensh;
                            if (this_time < 0)
                            {
                                na_siky_zmensh = this_time;
                                this_time = 0;
                                setBlockTime(col,inda,this_time);
                            }
                            else
                            {
                                setBlockTime(col,inda,this_time);
                                break;
                            }
                        }
                    }
                }*/



            }
        prev_end +=elm->getLifeTime();
        prev_elm = elm;
    }



    recountMaxTrackTime();
    //setBlockTime(col,ind,set_time);
    isBlocked = false;
    return true;
}

void ListControll::setForceResizeBlock(bool value)
{
    force_resize_block = value;
    qDebug() << "void ListControll::setForceResizeBlock " << force_resize_block;
}

bool ListControll::getForceResizeBlock()
{
    return force_resize_block;
}

void ListControll::logForTest()
{
    qDebug() << "HHHHH ______ HHHHHH _____";
}

void ListControll::emitSetBlockPlayTimeUntilFreezeSignal2(int col, int ind, int value)
{
    emit setBlockPlayTimeUntilFreezeSignal2(value);
}


void ListControll::addNewBlock(int col, QString str, DrawElement *element)
{
    if (element == NULL)
    {
        DrawTextElm *dr_text = new DrawTextElm(NULL,NULL);
        element = (DrawElement*) dr_text;
        element->setLifeTime(def_min_block_width);
    }
    else
    {
        quint64 life = element->getLifeTime();
        if(life < def_min_block_width)
        {
            element->setLifeTime(def_min_block_width);
            element->setPlayTimeUntilFreeze(def_min_block_width);

        }
    }
    int last_block_ind = tracks[col].block.size();
    element->setKey(str);





    element->setBlockColumn(col);
    element->setBlockIndex(last_block_ind);
    connect(element, SIGNAL(borderColorChangedSignal(int,int,QString)),
            this, SIGNAL(borderColorChangedSignal(int,int,QString)));
    connect(element, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
    connect(element,SIGNAL(dontUseThisValue()),
            this, SIGNAL(dontUseThisValue()));
    connect(element,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
            this, SIGNAL(setBlockPlayTimeUntilFreezeSignal(int,int,int)));


    /*
    connect(element,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
            this, SLOT(logForTest()));*/


    qDebug() << "ListControll::addNewBlock     last_block_ind = " << last_block_ind;



    if (getBlockIndToAddFromPos(element,scale_pointer_pos,-1,false)) //741
        return;

    tracks[col].block.append(element);
    addEmptyBlockAt(col, tracks[col].block.size() - 1 , 0);

    updateBlocksStartTimesFrom(col,0);
    //tracks[col].addTime(element->getLifeTime());
    tracks[col].updateTime();
    quint64   temp_time = tracks[col].getTime();

    updateMaxTrackTime(temp_time);

    //recountMaxTrackTime();

    calcPointedBlocks();


    element->setUseAnimTime(2);
    quint64 ddd = element->getLifeTime();
    qDebug() << " 121 void ListControll::addNewBlock(   ddd = " << ddd;
}

bool ListControll::addNewBlockFromLibrary(QString str , DrawElement *element)
{
    if (!load_from_file_or_library )
        return false;
    addNewBlockFromLibrary(curent_block.x(),str,element);
    return true;
}

bool ListControll::addNewBlockFromLibrary(int col, QString str , DrawElement *element)
{
    if (col <0 || col > tracks.size()-1)
        return false;
    QString file_name = f_manager.getFilePathName();
    DrawElement * elm =  loadFromFile(col,-1,file_name,false); //new DrawElement(NULL,NULL);//
    if (elm == NULL)
        return false;

    addNewBlock(col,str,elm);
    sendUpdateModel();
    if (element != NULL)
    {
        elm->copy(element);
    }
    else
    {
        elm->setBlockColumn(col);
        elm->setBlockIndex(tracks.size()-1);
        //emit updateSelectedBlock(QPoint(col,elm->getBlockIndex()));
    }

    return true;
}
int ListControll::getBlockSpaceToAddFromPos(int col,int ind)
{
    if (!blockValid(col,ind))
        return -1;
    return spaces_to_add;

}
void ListControll::logBlocksTypes(int col)
{
    /* for (int i = 0; i < tracks[col].block.size(); i++)
    {
        if (tracks[col].block[i] != NULL)
        qDebug() << "col = " << col<< "    Element[" << i << "] type = " << tracks[col].block[i ]->getTypeId() << "  ind = " <<tracks[col].block[i ]->getBlockIndex() ;
    }*/
}

void ListControll::logBlocksDrawElColInd(int col)
{
    for (int i = 0; i < tracks[col].block.size(); i++)
    {
        DrawElement * elm = tracks[col].block[i] ;
        qDebug() << "col = " << elm->getBlockColumn()<< "  ind = " << elm->getBlockIndex()  << " type = " << elm->getTypeId();
    }
}




int ListControll::getBlockIndToAddFromPos(int col,int ind, int pos, int col_dest,bool remove_movable_block )
{
    if (!blockValid(col,ind))
        return -1;
    DrawElement * move_block = tracks[col].block[ind];

    if (remove_movable_block)
        removeBlock(col,ind,false,true,false); // dont delete draw element

    // getBlockIndToAddFromPos(move_block,)

    if (col_dest >= 0)
    {
        col = col_dest;
        qDebug() << "col = col_dest = " << col_dest;
    }

    return getBlockIndToAddFromPos(move_block,pos,col );
}




bool ListControll::getBlockIndToAddFromPos(DrawElement * move_block, int pos, int col_dest , bool reback_block )
{
    int get_ind = -1;

    if (pos < 0)
        pos = 0;

    int col;
    int ind = move_block->getBlockIndex();
    bool rezult = false;

    if (col_dest >= 0)
    {
        col = col_dest;
    }
    else
    {
        col = move_block->getBlockColumn();
    }

    int move_block_start_time = move_block->getStartDrawTime();
    int track_size = tracks[col].block.size();
    int mov_block_time = move_block->getLifeTime();
    // int track_time = tracks[col].getTime() - mov_block_time;
    /* if (ind == tracks[col].block.size() - 1)
        track_time -= tracks[col].block[ind]->getLifeTime();*/


    // return 1;
    //pos_to_append.setY(pos_to_append.y() - 1);
    int track_time = tracks[col].getTime() ;//- mov_block_time;
    spaces_to_add = -1;
    //qDebug() << "FFAAAAAAAAAAAAAAAA    dfghsgs "<< track_size;
    if (pos == 0)
        if (track_size == 0)
        {
            qDebug() << "FFAAAAAAAAAAAAAAAA    dfghsgs";
            DrawElement *empta = new DrawElement(NULL,NULL);
            empta->setLifeTime(0);
            connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                    this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
            tracks[col].block.insert(0 , empta);
            tracks[col].block.insert(1, move_block);
            updateBlocksIndexFrom(col,0);
            empta->setBlockColumn(col);
            //reduceEmptyBlocksFromV2(col,m + 2 ,mov_block_time);
            updateBlocksStartTimesFrom(col,0);
            tracks[col].updateTime();
            recountMaxTrackTime();
            move_block->setBlockColumn(col);

        }
    if (pos > track_time)
    {
        spaces_to_add = pos + mov_block_time - track_time;
        get_ind = tracks[col].block.size();


        tracks[col].block.insert(get_ind   ,move_block);
        move_block->setBlockColumn(col);
        move_block->setBlockIndex(get_ind);
        /* connect(move_block, SIGNAL(borderColorChangedSignal(int,int,QString)),
                    this, SIGNAL(borderColorChangedSignal(int,int,QString)));
            connect(element, SIGNAL(sizeChangedSignal(int,int, int, bool)),
                    this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));*/
        //tracks[col].addTime(mov_block_time);
        addEmptyBlockAt(col,get_ind  ,spaces_to_add - mov_block_time);



        updateBlocksIndexFrom(col,0);
        updateBlocksStartTimesFrom(col,0);
        tracks[col].updateTime();
        recountMaxTrackTime();
        move_block->setBlockColumn(col);
        return true;
    }



    //logBlocksTypes(col);
    //if (false)
    tracks[col].updateTime();
    track_time = tracks[col].getTime();
    for (int m = 0; m < track_size; m++)
        //foreach (DrawElement* elm,tracks[col].block )
    {
        /*  if( elm->getBlockIndex() == ind)
            continue;*/
        DrawElement* elm = tracks[col].block[m];
        if (elm == NULL)
        {
            qDebug() << " if (elm == NULL)         continue";
            continue;
        }
        int start = elm->getStartDrawTime();
        int life = elm->getLifeTime();
        int end = start + life;
        int elm_index = elm->getBlockIndex();


        if (start <= pos && pos <= end ) //  && start + mov_block_time <= end ) //
        {
            if (elm->getTypeId() == Element_type::Empty)
            {
                int new_val = pos - start;
                if (pos + mov_block_time <= end) //влазе в пустоту   +++++++
                {
                    DrawElement *empta = new DrawElement(NULL,NULL);
                    empta->setLifeTime(new_val);
                    connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
                    tracks[col].block.insert(m , empta);
                    tracks[col].block.insert(m + 1, move_block);
                    updateBlocksIndexFrom(col,0);
                    empta->setBlockColumn(col);
                    reduceEmptyBlocksFromV2(col,m + 2 ,mov_block_time + new_val);
                    updateBlocksStartTimesFrom(col,0);
                    tracks[col].updateTime();
                    recountMaxTrackTime();
                    move_block->setBlockColumn(col);
                    return true;
                    break;
                }
                else   // не влазе в пустоту
                {
                    if (force_resize_block ) //двигаєм  ++++++
                    {
                        elm->setLifeTime(new_val);
                        tracks[col].block.insert(m + 1, move_block);
                        DrawElement *empta = new DrawElement(NULL,NULL);
                        empta->setLifeTime(0);
                        connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                                this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
                        tracks[col].block.insert(m + 2 , empta);
                        updateBlocksIndexFrom(col,0);
                        updateBlocksStartTimesFrom(col,0);

                        tracks[col].updateTime();
                        recountMaxTrackTime();
                        move_block->setBlockColumn(col);
                        return true;
                        break;
                    }
                    else // не влазе в пустоту - вертаєм на місце  +++
                    {
                        if (reback_block)
                            getBlockIndToAddFromPos(move_block,move_block_start_time);
                        return false;
                        break;
                    }
                }
            }
            else //nit empty
            {
                //if (append_ind > 0
                int append_ind = pos_to_append.y() ;
                if (col == move_block->getBlockColumn())
                    append_ind--;
                //qDebug() << "KKKKKKKKKKKKKKKKKKK  " << append_ind;
                /*if (force_resize_block ) //двигаєм
                {
                    qDebug() << "KKKKKKKKK         1";
                }
                else*/
                {
                    if (append_ind == elm->getBlockIndex())
                    {
                        DrawElement* prev_el = tracks[col].block[m - 1];
                        if (prev_el->getLifeTime() < mov_block_time) //не взлазе перед блочком
                        {
                            if (!force_resize_block ) //+++++++++++++
                            {
                                qDebug() << "KKKKKKKKK         2";
                                if (reback_block)
                                    getBlockIndToAddFromPos(move_block,move_block_start_time);
                                return false;
                                break;
                            }
                            else //+++++++++++++
                            {
                                DrawElement *empta = new DrawElement(NULL,NULL);
                                empta->setLifeTime(0);
                                connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                                        this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));

                                tracks[col].block.insert(m , move_block);
                                tracks[col].block.insert(m  + 1 , empta);

                                updateBlocksIndexFrom(col,0);

                                reduceEmptyBlocksFromV2(col,m  ,mov_block_time);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                move_block->setBlockColumn(col);
                                empta->setBlockColumn(col);
                                qDebug() << "KKKKKKKKK         22";
                                return true;
                                break;
                            }
                        }
                        else  //++++++++
                        {
                            prev_el->setLifeTime(prev_el->getLifeTime() - mov_block_time);
                            tracks[col].block.insert(m , move_block);
                            DrawElement *empta = new DrawElement(NULL,NULL);
                            empta->setLifeTime(0);
                            connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                                    this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
                            tracks[col].block.insert(m + 1 , empta);
                            updateBlocksIndexFrom(col,0);
                            updateBlocksStartTimesFrom(col,0);
                            tracks[col].updateTime();
                            qDebug() << "KKKKKKKKK         3";
                            move_block->setBlockColumn(col);
                            return true;
                            break;
                        }
                    }
                    else
                    {
                        if (m == track_size - 1 ) //+++++++++++
                        {
                            tracks[col].block.insert(m + 1, move_block);
                            updateBlocksIndexFrom(col,0);
                            updateBlocksStartTimesFrom(col,0);
                            tracks[col].updateTime();
                            qDebug() << "KKKKKKKKK         35";
                            move_block->setBlockColumn(col);
                            return true;
                            break;
                        }
                        else
                        {
                            DrawElement* next = tracks[col].block[m + 1];
                            int next_life_time = next->getLifeTime();
                            if (next_life_time < mov_block_time) //не взлазе after блочкa
                            {
                                if (!force_resize_block )  //++++++++++++++++++
                                {
                                    qDebug() << "KKKKKKKKK         20";
                                    if (reback_block)
                                        getBlockIndToAddFromPos(move_block,move_block_start_time);
                                    return false;
                                    break;
                                }
                                else
                                {
                                    DrawElement *empta = new DrawElement(NULL,NULL);
                                    empta->setLifeTime(0);
                                    connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                                            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));

                                    tracks[col].block.insert(m + 1 , move_block);
                                    tracks[col].block.insert(m  + 1 , empta);

                                    next->setLifeTime(0);
                                    updateBlocksIndexFrom(col,0);
                                    reduceEmptyBlocksFromV2(col,m  ,mov_block_time - next_life_time);
                                    updateBlocksStartTimesFrom(col,0);

                                    tracks[col].updateTime();
                                    move_block->setBlockColumn(col);
                                    empta->setBlockColumn(col);
                                    qDebug() << "KKKKKKKKK         22";
                                    return true;
                                    break;
                                }
                            }
                            else  // +++++++++
                            {
                                next->setLifeTime(next->getLifeTime() - mov_block_time);
                                DrawElement *empta = new DrawElement(NULL,NULL);
                                empta->setLifeTime(0);
                                connect(empta, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                                        this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
                                tracks[col].block.insert(m  + 1 , empta);
                                tracks[col].block.insert(m + 2, move_block);
                                updateBlocksIndexFrom(col,0);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                qDebug() << "KKKKKKKKK         30";
                                move_block->setBlockColumn(col);
                                empta->setBlockColumn(col);
                                return true;
                                break;
                            }
                        }
                    }

                }

            }

        }
    }

    return  get_ind;
}

int ListControll::reduceEmptyBlocksFrom(int col, int ind, int value)
{
    if (value <=0)
        return 0;
    if (ind < 0)
        ind = 0;\
    if (col < 0)
        col = 0;

    for (int i = ind; i < tracks[col].block.size(); i++)
    {
        DrawElement *elm = tracks[col].block[i];
        if (elm != NULL)
            if (elm->getTypeId()  == Element_type::Empty)
            {
                int time = elm->getLifeTime();
                //time -=value;
                if (time <= value)
                {
                    // tracks[col].addTime(-time);
                    value -= time;
                    tracks[col].block.removeAt(i);
                    delete elm;
                    i--;
                }
                else  // time > value
                {
                    time -= value;
                    elm->setLifeTime(time);
                    //tracks[col].addTime(-value);
                    return time;
                }
            }
    }
    return -1;
}

int ListControll::reduceEmptyBlocksFromV2(int col, int ind, int value)
{
    /*if (value <=0)
        return -1;*/
    if (ind < 0)
        return -1;\
    if (col < 0)
        return -1;
    block_to_del.clear();
    for (int k = ind; k </* ind +1;*/ tracks[col].block.size();      k++)
    {
        DrawElement *k_elm = tracks[col].block[k];
        if (k_elm == NULL)
            continue;
        if (k_elm->getTypeId() != Element_type::Empty)
            continue;
        int f_time = k_elm->getLifeTime();
        int new_time = f_time - value;

        //force_resize_block
        if (new_time < 0)
        {   //this code i need later!!!
            value = -new_time;
            new_time = 0;
            k_elm->setLifeTime(new_time,true)    ;
            block_to_del.append(k);
            //qDebug() << "99999999999999999999999999";

        }
        else
        {
            //value -= new_time;
            k_elm->setLifeTime(new_time,true)    ;
            value -= new_time - f_time;
            //qDebug() << "8888888888888888888888888888";
            break;
        }

        if (value == 0)
            break;

    }

    return value;
}

DrawElement* ListControll::getBlockFromBuffer()
{
    DrawElement *temp_el ;
    cloneBlock(block_in_buffer,temp_el);
    return temp_el;
}

void ListControll::addBlockWithSpaceAt(int col, int ind,int space,  DrawElement *element, int life_time ,bool need_balance)
{
    // int track_size = tracks[col].block.size();
    DrawElement * empt = new DrawElement(NULL,NULL);
    empt->setLifeTime(space);
    addBlockAt(col,  ind  , empt);
    element->setLifeTime(life_time);
    addBlockAt( col,  ind + 1 ,  element,  -1 , need_balance);
}

void ListControll::addBlockWithSpaceFromBufferAt(int col, int ind,int space,   int life_time ,bool need_balance)
{
    if (block_in_buffer = NULL)
    {
        return;
    }
    addBlockWithSpaceAt( col,  ind, space,  block_in_buffer,  life_time , need_balance);
}

void ListControll::addEmptyBlockAt(int col, int ind, int life_time, bool need_balance )
{
    DrawElement * elm = new DrawElement(NULL,NULL);   //
    elm->setLifeTime(life_time);
    elm->setKey(QString::number(ind));
    addBlockAt(col,ind,elm,life_time,need_balance);
    qDebug() << "AAAAAAAAA   addEmptyBlockAt";
}

void ListControll::addBlockAt(int col, int ind,  DrawElement *element, int life_time ,bool need_balance)
{
    //if (!blockValid(col,ind))       return;

    if (element == NULL)
    {
        DrawTextElm *dr_text = new DrawTextElm(NULL,NULL);
        element = (DrawElement*) dr_text;
        element->setKey(QString("block"+ QString::number(qrand())));
        if (life_time < def_min_block_width)
            life_time = def_min_block_width;
        element->setLifeTime(life_time);
    }
    else
    {
        if (element->getTypeId() == Element_type::Empty)
        {
            if (ind > 0 )
            {
                // if ( ind < tracks[col].block.size())
                {
                    DrawElement *prev = tracks[col].block[ind - 1];
                    if (prev != NULL)
                        if (prev->getTypeId() == Element_type::Empty)
                        {
                            int elm_time = element->getLifeTime();
                            int new_time = prev->getLifeTime() + elm_time;
                            prev->setLifeTime(new_time);

                            //tracks[col].addTime(elm_time);
                            updateBlocksStartTimesFrom(col,ind );
                            tracks[col].updateTime();
                            delete element;
                            quint64 temp_time = tracks[col].getTime();
                            updateMaxTrackTime(temp_time);
                            calcPointedBlocks();
                            return;
                        }
                }
            }

        }
    }



    tracks[col].block.insert(ind,element);


    if (element->getTypeId() != Element_type::Empty)
    {

        if(element->getLifeTime() < def_min_block_width)
            element->setLifeTime(def_min_block_width);
    }

    //int last_block_ind = tracks[col].block.size();
    connect(element, SIGNAL(borderColorChangedSignal(int,int,QString)),
            this, SIGNAL(borderColorChangedSignal(int,int,QString)));
    connect(element, SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
    connect(element,SIGNAL(dontUseThisValue()),
            this, SIGNAL(dontUseThisValue()));
    connect(element,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
            this, SIGNAL(setBlockPlayTimeUntilFreezeSignal(int,int,int)));
    /*
    connect(element,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
            this, SLOT(logForTest()));*/

    element->setBlockColumn(col);
    element->setBlockIndex(ind);


    // tracks[col].block.append(element);


    if(need_balance && element->getGroupWichElBelong() == NULL)
        balanceBlocksIfIsGroups(col,ind + 1);

    updateBlocksIndexFrom(col,0);
    updateBlocksStartTimesFrom(col,0 );



    //tracks[col].addTime(element->getLifeTime());
    tracks[col].updateTime();
    long temp_time = tracks[col].getTime();
    this->updateMaxTrackTime(temp_time);
    calcPointedBlocks();

    qDebug() << "AAAAAAAAA  time = "  << tracks[col].getTime();
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


    updateMaxTrackTime(temp_traclwidth);
    calcPointedBlocks();
}

DrawElement* ListControll::loadFromFile( QString path)
{
    /*  DrawElement* current = tracks[curent_block.x()].block[curent_block.y()];

    delete current;
    current =  \
            */
    return loadFromFile(curent_block.x(),  curent_block.y(),  path);
}

void ListControll::loadFromFileVoid( QString path)
{
    loadFromFile(selectedBlockPoint.x(),  selectedBlockPoint.y(),  path);
    // loadFromFile(curent_block.x(),  curent_block.y(),  path);
}



DrawElement* ListControll::loadFromFile(int col, int ind, QString path,bool emit_update)
{
    if (emit_update)
        if ( load_from_file_or_library )
            return NULL;
    qDebug() << "loadFromFile(): col = " << col << " IND = " << ind;
    setBlocked(true);
    qDebug() << "loadFromFile() 2";
    qApp->processEvents();
    qDebug() << "loadFromFile() 3";
    QString open;
    if ( path == "")
        open =  QFileDialog::getOpenFileName(0, QString(), QString(), QString(), 0, QFileDialog::DontUseNativeDialog);
    else
        open = path;
    qDebug() << "loadFromFile() 4 " << open;

    DrawElement *elm = GenerationDrawElement(open,NULL,NULL);
    if(elm == NULL)
    {
        qDebug() << "loadFromFile(): elm == NULL";
        //QMessageBox::warning(0, "Error",tr("Opening video failed"));
        return NULL;
    }
    qDebug() << "loadFromFile() 5321 " << elm->getLifeTime();


    if (elm->getTypeId() == Element_type::Image && p_drawWidget != NULL) //123_123
    {
        QSize image_size = QPixmap(open).size();
        elm->setSize(p_drawWidget->imageLoadedPictureSizeSlot(image_size));

    }
    qDebug() << "loadFromFile() 6";


    if (emit_update)
    {
        qDebug() << "loadFromFile() 7";
        if (!blockValid(col,ind))
        {
            delete elm;
            return NULL;
        }
        DrawElement* temp = tracks[col].block[ind]; ///////!!!!!!!!!!!!!!!!!!!!
        int new_life_time = elm->getLifeTime();
        qDebug() << "loadFromFile() 8";
        //elm->copy(temp);
        Element_type type = elm->getTypeId();
        if( type != Element_type::Audio && type != Element_type::Video )
            elm->setLifeTime(temp->getLifeTime());
        elm->setStartDraw(temp->getStartDrawTime());
        elm->setZ(col);
        elm->setBlockColumn(col);
        elm->setBlockIndex(ind);
        qDebug() << "loadFromFile() 9";

        //elm->setParent(temp->getParent());
        // elm->setGroupWichElBelong(temp->getGroupWichElBelong());
        //  elm->setDrawWidget(temp->getDrawWidget());

        tracks[col].block[ind] = elm;
        delete temp;
        qDebug() << "loadFromFile() 10";
        //zaloop
        /*      if(life_time == 1000)
            setBlockTime(col, ind, new_life_time);
*/
        //  tracks[col].block[ind] = elm;

        updateBlocksStartTimesFrom(col,0);
        calcPointedBlocks();
        tracks[col].updateTime();
        quint64 time = tracks[col].getTime();
        updateMaxTrackTime(time);
        qDebug() << "loadFromFile() 11";
    }

    qDebug() << "loadFromFile() 12";
    connect(elm,SIGNAL(borderColorChangedSignal(int,int,QString)),
            this,SIGNAL(borderColorChangedSignal(int,int,QString)));
    qDebug() << "LIFE_TIME  2";
    connect(elm,SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
    connect(elm,SIGNAL(dontUseThisValue()),
            this, SIGNAL(dontUseThisValue()));
    connect(elm,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
            this, SIGNAL(setBlockPlayTimeUntilFreezeSignal(int,int,int)));

    elm->setPlayTimeUntilFreeze(elm->getPlayTimeUntilFreeze());
    qDebug() << "LIFE_TIME  3";
    QFileInfo file_info(open);

    QString file_name = file_info.fileName();
    elm->setKey(file_name);
    qDebug() << "LIFE_TIME  4";
    if (emit_update)
    {
        qDebug() << "ListControll::loadFromFile    emit updateSelectedBlock     ";
        //emit updateSelectedBlock(selectedBlockPoint);
        sendUpdateModel();
    }


    setBlocked(false);

    emit loadTextFileSignal();

    return elm;
}

bool ListControll::updateMaxTrackTime(quint64 temp_time)
{
    if (maxTrackTime < temp_time)
    {
        maxTrackTime = temp_time;
        emit maxTrackTimeChanged(maxTrackTime);
    }
}

int ListControll::lastNotEmptyBlockIndexBeginFrom(int col, int ind )
{
    if (!blockValid(col,ind))
        return -1;
    int rez = -2;
    for (int i=ind ; i < tracks[col].block.size(); i++)
    {
        if (tracks[col].block[i]->getTypeId() ==5)
            return rez;
        else
            rez = i;
    }
    return rez;
}

bool ListControll::removeLastBlock(int col)
{
    return removeBlock(col,tracks[col].block.size() - 1,false);
}

bool ListControll::removeLastTrack()
{
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
            emit maxTrackTimeChanged(maxTrackTime);
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
    removeRectangle();

    isBlocked = true;
    if (tracks.size()>col)
    {
        quint64 lastColTime = tracks[col].getTime();
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

void  ListControll::moveBlockFromTo(int col0,int ind0, int ind1)  //0-0-0-0-0-0-
{
    qDebug() << " void  ListControll::moveBlockFromTo(int col0,int ind0, int ind1) " << ind0 << " " << ind1;
    if (!blockValid(col0,ind0))
        return ;
    if  (!blockValid(col0,ind1))
        return ;

    if (ind0 == ind1)
    {
        qDebug() << "if (ind0 = ind1)";
        return;
    }

    DrawElement *element = tracks[col0].block[ind0];

    int pos0, pos1;
    pos0 = ind0;
    pos1 = ind1;

    if (ind0 > ind1)
    {
        int temp = pos0;
        pos0 = pos1;
        pos1 = temp;


        DrawElement *prev_el = tracks[col0].block[ind1];
        foreach(DrawElement * elo,tracks[col0].block )
        {
            qDebug() << "DDDDDDDDDDDD       "<< elo->getTypeId();
        }

        int prev_el_type = prev_el->getTypeId();
        if (prev_el_type == 5)
        {
            int set_time = prev_el->getLifeTime() - element->getLifeTime();
            if (set_time < 0)
                set_time = 0;

            prev_el->setLifeTime(set_time);
        }
    }
    else
    {
        int prev_el_ind = ind0-1;
        if (prev_el_ind >=0)
        {
            DrawElement *prev_el = tracks[col0].block[prev_el_ind];
            if (prev_el->getTypeId() == 5)
            {
                DrawElement *next_el = tracks[col0].block[ind0 + 1];
                if (next_el->getTypeId() == 5)
                {
                    tracks[col0].block.removeAt(ind0 + 1);
                    prev_el->setLifeTime(prev_el->getLifeTime() + next_el->getLifeTime());
                    delete next_el;
                }
            }
        }

    }



    if (pos0 > 0 && ind1 == element->getBlockIndex())
    {
        //  qDebug() << "DAAAAAAAAAAAAAAAAA 111111111111111111";
        DrawElement* prev_elm = tracks[col0].block[pos0 -1];
        if (prev_elm->getTypeId() == 5)
        {
            setBlockTime(col0,pos0 - 1, prev_elm->getLifeTime() + element->getLifeTime());
        }
        DrawElement* next_elm = tracks[col0].block[pos0 + 1];
        if (next_elm->getTypeId() == 5)
        {
            setBlockTime(col0,pos0 + 1, next_elm->getLifeTime() - element->getLifeTime());
        }
    }
    if (pos1 < tracks[col0].block.size() - 2)
    {
        // qDebug() << "DAAAAAAAAAAAAAAAAA 222222222222222222222222";
        DrawElement* prev_elm = tracks[col0].block[pos1 -1];
        if (prev_elm->getTypeId() == 5)
        {
            setBlockTime(col0,pos1 - 1, prev_elm->getLifeTime() + element->getLifeTime());
        }
        DrawElement* next_elm = tracks[col0].block[pos1 + 1];
        if (next_elm->getTypeId() == 5)
        {
            setBlockTime(col0,pos1 + 1, next_elm->getLifeTime() - element->getLifeTime());
        }
    }





    tracks[col0].block.removeAt(ind0);
    balanceBlocksIfIsGroups(col0,ind0,false);
    tracks[col0].block.insert(ind1,element);








    balanceBlocksIfIsGroups(col0,ind1,false);




    updateBlocksIndexFrom(col0,0);
    updateBlocksStartTimesFrom(col0,0);


    DrawElement *last =  tracks[col0].block.last();
    if (last->getTypeId() == 5)
    {
        removeBlock(col0,last->getBlockIndex());
    }




}

void  ListControll::moveBlockFromTo(int col0,int ind0,int col1, int ind1) //not used now and able to crash
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

    updateBlocksIndexFrom(col0,0);
    updateBlocksStartTimesFrom(col0,0);
    updateBlocksIndexFrom(col1,0);
    updateBlocksStartTimesFrom(col1,0);

    balanceBlocksIfIsGroups(col0,ind0);

}


void ListControll::cloneBlock(DrawElement *origin, DrawElement *clone)
{
    if(origin == clone)
        return;
    setBlocked(true);
    QBuffer buff;
    buff.open(QBuffer::ReadWrite);
    origin->save(&buff, NULL);
    QPoint p = QPoint(clone->getBlockColumn(), clone->getBlockIndex());
    //tracks[p.x()].addTime(origin->getLifeTime() - clone->getLifeTime());
    tracks[p.x()].updateTime();
    if(clone != NULL)
        delete clone;
    buff.seek(0);
    clone = loadDrawElement(&buff, VERSION);

    clone->setDrawWidget(origin->getDrawWidget());

    clone->setBlockColumn(p.x());
    clone->setBlockIndex(p.y());

    tracks[p.x()].block[p.y()] = clone;


    calcPointedBlocks();
    recountMaxTrackTime();
    updateBlocksStartTimesFrom(p.x(), 0);
    sendUpdateModel();
    setBlocked(false);
}


void ListControll::setBlocks(int col,const QList <DrawElement *> &value)
{
    tracks[col].clear();
    tracks[col].block = value;
}

void ListControll::deleteBlockToDel(int col)
{
    int siz = block_to_del.size();
    int inda = block_to_del[0];
    for (int i=0; i < siz; i++ )
    {
        int ind = block_to_del[i];
        delete tracks[col].block[ind];
        tracks[col].block.removeAt(ind);
    }
    if (siz > 0)
    {
        updateBlocksStartTimesFrom(col,0);
        updateBlocksIndexFrom(col,0);
    }
    tracks[col].updateTime();
    block_to_del.clear();
}

bool ListControll::setBlockTimeBlockBalance(int col, int ind, int value, bool resize_next_empty)
{
    if(!blockValid(col,ind))
        return false;
    DrawElement *elm =  tracks[col].block[ind];

    int dif_time = elm->getLifeTime();
    setBlockTime( col,  ind, value,  resize_next_empty);
    dif_time = elm->getLifeTime() - dif_time;
    return false;



    tracks[0].block[0]->setLifeTime(tracks[0].block[0]->getLifeTime() + dif_time,true,true);
    return false;

    Group* f_group = NULL;
    for (int i = i + 1;  i < tracks[col].block.size(); i++)
    {
        Group* temp_group = tracks[col].block[i]->getGroupWichElBelong();
        if ( temp_group != NULL)
        {
            f_group = temp_group;
            break;
        }
    }
    if (f_group == NULL || dif_time == 0)
        return false;
    qDebug() << "setBlockTimeBlockBalance    dif_time = " << dif_time;
    if (dif_time > 0)
        foreach(DrawElement * f_elm, f_group->getFirst())
        {
            int col_p = f_elm->getBlockColumn();
            if (col_p == col)
                continue;
            int ind_p = f_elm->getBlockIndex();
            DrawElement *prev = tracks[col_p].block[ind_p - 1];
            if (prev != NULL)
            {
                if (prev->getTypeId() == Element_type::Empty)
                {
                    prev->setLifeTime(prev->getLifeTime(),true);
                }
                else
                {
                    DrawElement *rigth_insert = new DrawElement(NULL,NULL);
                    rigth_insert->setLifeTime(dif_time);
                    tracks[col_p].block.insert(ind_p, rigth_insert);
                }
            }
        }
    return true;


}



int ListControll::setBlockTime(int col, int i,int value, bool resize_next_empty, bool use_value)
{
    if(!blockValid(col,i))
        return -1;
    //qDebug() << "void ListControll::setBlockTime(int col, int i,int value) = " << value;
    DrawElement *elm =  tracks[col].block[i];

    if (elm == NULL)
        return -1;

    if (elm->getTypeId() != Element_type::Empty)
    {
        if(value <= def_min_block_width)
        {
            value = def_min_block_width;
        }
    }
    else
        if (value < 0)
        {
            value = 0;
        }

    int cur_time___ = elm->getLifeTime();
    if ( value == cur_time___ )
        return -1;

    int adding_time = value - cur_time___;
    qDebug() << "   force_resize_block = " << force_resize_block;
    if (!force_resize_block)
    {
        if (i < tracks[col].block.size() - 1)
        {
            DrawElement *next = tracks[col].block[i+1];
            int next_time = next->getLifeTime();
            if (next->getTypeId() == Element_type::Empty && adding_time > 0)
            {
                if (next_time == 0 )
                    return -1;
                else
                    if (next_time < adding_time)
                    {

                        adding_time = next_time;
                        value = cur_time___ + adding_time;
                    }
            }
        }
    }

    if (resize_next_empty  )

        adding_time = reduceEmptyBlocksFromV2(col,i+1,adding_time);
    /*{
        block_to_del.clear();
        for (int k = i + 1; k <  i + 2; //tracks[col].block.size();
             k++)
        {
            DrawElement *k_elm = tracks[col].block[k];
            if (k_elm == NULL)
                continue;
            if (k_elm->getTypeId() != Element_type::Empty)
                continue;
            int new_time = k_elm->getLifeTime() - adding_time;
            if (new_time < 0)
            {
                adding_time = -new_time;
                new_time = 0;
                block_to_del.append(k);
                ///reduceEmptyBlocksFrom(col,k+1,)
                 qDebug() << "88888888888888888888888888888888888                     99999999999999990000000000000000000";
            }
            else
            {
                adding_time -= new_time;
                k_elm->setLifeTime(new_time,true)    ;//,true);
                qDebug() << "9999999999999900000000000000000000000000000                     99999999999999990000000000000000000";
            }
            if (adding_time == 0)
                break;

        }

    }*/
    if (adding_time < 0)
    {
        // return;
        //     tracks[col].addTime(adding_time);
    }
    else
        if (adding_time == 0)
        {
            //updateBlocksIndexFrom(col,i);
        }


    /*if ( tracks[col].block[i]->getGroupWichElBelong() == NULL)
        balanceBlocksIfIsGroups(col,i);*/

    // tracks[col].addTime(value - elm->getLifeTime());
    elm->setLifeTime(value,false,true, use_value);

    updateBlocksStartTimesFrom(col,i+1);
    tracks[col].updateTime();
    recountMaxTrackTime();

    qDebug() << "HHHHHHHHHHH  " << elm->getPlayTimeUntilFreeze();
    blockTimeSignel2(value);
    return value;

}

void ListControll::setBlockTimeWithUpdate(int col, int i, quint64 value, bool visual)
{
    /* qDebug() << "void ListControll::setBlockTimeWithUpdate(int col = " << col << " ind = "<<  i
             <<"value = "<< value;*/
    //setBlockTime(col, i, value);
    // if(visual)
    emit blockTimeSignel(col, i, value);
}


bool ListControll::balanceBlocksIfIsGroups(int col0, int ind0 , bool calc_time_change)
{
    /*for(int i = 0; i < tracks.size(); i++)
        for(int j = 0; j < tracks[i].block.size(); j++)
        {
            checkBlockValidGroup(tracks[i].block[j]);
        }*/
    /* if (!blockValid(col0,ind0))
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
                if(elm->getBlockColumn() == col0)
                {
                    DrawElement *deltaElm = new DrawElement();
                   // deltaElm->setLifeTime(-delta);
                    qDebug() << "UUUUUUUUUUUUUUU delta = "<< delta;
                    addBlockAt(col0, ind0 + 1, deltaElm, -delta,false);
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
                if(elm->getBlockColumn() != col0)
                {
                    //DrawElement *deltaElm = new DrawElement();
                    int cur_col = elm->getBlockColumn();
                    if (temp_col == cur_col)
                        continue;
                    temp_col = cur_col;
                    qDebug() << "UUUUUUUUUUUUUUU delta = "<< delta;
                    addBlockAt(cur_col, elm->getBlockIndex(), NULL, delta,false);

                }
            }
             updateModel();
            break;

        }
    }*/
    return false;
}


QPoint ListControll::getCurentBlock()
{
    return curent_block;
}
void ListControll::setCurentBlock (QPoint value)
{
    curent_block = value;
}

void ListControll::setCurentBlock (int col, int ind)
{
    qDebug() << "void ListControll::setCurentBlock (int col, int ind)";
    setCurentBlock(QPoint(col,ind));
}

bool ListControll::checkBlockValidGroup(DrawElement *elm)
{
    /* if(elm->getGroupWichElBelong() != NULL)
    {
        Group *groupTemp = elm->getGroupWichElBelong();
        if(!groupTemp->isGroupValid())
        {
            groupTemp->deInitGroupBlocks();
            delete groupTemp;
            removeRectangle();
        }
    }*/

}

void ListControll::updateBlocksStartTimesFrom(int col0,int ind0, bool withGroup)
{
    if (!blockValid(col0,ind0))
        return;

    if (ind0 == 0)
    {
        DrawElement* t_elm =  tracks[col0].block[ind0];
        if (t_elm != NULL)
            t_elm->setStartDraw(0);
        ind0++;
    }
    Group *updatedGroup = NULL;
    quint64 delta =  tracks[col0].calcTimeChange();

    for (int i=ind0; i < tracks[col0].block.size(); i++)
    {

        DrawElement *temp_el = tracks[col0].block[i - 1];
        int draw_time = temp_el->getStartDrawTime()  + temp_el->getLifeTime();
        tracks[col0].block[i]->setStartDraw(draw_time);
    }

    if(false)
        for (int i=ind0; i < tracks[col0].block.size(); i++)
        {
            //if(updatedGroup != tracks[col0].block[i]->getGroupWichElBelong() && tracks[col0].block[i]->getGroupWichElBelong() != NULL && !tracks[col0].block[i]->getGroupWichElBelong()->isGroupValid())
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

int ListControll::setBlockStartTimeGroup(int col,int ind,int value )
{
    if (!blockValid(col,ind))
        return -1;
    DrawElement * elm = tracks[col].block[ind];
    if (elm == NULL)
        return -1;
    Group * group = elm->getGroupWichElBelong();
    if (group == NULL)
        return -1;
    int elm_start = elm->getStartDrawTime();
    value -=elm_start;
    if (value == 0)
        return elm_start;

    addBlockStartTimeGroup(col,ind,value);

}

int ListControll::setBlockTimeLeft(int col,int ind,quint64 value )
{
    if (!blockValid(col,ind))
        return -1;
    DrawElement * elm = tracks[col].block[ind];
    if (elm == NULL)
        return -1;
    quint64 life = elm->getLifeTime(); // 1000
    quint64 start = elm->getStartDrawTime(); //5000
    quint64 end = life + start;
    if (value == start)
        return life;

    if (value > end)
        value = end;

    int zdvig ;
    if (start < value)
        zdvig = value - start;
    else
    {
        zdvig = start - value;
        zdvig *= -1;
    }
    DrawElement *prev = NULL;
    quint64 set_life_time ;
    quint64 set_start;
    if (ind > 0)
    {
        prev = tracks[col].block[ind - 1];
        if (prev == NULL)
            return life;
        quint64 prev_life = prev->getLifeTime();
        quint64 prev_start = prev->getStartDrawTime() ;

        quint64 set_prev_life;

        if (zdvig < 0)
        {

            if (-zdvig > prev_life)
            {
                set_prev_life = 0;
                value = prev_start;
                zdvig = -prev_life;
            }
            else
            {
                set_prev_life = prev_life + zdvig;
            }
            set_life_time = life - zdvig;
            set_start = start + zdvig;
        }
        else
        {
            set_start = value;
            quint64 able_start = end - minBlockTime;
            if (set_start > able_start)
            {
                set_start = able_start;
                set_life_time =  minBlockTime;
                set_prev_life = prev_life + life - minBlockTime;
                qDebug() << "__________________________shit";
            }
            else
            {
                set_life_time = life - zdvig;
                set_prev_life = prev_life + zdvig;
            }

        }

        prev->setLifeTime(set_prev_life,true );
        elm->setLifeTime(set_life_time,true);
        elm->setStartDraw(set_start);

    }
    return set_life_time;

}

int ListControll::addBlockStartTime(int col,int ind,int value )
{
    if (!blockValid(col,ind))
        return -1;
    DrawElement * elm = tracks[col].block[ind];
    if (elm == NULL)
        return -1;

    if (ind > 0)
    {
        if (!force_resize_block)
        {
            quint64 elm_start = elm->getStartDrawTime();
            quint64 end = elm_start + elm->getLifeTime();
            if (value > 0)
            {
                if (ind < tracks[col].block.size() - 1)
                {
                    DrawElement *next = tracks[col].block[ind + 1];
                    quint64 next_start = next->getStartDrawTime() + next->getLifeTime();
                    // int able_zdvig =  next_start  -  end;
                    int able_zdvig = next_start - end;
                    if (value > able_zdvig)
                        value = able_zdvig;
                    if (value < 0)
                        value = 0;
                }

            }
            else
            {
                if (ind > 0)
                {
                    DrawElement *prev = tracks[col].block[ind - 1];
                    quint64 prev_end = prev->getStartDrawTime() ;//+ prev->getLifeTime();
                    int diff  = prev_end - elm_start ; //how mush get left a able to do

                    if (diff > value )
                    {
                        value = diff;
                    }
                    if (value > 0)
                        value = 0;
                }
            }
        }
        DrawElement *prev = tracks[col].block[ind - 1];
        quint64 prev_life = prev->getLifeTime();
        quint64 set_time = 0;// prev->getLifeTime() + value;
        if (value >0 )
            set_time = prev_life + value;
        else
        {
            quint64 abs_value = (quint64) abs(value);
            if (prev_life > abs_value )    //prev_life - value > 0
            {
                set_time = prev_life - abs_value;
            }
            else
            {
                value = -prev_life;
            }
        }

        prev->setLifeTime(set_time, true);
        reduceEmptyBlocksFromV2(col,ind + 1, value);
        updateBlocksStartTimesFrom(col,ind);
        this->emitBlockEditedSignal();

    }


    tracks[col].updateTime();
    return value;

}

int ListControll::addBlockStartTimeGroup(int col,int ind,int value ) //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
{
    if (!blockValid(col,ind))
        return -1;
    DrawElement * elm = tracks[col].block[ind];
    if (elm == NULL)
        return -1;
    Group * group = elm->getGroupWichElBelong();
    if (group == NULL)
        return -1;

    QMap < int, BlockType > columns =  group->getMembers();

    int elm_start = elm->getStartDrawTime();
    //value -=elm_start;
    if (value == 0)
        return elm_start;

    int min_zdvig = value;


    //value+= elm_start;
    // int zdvig = value -  elm_start;
    /* foreach(BlockType btype, columns)
                foreach (DrawElement * draw_el, btype)*/
    foreach(BlockType btype, columns)
    {
        int lastk =  btype.lastKey();
        int fistk =  btype.firstKey();
        for (int i = lastk; i >= fistk; i--)
        {
            DrawElement * draw_el = btype.take(i);
            if(draw_el != NULL)
            {
                int el_ind = draw_el->getBlockIndex();
                int el_col = draw_el->getBlockColumn();
                int track_size = tracks[el_col].block.size();
                int start = draw_el->getStartDrawTime();
                int life = draw_el->getLifeTime();
                int end = start + life;

                bool is_next_in_this_group = false;
                for (int k = fistk + 1; k <= lastk; k++)
                {
                    DrawElement * drawl = btype.take(k);
                    if(drawl != NULL)
                    {
                        Group* t_group = drawl->getGroupWichElBelong();
                        if (t_group == group)
                        {
                            is_next_in_this_group = true;
                            break;
                        }
                    }
                }

                bool is_prev_in_this_group = false;
                for (int k = el_ind - 1; k >= fistk; k++)
                {
                    if (getBlockGroup(el_col,k) == group)
                    {
                        is_prev_in_this_group = true;
                        break;
                    }
                }

                if (is_next_in_this_group)
                    break;

                //if (!is_next_in_this_group)
                bool if_1 = is_prev_in_this_group && value < 0;
                bool if_2  = is_next_in_this_group && value > 0;
                {
                    if (!force_resize_block || value < 0)
                    {
                        if (value > 0)
                        {
                            if (el_ind < track_size - 1)
                            {
                                DrawElement *next = tracks[el_col].block[el_ind + 1];

                                /* if (next->getTypeId() == Element_type::Empty )
                            {
                                if (el_ind < track_size - 2)
                                {
                                    DrawElement * next_p = tracks[el_col].block[el_ind + 2];
                                    if (next_p->getGroupWichElBelong() != group)
                                    {
                                        next = next_p;
                                    }
                                }
                            }*/
                                int next_start = next->getStartDrawTime() + next->getLifeTime(); //cuz nex block empty

                                int able_zdvig = next->getLifeTime();// next_start - end;
                                // qDebug()<< "@@@@@@@@@@@@@@@@@@@@@@  able_zdvig = " << able_zdvig;

                                if (min_zdvig > able_zdvig)
                                    min_zdvig = able_zdvig;
                                if (min_zdvig < 0)
                                    min_zdvig = 0;


                            }
                        }
                        else
                        {
                            if (el_ind > 0)
                            {
                                DrawElement *prev = tracks[el_col].block[el_ind - 1];

                                /*if (prev->getTypeId() == Element_type::Empty )
                                {
                                    if (el_ind > 1)
                                    {
                                        prev = tracks[el_col].block[el_ind - 2];
                                    }
                                }*/
                                //int prev_end = prev->getStartDrawTime() ;//+ prev->getLifeTime();
                                int diff =  -prev->getLifeTime();    //prev_end - elm_start ; //how mush get left a able to do


                                if (diff > min_zdvig )
                                {
                                    min_zdvig = diff;
                                }
                                if (min_zdvig > 0)
                                    min_zdvig = 0;

                            }
                        }
                    }
                }
            }
        }
    }


    // qDebug() << "@@@@@@@@@@@@@@@   min_zdvig = " << min_zdvig;

    /*foreach(BlockType btype, columns)
                foreach (DrawElement * draw_el, btype)*/
    foreach(BlockType btype, columns)
    {
        int lastk =  btype.lastKey();
        int fistk =  btype.firstKey();
        for (int i = lastk; i >= fistk; i--)
        {
            DrawElement * draw_el = btype.take(i);

            if(draw_el != NULL)
            {
                //DrawElement * draw_el = elm;
                draw_el->setStartDraw(draw_el->getStartDrawTime() + min_zdvig);
                int el_ind = draw_el->getBlockIndex();
                int el_col = draw_el->getBlockColumn();
                //if (min_zdvig > 0)
                {
                    if (ind > 0)
                    {
                        DrawElement *prev = tracks[el_col].block[el_ind - 1];
                        int set_time = prev->getLifeTime() + min_zdvig;
                        prev->setLifeTime(set_time, true);
                        qDebug() << "@@@@@@@@@@@@@@@   set_time = " << set_time;

                        reduceEmptyBlocksFromV2(el_col,el_ind + 1, min_zdvig);
                        updateBlocksStartTimesFrom(el_col,ind);
                        // updateBlocksIndexFrom(el_col,0);
                        tracks[el_col].updateTime();

                    }
                    /* else
                            if (ind < tracks[el_col].block.size() - 1)
                            {
                                DrawElement *next = tracks[el_col].block[el_ind + 1];
                                next->setLifeTime(next->getLifeTime() + min_zdvig, true);
                            }*/
                }
                /*if (force_resize_block)
                        {
                            tracks[el_col].updateTime();
                        }*/
            }

        }
    }
    recountMaxTrackTime(); //8899
    emit maxTrackSizeChange();
}


quint64 ListControll::setBlockStartTime(DrawElement * elm,quint64 value, bool move_group )
{
    /* if (value < 0)
            {
                value = 0;
            }*/
    return elm->setStartDraw(value);


}

quint64 ListControll::setBlockStartTime(int col, int i,quint64 value, bool move_group )
{

    qDebug() << "void ListControll::setBlockStartTime(int col, int i,int value)";


    if (!blockValid(col,i))
        return -1;
    /*if (value < 0)
            {
                value = 0;
            }*/

    DrawElement * elm = tracks[col].block[i];

    setBlockStartTime( elm, value,  move_group );

    return value;


    //qDebug() << "value = " << value;
    /*
            if(testIndexs(col, i))
                tracks[col].block[i]->setStartDraw(value);*/

}

quint64 ListControll::getBlockStartTime(int col, int i)
{
    if(!testIndexs(col, i))
        return -1;
    return tracks[col].block[i]->getStartDrawTime();
}

Group * ListControll::getBlockGroup(int col, int ind)
{
    if(!blockValid(col, ind))
        return NULL;
    Group * group = tracks[col].block[ind]->getGroupWichElBelong();
    return group;

}

bool ListControll::isBlockInGroup(int col, int ind)
{
    if (getBlockGroup(col,ind) != NULL)
        return true;
    return false;
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

int ListControll::getDrawBorder(int col, int ind)
{
    if(!testIndexs(col, ind))
        return -1;
    DrawElement *elm = tracks[col].block[ind];
    /*if (elm->getTypeId() != Element_type::Image)
                return -1;*/
    return elm->getBorder() ;
}

bool ListControll::setDrawBorder(int col, int ind, int value)
{
    if(!testIndexs(col, ind))
        return false;
    DrawElement *elm = tracks[col].block[ind];
    /*if (elm->getTypeId() != Element_type::Image)
                return false;*/
    elm->setBorder(value);
    return true;
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

bool ListControll::addBlockToCurentGroup(int col,int ind)
{
    if (!blockValid(col,ind))
        return false;
    return addBlockToCurentGroup(tracks[col].block[ind]);
}

bool  ListControll::addBlockToCurentGroup(DrawElement* block)
{
    qDebug() << "bool  ListControll::addBlockToGroup(DrawElement* block)";
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
    if(curent_group->addTo(block))
    {
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

bool ListControll::isCurentGroupValid()
{
    if (curent_group == NULL)
        return false;
    //curent_group->calcBoundRec();

}



void ListControll::setCtrlPressed(bool value)
{
    //drawYellowRectangle(QRect(1000 ,  140  , 2001  , 141));
    if (group_changed)
        if (ctrl_pressed && !value)
        {
            group_changed = false;

            if (curent_group != NULL)
            {
                if (curent_group->isGroupValid()) //QQQQQQQQQQQQQQ
                {
                    //
                    // curent_group = new Group();
                    /*if (curent_group_buffer != NULL)
                                delete curent_group_buffer;*/
                    //curent_group_buffer = new Group(*(curent_group));
                    curent_group->setBlocksBorderColor("blue");
                    curent_group->initGroupBlocks();
                    curent_group->calcBoundRec();

                    drawYellowRectangle(curent_group->getBoundRec());

                    curent_group->makeBackup();
                }
                else
                {
                    curent_group->setBlocksBorderColor("white");
                    curent_group->deInitGroupBlocks();
                    block_groups.removeAt(curent_group->getIndex());
                    if (curent_group->ablelRebuckup())
                    {
                        curent_group->reloadFromBuckup();
                        curent_group->initGroupBlocks();

                        //curent_group->calcBoundRec();
                    }
                    else
                    {
                        delete curent_group;
                        curent_group = NULL;
                    }

                    /* if (curent_group_buffer != NULL)
                            {
                                curent_group = curent_group_buffer;
                                curent_group_buffer = NULL;

                                curent_group->setBlocksBorderColor("blue");
                                curent_group->initGroupBlocks();
                            }*/
                    //curent_group.setBlocksBorderColor("green");
                }
            }
            isGroupChanged = false;
        }

    if (!ctrl_pressed && value)
    {
        removeRectangle();
        if(curent_group == NULL)
        {
            curent_group = new Group();
            block_groups.append(curent_group);
            curent_group->setIndex(block_groups.size() - 1);
        }
    }

    ctrl_pressed = value;
}

bool ListControll::getCtrlPressed()
{
    return ctrl_pressed;
}

void ListControll::setPosToAppend(QPoint point)
{
    pos_to_append = point;
}

QPoint ListControll::getPosToAppend()
{
    return pos_to_append;
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

bool ListControll::attachBlockLeft(int col, int index, int value)
{
    if (!blockValid(col,index))
        return false;
    if (value < 0)
        value = 0;
    value *=scale_scroll_children;
    qDebug() << "DOVODKA start";
    DrawElement *draw_el = tracks[col].block[index];
    quint64 from_begin = draw_el->getStartDrawTime();
    quint64 life = draw_el->getLifeTime();
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
            if (draw_el2->getTypeId() == Element_type::Empty)
                continue;
            quint64 el2_start = draw_el2->getStartDrawTime();
            quint64 el2_end = draw_el2->getLifeTime() + el2_start;
            int temp_dovodka;
            if (from_begin < el2_start)
            {
                temp_dovodka = el2_start - from_begin;
                temp_dovodka *= -1;
            }
            else
            {
                if (from_begin < el2_end)
                {
                    int temp_dovodka_1 = from_begin - el2_start;
                    int temp_dovodka_2 = el2_end - from_begin;
                    if (abs(temp_dovodka_1) < abs(temp_dovodka_2))
                        temp_dovodka = temp_dovodka_1;
                    else
                        temp_dovodka = -temp_dovodka_2;
                }
                else
                {
                    temp_dovodka = from_begin - el2_end;
                }
            }
            //qDebug() << "temp_dovodka =   "<< temp_dovodka;
            if (abs(temp_dovodka) <=  abs(value) && (abs(temp_dovodka) <  abs(dovod_value) ))
            {
                dovod_value = temp_dovodka;
                // qDebug() << "dovodka value =   "<< dovod_value;
                value_setted = true;
            }
        }
    }
    if (value_setted)
    {
        setBlockTimeLeft(col,index,from_begin - dovod_value);
        /*
                draw_el->setLifeTime(draw_el->getLifeTime() + dovod_value);
                draw_el->setStartDraw(from_begin - dovod_value);*/
        //   setBlockTime(col,index,draw_el->getLifeTime() - dovod_value);
        /* qDebug() << "DOVODKA21 life = " << life;
                from_begin = dovod_value;
                setBlockTimeLeft(col,index,from_begin);
                qDebug() << "DOVODKA22 life = " << life << " dov_val = " << dovod_value;*/
        /*reduceEmptyBlocksFromV2(col,index,-dovod_value);
                updateBlocksStartTimesFrom(col,index);*/
        tracks[col].updateTime();
    }
    // ctrl_pressed = value;
}


bool ListControll::attachBlock(int col, int index, int value)
{
    if (!blockValid(col,index))
        return false;
    value *=scale_scroll_children;
    qDebug() << "DOVODKA start";
    DrawElement *draw_el = tracks[col].block[index];
    quint64 from_width = draw_el->getLifeTime() + draw_el->getStartDrawTime();
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
            if (draw_el2->getTypeId() == Element_type::Empty)
                continue;
            int temp_dovodka = from_width - draw_el2->getLifeTime() - draw_el2->getStartDrawTime();
            //qDebug() << "temp_dovodka =   "<< temp_dovodka;
            if (abs(temp_dovodka) <=  abs(value) && (abs(temp_dovodka) <  abs(dovod_value) ))
            {
                dovod_value = temp_dovodka;
                // qDebug() << "dovodka value =   "<< dovod_value;
                value_setted = true;
            }
            else
            {
                int temp_dovodka = from_width  - draw_el2->getStartDrawTime();
                //qDebug() << "temp_dovodka =   "<< temp_dovodka;
                if (abs(temp_dovodka) <=  abs(value) && (abs(temp_dovodka) <  abs(dovod_value) ))
                {
                    dovod_value = temp_dovodka;
                    // qDebug() << "dovodka value =   "<< dovod_value;
                    value_setted = true;
                }
            }
        }
    }
    if (value_setted)
    {
        draw_el->setLifeTime(draw_el->getLifeTime() - dovod_value);
        //   setBlockTime(col,index,draw_el->getLifeTime() - dovod_value);
        reduceEmptyBlocksFromV2(col,index,-dovod_value);
        updateBlocksStartTimesFrom(col,index);
        tracks[col].updateTime();
    }
    // ctrl_pressed = value;
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
    view.setModality(Qt::WindowModal);
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
    view.setWidth(1000);

    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    connect(&f_manager,SIGNAL(filePathNameChanged(QString)),this,SLOT(addNewBlockFromLibrary( QString)));
    connect(&f_manager, SIGNAL(filePathNameChanged(QString)),this,SLOT(loadFromFile(QString)));


    //view.setMaximumHeight(215);
    //loadCurrentTextInTheFirstBlockWhenInit();


    /* view.setWidth(1200);
           view.setHeight(600);*/
    connect(this,SIGNAL(setBlockPlayTimeUntilFreezeSignal(int,int,int)),
            this, SLOT (emitSetBlockPlayTimeUntilFreezeSignal2(int,int,int)));
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

bool ListControll::save(QIODevice* device, QProgressBar *bar)
{
    QDataStream stream(device);
    stream << (float)VERSION;
    stream << tracks.size() ;
    QSet<Group*> allGroups;

    for (int i=0; i< tracks.size(); i++)
    {
        tracks[i].save(device, bar);

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
    /*mess_box.setText("Project saved");
            mess_box.show();*/
    return true;
}

bool ListControll::load(QIODevice* device)
{
    //QDataStream stream(device);
    float version = 0.0f;
    tracks.clear();
    int tracks_size;
    QDataStream stream(device);
    stream >> version;
    qWarning() << "LOAD_VERSION   v" << version ;
    stream >> tracks_size ;
    //  qDebug() << "Num of loaded tracks: " << tracks_size;
    for (int i=0; i< tracks_size; i++)
    {
        Track temp;
        temp.load(device, version);
        //qDebug() << "load blocks size in track" << temp.block.size();
        tracks.append(temp);

        updateBlocksIndexFrom(i, 0);
        updateBlocksStartTimesFrom(i, 0);
    }
    //@ CRASH IN RELEASE BUT WORK IN DEBUG @
    //  qApp->processEvents(QEventLoop::AllEvents,10000);

    for (int k=0; k< tracks.size(); k++)
    {
        if (version < 2.95)
        {
            for (int i=0; i< tracks[k].block.size();)
            {
                addEmptyBlockAt(k, i, 0);
                i+=2;
            }
            updateBlocksIndexFrom(k, 0);
            updateBlocksStartTimesFrom(k, 0);
        }



        for (int i=0; i< tracks[k].block.size(); i++)
        {
            DrawElement *el_connect = tracks[k].block[i];
            connect(el_connect,SIGNAL(borderColorChangedSignal(int,int,QString)),
                    this,SIGNAL(borderColorChangedSignal(int,int,QString)));
            connect(el_connect,SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
                    this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
            if (el_connect->getTypeId() != Element_type::Empty)
            {
                connect(el_connect,SIGNAL(dontUseThisValue()),
                        this, SIGNAL(dontUseThisValue()));
                connect(el_connect,SIGNAL(playTimeUntilFreezeChangeSignal(int,int,int)),
                        this, SIGNAL(setBlockPlayTimeUntilFreezeSignal(int,int,int)));
                el_connect->setPlayTimeUntilFreeze(el_connect->getPlayTimeUntilFreeze());
            }

        }
        //updateBlocksPlayTimeUntilFreeze(k);

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
        //group->isGroupValid();
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

int ListControll::getMemberCount()
{
    int count = 0;
    for(Track tr: tracks)
    {
        count += tr.block.size();
    }
    return count;
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
    emit scalePointerXChanged(x);
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
    //qDebug() << "BLOCK FOR DRAW" << pointed_block.size();
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
    emit updateTrackAt(block_in_buffer->getBlockColumn());


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

void ListControll::setBlockPositionSizeFromBuffer()
{
    if (!buffer_is_full)
        return;

    setBlocked(true);

    QPoint sel = getSelectedBlockPoint();
    DrawElement *elm = getBlock(sel);
    elm->getDrawWidget()->setSelElm( NULL);

    elm->setRect(block_in_buffer->getRect());

    setBlocked(false);
}

void ListControll::setBlockEffectsFromBuffer()
{
    QVector<ShaderEffect> effList = block_in_buffer->getEffects();
    DrawElement *elm = getBlock(getSelectedBlockPoint());
    elm->clearEffects();
    for(ShaderEffect eff : effList)
    {
        elm->addEffect(eff);
    }

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
    emit maxTrackTimeChanged(maxTrackTime);
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
    /* if(elm->getGroupWichElBelong() != NULL)
            {
                elm->getGroupWichElBelong()->tryMemberReverce(elm, text);
            }*/
    delete elm;
    tracks[selectedBlockPoint.x()].block[selectedBlockPoint.y()] = text;
    text->setBlockColumn(selectedBlockPoint.x());
    text->setBlockIndex(selectedBlockPoint.y());
    connect(text,SIGNAL(borderColorChangedSignal(int,int,QString)),
            this,SIGNAL(borderColorChangedSignal(int,int,QString)));
    connect(text,SIGNAL(sizeChangedSignal(int,int, quint64, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, quint64, bool)));
    connect(text,SIGNAL(dontUseThisValue()),
            this, SIGNAL(dontUseThisValue()));


    calcPointedBlocks();
    emit updateSelectedBlock(selectedBlockPoint);
    emit updateSelectBlock();
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

DrawElement* ListControll::getSelectedBlock()
{
    if(!blockValid(selectedBlockPoint))
        return NULL;
    return this->getBlock(selectedBlockPoint);
}


bool ListControll::blockValid(QPoint point)
{
    return blockValid(point.x(),point.y());
}
int ListControll::getBlockPlayTimeUntilFreeze(int col, int i )
{
    if(!blockValid(col, i))
        return -1;
    return tracks[col].block[i]->getPlayTimeUntilFreeze();
}

int ListControll::updateBlocksPlayTimeUntilFreeze(int col)
{
    if(!blockValid(col, 0))
        return -1;
    foreach(DrawElement *elm, tracks[col].block)
        if (elm->getTypeId() != Element_type::Empty)
            elm->setPlayTimeUntilFreeze(elm->getPlayTimeUntilFreeze());
}


void ListControll::setBlockPlayTimeUntilFreeze(int col, int i, int val)
{
    if(!blockValid(col, i))
        return;
    DrawElement *elm =  tracks[col].block[i];
    elm->setPlayTimeUntilFreeze(val);
    qDebug() << "RRRRRRRRRRRRRRR     void ListControll::setBlockPlayTimeUntilFreeze(int col, int i, int val) ";
}






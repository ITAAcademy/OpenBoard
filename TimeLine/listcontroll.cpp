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
    //if (false)
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
                    if (curent_group->addTo(draw_el))
                    {
                        need_calc_bound_rec = true;
                        isGroupChanged = true;
                        // curent_group = &test_group;
                        draw_el->setBlockBorderColor(colora);
                        //emit borderColorChangedSignal(value.x(), value.y(), colora);
                        qDebug() << "ListControll::setSelectedBlockPoint adding block to group succesfull";

                        if (el_ind > 1)
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
                        }


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
                    curent_group->calcBoundRec();
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
                        if (t_group->isGroupValid())
                        {
                            t_group->calcBoundRec();

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
                                //curent_group = elm->getGroupWichElBelong();
                                drawYellowRectangle(curent_group->getBoundRec());
                                qDebug() << "rawYellowRectangle(curent_group->getBoundRec());";
                            }
                        }
                        else
                        {
                            t_group->setBlocksBorderColor("white");
                            t_group->deInitGroupBlocks();
                            t_group->clear();


                        }
                    }
                }
            }

        }

        selectedBlockPoint = value;
        emit updateSelectedBlock(value);

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

bool ListControll::redrawYellowRect()
{
    curent_group->calcBoundRec();
    drawYellowRectangle(curent_group->getBoundRec());
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
    curent_group->calcBoundRec();
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
    elm = tracks[col].block[i];

    if (i > 0)
    {
        DrawElement *prev = tracks[col].block[i -1];
        int type = prev->getTypeId();
        if (type == Element_type::Empty )
        {
            prev->setLifeTime( prev->getLifeTime() + l_time);
            // tracks[col].addTime(l_time);
            tracks[col].block.removeAt(i);
            delete elm;
            elm = prev;

            i--; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\
            updateBlocksIndexFrom(col,i);



        }
    }
    if (i +1 < tracks[col].block.size() )
    {
        DrawElement * next_el = tracks[col].block[i + 1];
        if (next_el->getTypeId() == Element_type::Empty)
        {
            l_time = elm->getLifeTime();
            elm->setLifeTime(next_el->getLifeTime() + l_time);
            // tracks[col].addTime(l_time);
            tracks[col].block.removeAt(i + 1);
        }
    }
    if (del_last_empty)
    {
        DrawElement *tmp = tracks[col].block.last();
        if (tmp->getTypeId() ==  Element_type::Empty)
        {
            tracks[col].addTime(-tmp->getLifeTime());
            delete tmp;
            tmp = NULL;
            tracks[col].block.removeLast();

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
    QMap <int,int> start_ind;
    for (int i=0 ; i < tracks[col].block.size(); i++)
    {
        DrawElement* elm = tracks[col].block[i];
        int start = elm->getStartDrawTime();
        start_ind.insert(start,i);
    }
    int time_bonus = 0;
    int na_siky_zmensh = 0;
    DrawElement *prev_elm = NULL;
    foreach(int index, start_ind)
    {
        DrawElement* elm = tracks[col].block[index];
        int cur_start = elm->getStartDrawTime();
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

void ListControll::setForceAppendBlock(bool value)
{
    force_append_block = value;
    qDebug() << "void ListControll::setForceAppendBlock " << force_append_block;
}


void ListControll::addNewBlock(int col, QString str, DrawElement *element)
{
    if (element == NULL)
    {
        DrawTextElm *dr_text = new DrawTextElm(NULL,NULL);
        element = (DrawElement*) dr_text;
    }

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





    tracks[col].block.append(element);
    addEmptyBlockAt(col, tracks[col].block.size() - 1 , 0);

    tracks[col].addTime(element->getLifeTime());
    long temp_time = tracks[col].getTime();
    updateBlocksStartTimesFrom(col,0);
    if (maxTrackTime <  temp_time)
        maxTrackTime =  temp_time;
    calcPointedBlocks();

    qDebug() << "void ListControll::addNewBlock(   track time = " << tracks[col].getTime();
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


int ListControll::getBlockIndToAddFromPos(DrawElement * elm, int pos, int col_dest )
{
    return getBlockIndToAddFromPos(elm->getBlockColumn(),elm->getBlockIndex(),pos,col_dest);
}



int ListControll::getBlockIndToAddFromPos(int col,int ind, int pos, int col_dest)
{
    spaces_to_add = -1;
    qDebug() << "         DAAAAAAAAAAAAAAAAAAAAAAAAA                  !!!!!!!!!!!!!!!!!!!                      ee";
    if (!blockValid(col,ind))
        return -1;

    int get_ind = -1;
    DrawElement * move_block = tracks[col].block[ind];

    removeBlock(col,ind,false,true,false); // dont delete draw element
    if (col_dest >= 0)
    {
        col = col_dest;
        qDebug() << "col = col_dest = " << col_dest;
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
                    this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));*/
        //tracks[col].addTime(mov_block_time);
        addEmptyBlockAt(col,get_ind  ,spaces_to_add - mov_block_time);



        updateBlocksIndexFrom(col,0);
        updateBlocksStartTimesFrom(col,0);
        tracks[col].updateTime();
        recountMaxTrackTime();
        return get_ind;
    }



    //logBlocksTypes(col);
    //if (false)
    foreach (DrawElement* elm,tracks[col].block )
    {
        /*  if( elm->getBlockIndex() == ind)
            continue;*/

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
                if (pos + mov_block_time <= end || force_append_block)     //if (force_append_block)
                {
                    int elm_index = elm->getBlockIndex();
                    int new_time = pos - start;
                    bool elm_is_last = (elm_index == track_size - 1 ||
                                        move_block->getBlockIndex() == track_size - 1);// ? true : false;
                    elm->setLifeTime( new_time);
                    tracks[col].block.insert(elm_index + 1, move_block);

                    int right_emp_time = end - pos - mov_block_time;
                    if (!elm_is_last && right_emp_time > 0 )
                    {
                        int next_index = elm_index + 2;
                        DrawElement* next_el = tracks[col].block[next_index];

                        if (next_el->getTypeId() != Element_type::Empty)
                        {
                            /* DrawElement* right_empty = new DrawElement(NULL,NULL);
                            right_empty->setLifeTime(right_emp_time);
                            tracks[col].block.insert(elm_index + 2,right_empty);
                            right_empty->setBlockColumn(col);
                            right_empty->setBlockIndex(elm_index + 2);
                            */
                            addEmptyBlockAt(col,elm_index + 2  ,right_emp_time);
                            /* connect(right_empty, SIGNAL(borderColorChangedSignal(int,int,QString)),
                                        this, SIGNAL(borderColorChangedSignal(int,int,QString)));
                                connect(right_empty, SIGNAL(sizeChangedSignal(int,int, int, bool)),
                                        this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));*/
                            qDebug() << "AAAAAAAAAAAA " << tracks[col].getTime();
                        }
                        else
                        {
                            next_el->setLifeTime(next_el->getLifeTime() + right_emp_time );
                            tracks[col].addTime(right_emp_time);
                            qDebug() << "BBBBBBBBBBBB " << tracks[col].getTime();
                        }
                        qDebug() << " tracks[col].addTime(" <<  right_emp_time;
                        // tracks[col].setTime( pos + mov_block_time + right_emp_time);
                    }
                    else
                    {
                        //tracks[col].setTime( pos + mov_block_time);
                        // qDebug() << "FFFFFFFFFFFF " << tracks[col].getTime(); /////////////666666666666666666666
                        if (elm_is_last)
                        {
                            int val = start + life - mov_block_time - pos;
                            /* DrawElement* right_empty = new DrawElement(NULL,NULL);
                            right_empty->setLifeTime(val);
                            tracks[col].block.insert(elm_index + 2 ,right_empty);
                            right_empty->setBlockColumn(col);
                            right_empty->setBlockIndex(elm_index + 2);
                            */
                            addEmptyBlockAt(col,elm_index + 2  ,val);
                            /* connect(right_empty, SIGNAL(borderColorChangedSignal(int,int,QString)),
                                        this, SIGNAL(borderColorChangedSignal(int,int,QString)));
                                connect(right_empty, SIGNAL(sizeChangedSignal(int,int, int, bool)),
                                        this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));*/
                            qDebug() << "FFFFFFFFFFFF  salonamana66  "<<val;
                        }
                        else
                        {
                            DrawElement * next =  tracks[col].block[elm_index + 2];
                            reduceEmptyBlocksFrom(col,elm_index+1,  pos + mov_block_time - next->getStartDrawTime());
                            qDebug() << "FFFFFFFFFFFF  papapa" <<
                                        next->getStartDrawTime() <<
                                        "    " << pos;
                        }

                    }
                    updateBlocksIndexFrom(col,0);
                    updateBlocksStartTimesFrom(col,0);
                    tracks[col].updateTime();
                    recountMaxTrackTime();
                    return  get_ind;
                }
                else
                {
                    getBlockIndToAddFromPos(move_block,move_block_start_time);

                    return 1;
                }
            }
            else  //Element_type != empty
            {
                int append_ind = pos_to_append.y();

                if (force_append_block )
                {
                    qDebug() << "1111111111111111";
                    //addEmptyBlockAt(col, append_ind , 500); //12345'
                    //this->addBlockAt(col, append_ind );
                    tracks[col].block.insert(append_ind, move_block);
                    //addEmptyBlockAt(col, append_ind , 1001); //12345'
                    // addEmptyBlockAt(col, append_ind + 1 , 0); //12345
                    //addEmptyBlockAt(col, append_ind , 0); //12345'
                    //append_ind += 1;
                    //this->addBlockAt(col, append_ind + 1 );

                    if (append_ind > 0 && append_ind == elm_index)
                    {
                        DrawElement* prev_el = tracks[col].block[elm_index - 1];
                        if (prev_el->getTypeId() == Element_type::Empty)
                        {
                            int prev_time = prev_el->getLifeTime();

                            if (prev_time >mov_block_time)
                            {
                                //tracks[col].addTime(\-mov_block_time);
                                prev_time -= mov_block_time;
                                prev_el->setLifeTime(prev_time);
                                /*for (int j = elm_index + 1; j < tracks[col].block.size(); j++)
                                {
                                    DrawElement *elma = tracks[col].block[j];
                                    if (elma->getTypeId()  == Element_type::Empty)
                                    {
                                        int time = elma->getLifeTime();
                                        //time -=value;
                                        if (time <= mov_block_time)
                                        {
                                           // tracks[col].addTime(-time);
                                            mov_block_time -= time;
                                            tracks[col].block.removeAt(j);
                                            delete elma;
                                            j--;
                                        }
                                        else  // time > value
                                        {
                                            time -= mov_block_time;
                                            elma->setLifeTime(time);
                                            //tracks[col].addTime(-value);
                                            j = tracks[col].block.size();
                                        }
                                    }
                                }*/
                                qDebug() << "1111111111111111    2";
                                updateBlocksIndexFrom(col,0);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                recountMaxTrackTime();
                                // return 1;
                            }
                            else
                            {
                                qDebug() << "1111111111111111 3";
                                /*tracks[col].block.removeAt(append_ind - 1);
                                // tracks[col].block.move(append_ind-1, append_ind);

                                 removeBlock(col,append_ind-1,false,true,false);
                                 tracks[col].block.insert(append_ind+1, move_block);
                                //tracks[col].block.insert(append_ind,move_block);
                               // tracks[col].addTime(mov_block_time - prev_time);
                                 int temp_time = reduceEmptyBlocksFrom(col,append_ind+1,mov_block_time);*/
                                /* if (temp_time > 0)
                                     tracks[col].addTime( -mov_block_time + temp_time);*/

                                reduceEmptyBlocksFromV2(col,elm_index,mov_block_time);
                                /* for (int j = elm_index; j < tracks[col].block.size(); j++)
                                {
                                    DrawElement *elma = tracks[col].block[j];
                                    if (elma->getTypeId()  == Element_type::Empty)
                                    {
                                        int time = elma->getLifeTime();
                                        //time -=value;
                                        if (time <= mov_block_time)
                                        {
                                            // tracks[col].addTime(-time);
                                            mov_block_time -= time;
                                            tracks[col].block.removeAt(j);
                                            delete elma;
                                            j--;
                                        }
                                        else  // time > value
                                        {
                                            time -= mov_block_time;
                                            elma->setLifeTime(time);
                                            //tracks[col].addTime(-value);
                                            j = tracks[col].block.size();
                                        }
                                    }
                                }*/

                                updateBlocksIndexFrom(col,0);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                recountMaxTrackTime();
                                //return 1;
                            }


                        }
                        else
                        {

                            int temp_time = reduceEmptyBlocksFrom(col,elm_index,mov_block_time);
                            /*if (temp_time > 0)
                                tracks[col].addTime( -mov_block_time + temp_time);
                            */
                            updateBlocksIndexFrom(col,0);
                            updateBlocksStartTimesFrom(col,0);
                            tracks[col].updateTime();
                            recountMaxTrackTime();
                            qDebug() << "pupupuppuu     09 090 9 0";
                            //return 1;;
                        }
                    }
                    else
                    {
                        if (append_ind < tracks[col].block.size() - 1 && append_ind == elm_index + 1)
                        {
                            DrawElement* next_el = tracks[col].block[append_ind + 1];
                            if (next_el->getTypeId() == Element_type::Empty)
                            {
                                int next_time = next_el->getLifeTime();
                                if (next_time >mov_block_time)
                                {
                                    //tracks[col].addTime(\-mov_block_time);
                                    next_time -= mov_block_time;
                                    next_el->setLifeTime(next_time);
                                    /*  updateBlocksIndexFrom(col,0);
                                    updateBlocksStartTimesFrom(col,0);

                                    reduceEmptyBlocksFrom(col,elm_index,mov_block_time);*/

                                    updateBlocksIndexFrom(col,0);
                                    updateBlocksStartTimesFrom(col,0);
                                    tracks[col].updateTime();
                                    recountMaxTrackTime();
                                    qDebug() << "poduska";
                                    //return 1;;

                                }
                                else
                                {
                                    tracks[col].block.removeAt(append_ind + 1);


                                    tracks[col].addTime(mov_block_time - next_time);
                                    int temp_time = reduceEmptyBlocksFrom(col,append_ind + 1,mov_block_time - next_time);\
                                    /* if (temp_time > 0)
                                        tracks[col].addTime( -mov_block_time + temp_time);*/

                                    updateBlocksIndexFrom(col,0);
                                    updateBlocksStartTimesFrom(col,0);
                                    tracks[col].updateTime();
                                    recountMaxTrackTime();
                                    qDebug() << "tatuska";
                                    // return 1;
                                }
                            }
                            else
                            {
                                tracks[col].addTime(mov_block_time); //nepravilno
                                reduceEmptyBlocksFrom(col,elm_index - 1,mov_block_time);
                                updateBlocksIndexFrom(col,0);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                recountMaxTrackTime();
                                qDebug() << "bubuska";  ////9999999999999999999999
                                //return 1;
                            }
                        }
                        else
                        {

                            /* if (pos_to_append.y() == elm_index + 1)
                                tracks[col].block.move(append_ind,append_ind - 1);*/
                            int mov_index = move_block->getBlockIndex();
                            if (mov_index < elm_index)
                            {
                                if (elm_index < pos_to_append.y())
                                {
                                    if (pos_to_append.y() < mov_index)
                                    {
                                        qDebug() << "buba 1";  // ok

                                    }
                                    else
                                    {
                                        qDebug() << "buba 2";
                                    }
                                }
                                else
                                {
                                    if (pos_to_append.y() < mov_index)
                                    {
                                        qDebug() << "buba 3";

                                    }
                                    else
                                    {
                                        qDebug() << "buba 4";
                                    }
                                }
                            }
                            else
                            {
                                if (elm_index < pos_to_append.y())
                                {
                                    if (pos_to_append.y() < mov_index)
                                    {
                                        qDebug() << "buba 11";  // ok

                                    }
                                    else
                                    {
                                        qDebug() << "buba 12"; // ok
                                        /* if (pos_to_append.y() == elm_index + 1)
                                            tracks[col].block.move(append_ind,append_ind - 1);*/
                                    }
                                }
                                else
                                {
                                    if (pos_to_append.y() < mov_index)
                                    {
                                        qDebug() << "buba 13";

                                    }
                                    else
                                    {
                                        qDebug() << "buba 14";
                                    }
                                }
                            }




                            /*if (mov_index < elm_index)
                            {
                                if (pos_to_append.y() < elm_index + 2)
                                {
                                    qDebug() << "baba 1";
                                }
                                else
                                {
                                    qDebug() << "baba 2";
                                }
                            }
                            else
                            {
                                if (pos_to_append.y() < elm_index + 2)
                                {
                                    qDebug() << "baba 3";
                                }
                                else
                                {
                                    qDebug() << "baba 4";
                                }

                            }*/
                            /* int new_tim = elm->getLifeTime() - mov_block_time;
                            if (new_tim > 0)
                                elm->setLifeTime(new_tim);
                            else
                            {
                                elm->setLifeTime(0);
                                /*delete elm;
                                tracks[col].block.removeAt(append_ind - 1);

                            }*/


                            reduceEmptyBlocksFrom(col,elm_index ,mov_block_time);
                            updateBlocksIndexFrom(col,0);
                            updateBlocksStartTimesFrom(col,0);
                            tracks[col].updateTime();
                            recountMaxTrackTime();
                            qDebug() << "ta nu _____________________________________________=-=-=-=-  pos_to_append  = "<< pos_to_append << "  elm_index = " << elm_index
                                     << "  mov_index = " << mov_index;
                            // return 1;

                        }
                    }
                    addEmptyBlockAt(col, append_ind , 0); //12345'
                    addEmptyBlockAt(col, append_ind-1 , 0); //12345'
                    //this->addBlockAt(col, append_ind );
                    // tracks[col].addTime(mov_block_time);

                    return 1;
                }
                else // force_append_block
                {
                    if (append_ind ==  track_size - 1)
                    {
                        tracks[col].block.insert(append_ind, move_block);
                        tracks[col].addTime(mov_block_time);
                        qDebug() << "22222222222222";
                        updateBlocksIndexFrom(col,0);

                        updateBlocksStartTimesFrom(col,0);
                        tracks[col].updateTime();
                        recountMaxTrackTime();
                        return 1;
                    }
                    else
                    {
                        DrawElement* next_el = tracks[col].block[append_ind];
                        if (next_el->getTypeId() == Element_type::Empty)
                        {
                            int next_el_time = next_el->getLifeTime();
                            if (next_el_time > mov_block_time)
                            {
                                tracks[col].block.insert(append_ind, move_block);
                                next_el->setLifeTime(next_el->getLifeTime() - mov_block_time);
                                qDebug() << "333333333333333333333";
                                updateBlocksIndexFrom(col,0);
                                updateBlocksStartTimesFrom(col,0);
                                tracks[col].updateTime();
                                recountMaxTrackTime();
                                return 1;
                            }
                            else
                                if (next_el_time == mov_block_time)
                                {
                                    tracks[col].block.insert(append_ind, move_block);
                                    tracks[col].block.removeAt(append_ind + 1);
                                    delete next_el;
                                    qDebug() << "44444444444444";
                                    updateBlocksIndexFrom(col,0);
                                    updateBlocksStartTimesFrom(col,0);
                                    tracks[col].updateTime();
                                    recountMaxTrackTime();
                                    return 1;
                                }
                                else
                                {
                                    if (next_el_time >= minBlockTime)
                                    {
                                        move_block->setLifeTime(next_el_time);
                                        tracks[col].block.insert(append_ind, move_block);
                                        tracks[col].block.removeAt(append_ind + 1);
                                        delete next_el;
                                        qDebug() << "55555555555555";
                                        updateBlocksIndexFrom(col,0);
                                        updateBlocksStartTimesFrom(col,0);
                                        tracks[col].updateTime();
                                        recountMaxTrackTime();
                                        return 1;
                                    }
                                    else
                                    {
                                        qDebug() << "666666666666666666";
                                        return getBlockIndToAddFromPos(move_block,move_block_start_time);
                                    }
                                }
                            /* tracks[col].block.insert(append_ind, move_block);
                            next_el->setLifeTime(next_el->getLifeTime());
                            tracks[col].addTime(mov_block_time);*/

                        }


                    }
                    //getBlockIndToAddFromPos(move_block,move_block_start_time);
                }
            }
        }
    }
    getBlockIndToAddFromPos(move_block,move_block_start_time);
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


        if (new_time < 0)
        {
            value = -new_time;
            new_time = 0;
            k_elm->setLifeTime(new_time,true)    ;
            block_to_del.append(k);
            qDebug() << "99999999999999999999999999";

        }
        else
        {
            //value -= new_time;
            k_elm->setLifeTime(new_time,true)    ;
            value -= new_time - f_time;
            qDebug() << "8888888888888888888888888888";
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
    if (!blockValid(col,ind))
        return;

    if (element == NULL)
    {
        DrawTextElm *dr_text = new DrawTextElm(NULL,NULL);
        element = (DrawElement*) dr_text;
        element->setKey(QString("block"+ QString::number(qrand())));
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

                            tracks[col].addTime(elm_time);
                            updateBlocksStartTimesFrom(col,ind );

                            delete element;
                            long temp_time = tracks[col].getTime();
                            if (maxTrackTime <  temp_time)
                                maxTrackTime =  temp_time;
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
    connect(element, SIGNAL(sizeChangedSignal(int,int, int, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));
    element->setBlockColumn(col);
    element->setBlockIndex(ind);


    // tracks[col].block.append(element);


    if(need_balance && element->getGroupWichElBelong() == NULL)
        balanceBlocksIfIsGroups(col,ind + 1);

    updateBlocksIndexFrom(col,0);
    updateBlocksStartTimesFrom(col,0 );



    tracks[col].addTime(element->getLifeTime());
    long temp_time = tracks[col].getTime();
    if (maxTrackTime <  temp_time)
        maxTrackTime =  temp_time;
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

    if (maxTrackTime < temp_traclwidth)
        maxTrackTime = temp_traclwidth; //1234
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
    loadFromFile(curent_block.x(),  curent_block.y(),  path);
}



DrawElement* ListControll::loadFromFile(int col, int ind, QString path,bool emit_update)
{
    if (emit_update)
        if ( load_from_file_or_library )
            return NULL;
    qDebug() << "loadFromFile(): col = " << col << " IND = " << ind;
    setBlocked(true);
    qApp->processEvents();

    QString open;
    if ( path == "")
        open =  QFileDialog::getOpenFileName(0, QString(), QString(), QString(), 0, QFileDialog::DontUseNativeDialog);
    else
        open = path;


    DrawElement *elm = GenerationDrawElement(open,NULL,NULL);
    if(elm == NULL)
    {
        qDebug() << "loadFromFile(): elm == NULL";
        return NULL;
    }


    if (elm->getTypeId() == Element_type::Image && p_drawWidget != NULL) //123_123
    {
        QSize image_size = QPixmap(open).size();
        elm->setSize(p_drawWidget->imageLoadedPictureSizeSlot(image_size));

    }


    if (emit_update)
    {
        DrawElement* temp = tracks[col].block[ind]; ///////!!!!!!!!!!!!!!!!!!!!
        int new_life_time = elm->getLifeTime();

        //elm->copy(temp);
        elm->setLifeTime(temp->getLifeTime());
        elm->setStartDraw(temp->getStartDrawTime());
        elm->setZ(col);
        elm->setBlockColumn(col);
        elm->setBlockIndex(ind);


        //elm->setParent(temp->getParent());
        // elm->setGroupWichElBelong(temp->getGroupWichElBelong());
        //  elm->setDrawWidget(temp->getDrawWidget());

        tracks[col].block[ind] = elm;
        delete temp;

        //zaloop
        /*      if(life_time == 1000)
            setBlockTime(col, ind, new_life_time);
*/
        //  tracks[col].block[ind] = elm;

        updateBlocksStartTimesFrom(col,0);
        calcPointedBlocks();
    }


    connect(elm,SIGNAL(borderColorChangedSignal(int,int,QString)),
            this,SIGNAL(borderColorChangedSignal(int,int,QString)));
    qDebug() << "LIFE_TIME  2";
    connect(elm,SIGNAL(sizeChangedSignal(int,int, int, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));

    qDebug() << "LIFE_TIME  3";
    QFileInfo file_info(path);

    elm->setKey(file_info.fileName());
    qDebug() << "LIFE_TIME  4";
    if (emit_update)
    {
        qDebug() << "ListControll::loadFromFile    emit updateSelectedBlock     ";
        //emit updateSelectedBlock(selectedBlockPoint);
        sendUpdateModel();
    }


    setBlocked(false);

    return elm;
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
    tracks[p.x()].addTime(origin->getLifeTime() - clone->getLifeTime());

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



void ListControll::setBlockTime(int col, int i,int value, bool resize_next_empty)
{
    if(!blockValid(col,i))
        return;
    //qDebug() << "void ListControll::setBlockTime(int col, int i,int value) = " << value;
    DrawElement *elm =  tracks[col].block[i];

    if (elm == NULL)
        return;

    int cur_time___ = elm->getLifeTime();

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

    int adding_time = value - cur_time___;
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
    if (adding_time > 0)
    {
        //     tracks[col].addTime(adding_time);
    }
    else
        if (adding_time == 0)
        {
            //updateBlocksIndexFrom(col,i);
        }


    if ( tracks[col].block[i]->getGroupWichElBelong() == NULL)
        balanceBlocksIfIsGroups(col,i);

    tracks[col].addTime(value - elm->getLifeTime());
    elm->setLifeTime(value);

    recountMaxTrackTime();

}

void ListControll::setBlockTimeWithUpdate(int col, int i, int value, bool visual)
{
    qDebug() << "void ListControll::setBlockTimeWithUpdate(int col = " << col << " ind = "<<  i
             <<"value = "<< value;
    //setBlockTime(col, i, value);
    // if(visual)
    emit blockTimeSignel(col, i, value);
}


bool ListControll::balanceBlocksIfIsGroups(int col0, int ind0 , bool calc_time_change)
{
    for(int i = 0; i < tracks.size(); i++)
        for(int j = 0; j < tracks[i].block.size(); j++)
        {
            checkBlockValidGroup(tracks[i].block[j]);
        }
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
    if(elm->getGroupWichElBelong() != NULL)
    {
        Group *groupTemp = elm->getGroupWichElBelong();
        if(!groupTemp->isGroupValid())
        {
            groupTemp->deInitGroupBlocks();
            delete groupTemp;
            removeRectangle();
        }
    }

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
    long delta =  tracks[col0].calcTimeChange();

    for (int i=ind0; i < tracks[col0].block.size(); i++)
    {

        DrawElement *temp_el = tracks[col0].block[i - 1];
        int draw_time = temp_el->getStartDrawTime()  + temp_el->getLifeTime();
        tracks[col0].block[i]->setStartDraw(draw_time);
    }

    if(false)
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

    qDebug() << "void ListControll::setBlockStartTime(int col, int i,int value)";


    if(testIndexs(col, i))
    {
        if (value < 0)
        {
            value = 1;
        }
        tracks[col].block[i]->setStartDraw(value);
    }


    //qDebug() << "value = " << value;
    /*
    if(testIndexs(col, i))
        tracks[col].block[i]->setStartDraw(value);*/

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

void ListControll::setCtrlPressed(bool value)
{
    if (group_changed)
        if (ctrl_pressed && !value)
        {
            group_changed = false;

            if (curent_group != NULL)
            {
                if (curent_group->isGroupValid())
                {
                    //
                    // curent_group = new Group();
                    curent_group->setBlocksBorderColor("blue");
                    curent_group->initGroupBlocks();
                    drawYellowRectangle(curent_group->getBoundRec());
                }
                else
                {
                    curent_group->setBlocksBorderColor("white");
                    curent_group->deInitGroupBlocks();
                    delete curent_group;
                    curent_group = NULL;
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
        }
    }
    if (value_setted)
        draw_el->setLifeTime(draw_el->getLifeTime() - dovod_value);
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
    qDebug() << "LOAD_VERSION   v" << version ;
    stream >> tracks_size ;
    //  qDebug() << "Num of loaded tracks: " << tracks_size;
    for (int i=0; i< tracks_size; i++)
    {
        Track temp;
        temp.load(device, version);
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
    if(elm->getGroupWichElBelong() != NULL)
    {
        elm->getGroupWichElBelong()->tryMemberReverce(elm, text);
    }
    delete elm;
    tracks[selectedBlockPoint.x()].block[selectedBlockPoint.y()] = text;
    text->setBlockColumn(selectedBlockPoint.x());
    text->setBlockIndex(selectedBlockPoint.y());
    connect(text,SIGNAL(borderColorChangedSignal(int,int,QString)),
            this,SIGNAL(borderColorChangedSignal(int,int,QString)));
    connect(text,SIGNAL(sizeChangedSignal(int,int, int, bool)),
            this, SLOT(setBlockTimeWithUpdate(int, int, int, bool)));

    calcPointedBlocks();
    emit updateSelectedBlock(selectedBlockPoint);
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




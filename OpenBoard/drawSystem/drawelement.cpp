#include "drawElement.h"
#include "../TimeLine/listcontroll.h"
class ListControll;
OGLWidget *DrawElement::getDrawWidget() const
{
    return pDrawWidget;
}

bool DrawElement::setDrawWidget(OGLWidget *value)
{


    if(value == pDrawWidget && value != NULL)
    {
        //  qDebug() << "VALUE  " << fboWrapper.errorStatus;
        if(fboWrapper.errorStatus != 0 &&  pDrawWidget->isInit()){
            setFBOWrapper(pDrawWidget->initFboWrapper(pDrawWidget->getWax(),pDrawWidget->getWay()));//TODO
            for (int i = 0; i <effects.length(); i++)
                effects[i].setShaderWrapper(pDrawWidget->getShaderPrograms()[effects[i].getShaderWrapperIndex()]);
        }
        return false;
    }


    if(pDrawWidget != NULL)
    {
        disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }


    pDrawWidget = value;

    connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));

    for (int i = 0; i <effects.length(); i++)
        effects[i].setShaderWrapper(pDrawWidget->getShaderPrograms()[effects[i].getShaderWrapperIndex()]);

    // qDebug() << "before alpha effect created";
    // qDebug() << "pDrawWidget->getShaderPrograms().length:"<<pDrawWidget->getShaderPrograms().length();


    if(fboWrapper.errorStatus != 0  && pDrawWidget->isInit())
    {
        // qDebug()<<"BEFORE SETFBOWRAPPER";
        setFBOWrapper(pDrawWidget->initFboWrapper(pDrawWidget->getWax(),pDrawWidget->getWay()));//TODO


        //qDebug()<<"AFTER SETFBOWRAPPER";

    }
    return true;

}

QString DrawElement::getKey() const
{
    return key;
}

void DrawElement::setKey(const QString &value)
{
    key = value;
}


DrawElement::DrawElement(OGLWidget *drawWidget, QObject *parent) : QObject(parent)
{
    playTimeUntilFreeze = 1000;
    group_wich_el_belong = NULL;
    startDrawTime = 0;
    pDrawWidget = drawWidget;
    bPause = false;
    x = 0;
    y = 0;
    z = 0;
    width = 100;
    height = 100;
    keyCouter = 0;
    lifeTime = -1;
    icon = QImage();
    typeId = Element_type::Empty;
    fboWrapper.errorStatus = -1;

    show_text_cursor = false;
    use_anim_time = 2;
    if(pDrawWidget != NULL)
    {
        connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }

    // qDebug() << "RRRR BEFORE";
    // if (pDrawWidget)
    //fboWrapper=pDrawWidget->initFboWrapper();
    //qDebug() << "RRRR AFTER";
}

void DrawElement::copy(DrawElement *elm)
{
    lifeTime = elm->getLifeTime();
    tickTime = elm->getTickTime();
    startDrawTime = elm->getStartDrawTime();
    x = elm->getX();
    y = elm->getY();
    z = elm->getZ();
    width = elm->getSize().width();
    height = elm->getSize().height();
    rotationAngle = elm->rotationAngle;
    //typeId = elm->getTypeId();
}

DrawElement::~DrawElement()
{


    qDebug() << "delete DrawElement";
    if(pDrawWidget != NULL)
    {
        pDrawWidget->deleteFBO(fboWrapper);
        disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }
    if(group_wich_el_belong != NULL)
    {
        void *gr_temp = group_wich_el_belong;
        group_wich_el_belong->deInitGroupBlocks();
        delete gr_temp;
    }
    qDebug() << "delete end";
}

void DrawElement::setAnimStateTime(AnimStateTime value)
{
    anim_state_time = value;
}

void DrawElement::setAnimStateTime(int stat, int tim)
{
    //setAnimStateTime(AnimStateTime(stat,tim));
    setAnimState(stat);
    setAnimTime(tim);
    qDebug() << "DrawElement::setAnimStateTime = " << tim;
}

void DrawElement::setAnimStateTime(QPoint pp)
{
    setAnimStateTime(pp.x(), pp.y());
}

void DrawElement::setAnimState(int value)
{
    anim_state_time.state = value;
    effects.clear();
    effects = ShaderEffect::creatEffectByNum(value, anim_state_time.time);
    for (int i = 0; i <effects.length(); i++)
        effects[i].setShaderWrapper(pDrawWidget->getShaderPrograms()[effects[i].getShaderWrapperIndex()]);
}

int DrawElement::useAnimTime()
{
    return use_anim_time;
}

void DrawElement::setUseAnimTime(int value)
{
    use_anim_time = value;
}

void DrawElement::setAnimTime(int value)
{
    if (value > this->getLifeTime())
        value = this->getLifeTime();
    anim_state_time.time = value;
    effects.clear();
    effects = ShaderEffect::creatEffectByNum(anim_state_time.state, value);
    for (int i = 0; i <effects.length(); i++)
        effects[i].setShaderWrapper(pDrawWidget->getShaderPrograms()[effects[i].getShaderWrapperIndex()]);
    qDebug() << "DrawElement::setAnimTime(int value) " << anim_state_time.time;
}

QPoint DrawElement::getAnimStateTimePoint()
{
    return QPoint(anim_state_time.state, anim_state_time.time);
}

AnimStateTime DrawElement::getAnimStateTime()
{
    return anim_state_time;
}


void DrawElement::paint()
{

    //  qDebug() << "paint on buffer:"<<fboWrapper.frameBuffer;
    /*if (pDrawWidget->getTimeLine()->getPlayTime() >= lifeTime + startDrawTime)
        return;*/
int toX=0;
int toY=0;

shaderAngle = 0;
shaderScaleX = 1;
shaderScaleY = 1;
xDelta=0;
yDelta=0;

bool isMoveTo = false;
    if(fboWrapper.errorStatus == 0)
    {
        bool drawToSecondBuffer = true;
        //DONT REMOVE ShaderEffect mainEffect(pDrawWidget->getTestShader());
        //DONT REMOVE effects.push_back(mainEffect);
        // bool currentDrawToSecondBuffer=false;
        int effectsUsedInOneTime=0;

        // ShaderEffect testShaderEffect(pDrawWidget->getTestShader());
        //testShaderEffect.setEffectTimeHowLong(5000);
        // effects.push_back(testShaderEffect);
        if (!effects.isEmpty())
        {
            /* if (effects.length()%2==1)
            {
                drawToSecondBuffer=true;
                //pDrawWidget->clearFrameBuffer(pDrawWidget->getPingPongFBO());
                //pDrawWidget->clearFrameBuffer(pDrawWidget->getMainFBO());
            }*/
            int playTime = pDrawWidget->getTimeLine()->getPlayTime();
            //TO BE REMOVED IN RELEASE

            //

            //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND );

            for (int i=0;i<effects.length();i++)
            {
                isMoveTo = false;
                int beginAtTime;
                if(!effects[i].getAnchorToEnd())
                    beginAtTime = effects[i].getStartTimeMS()+ startDrawTime ;
                else
                {
                    beginAtTime = lifeTime + startDrawTime - effects[i].getEffectTimeHowLong();
                    if (beginAtTime<0)
                        beginAtTime=0;

                }
                //  beginAtTime = effects[i].getStartTimeMS()+ startDrawTime ;
                //if (beginAtTime<0)beginAtTime=0;

                int endAtTime = beginAtTime + effects[i].getEffectTimeHowLong();
                float keyFrame = 1;
                //   qDebug() << ":"<<playTime-beginAtTime;


               // if ((((playTime >= beginAtTime && playTime <= endAtTime))))//endAtTime + 50 if flickering !!! @BAG@//NICOLAS problem with animation in last ms

                if(playTime > 0)
                {
                    bool shaderUsed = false;
                    if(endAtTime-beginAtTime > 0)
                    {
                        keyFrame=(float)(playTime-beginAtTime)/(endAtTime-beginAtTime);
                    }

                    if(keyFrame > 1)
                        keyFrame = 1;
                    ShaderProgramWrapper *shaderWrapper = effects[i].getShaderWrapper();
                    if (shaderWrapper!=NULL)
                    {
                         shaderUsed=true;
                    pDrawWidget->useShader(shaderWrapper);

                    effects[i].setUniform("animationKey",keyFrame);
                    effects[i].setUniform("resolution",fboWrapper.tWidth,fboWrapper.tHeight);
                    effects[i].setUniform("reverse",effects[i].getReverse());
                    effects[i].setUniform("count",effects[i].getCount());
                    effects[i].setUniform("elementSize",effects[i].getElementSize());
                    }
                     // qDebug() <<i<< "-b:"<<beginAtTime;
                     //qDebug() << i<<"-keyFrame:"<<keyFrame;
                    if (effects[i].getRotateAngle()!=0)
                     shaderAngle += effects[i].getRotateAngle()*keyFrame;
                    if (effects[i].getMoving())isMoveTo=true;
                    toX=effects[i].getToPosX();
                    toY=effects[i].getToPosY();
                    shaderScaleX += (effects[i].getToScaleX() - shaderScaleX)*keyFrame;
                    shaderScaleY += (effects[i].getToScaleY() - shaderScaleY)*keyFrame;
                    if (isMoveTo){
                        xDelta +=(toX-(x + xDelta))*keyFrame;
                        yDelta +=(toY-(y + yDelta))*keyFrame;
                    }

                    if(drawToSecondBuffer)
                    {
                        pDrawWidget->bindBuffer(pDrawWidget->getPingPongFBO().frameBuffer);
                        pDrawWidget->clearFrameBuffer(pDrawWidget->getPingPongFBO());
                        // qDebug() << "Shader program ("<<i<<"):"<<effects[i].getShaderWrapper()->getShaderProgram();

                        //  float keyFrame = (float)(pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)/lifeTime;//MOVE UP LATER


                        if (effectsUsedInOneTime==0)
                            draw();
                        else
                            pDrawWidget->drawTexture(0,0,fboWrapper.tWidth,fboWrapper.tHeight,
                                                     fboWrapper.bindedTexture,0,1,1,z );
                    }
                    else
                    {
                        // qDebug()<<"drawToFirstBuffer:"<<fboWrapper.frameBuffer;
                        pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
                        pDrawWidget->clearFrameBuffer(fboWrapper);
                        // float keyFrame = (float)(pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)/lifeTime;//MOVE UP LATER
                        if (effectsUsedInOneTime==0)
                            draw();
                        else
                            pDrawWidget->drawTexture(0,0,pDrawWidget->getPingPongFBO().tWidth,
                                                     pDrawWidget->getPingPongFBO().tHeight,
                                                     pDrawWidget->getPingPongFBO().bindedTexture,0,1,1,z );
                    }
                     if (shaderUsed)
                    pDrawWidget->useShader(0);
                    effectsUsedInOneTime++;
                    drawToSecondBuffer=!drawToSecondBuffer;
                }
            }

            //qDebug()<<"before remove temp effect";
            //remove test effect
            //effects.removeAt(effects.length()-1);

            pDrawWidget->disableShader();

            if (effectsUsedInOneTime==0){
                //qDebug() << "if (effectsUsedInOneTime==0)";
                pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
                draw();//Draw original image one time without any effects

            }
            else
                if (!drawToSecondBuffer)
                {
                    // qDebug() << "draw to first buffer forcly";
                    pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
                    pDrawWidget->clearFrameBuffer(fboWrapper);
                    // float keyFrame = (float)(pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)/lifeTime;//MOVE UP LATER

                    pDrawWidget->drawTexture(0,0,pDrawWidget->getPingPongFBO().tWidth,
                                             pDrawWidget->getPingPongFBO().tHeight,
                                             pDrawWidget->getPingPongFBO().bindedTexture,0,1,1,z );

                }

            pDrawWidget->enableShader();
        }
        if (effects.isEmpty()){ //&& effectsUsedInOneTime==0){
            {
                //qDebug() << "if (effects.isEmpty()";
                pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
                draw();//Draw original image one time without any effects
                //qDebug() << "EFFECTS EMPTY !!!";
            }
        }
        /*
        //NEWNEWNEWNEWNEWNENWNENWNENWNENWNENWNENW
                pDrawWidget->bindBuffer(pDrawWidget->getPingPongFBO().frameBuffer);
               // qDebug() << "Shader program ("<<i<<"):"<<effects[i].getShaderWrapper()->getShaderProgram();
                pDrawWidget->useShader(pDrawWidget->getTestShader());
                //pDrawWidget->useShader(0);

                pDrawWidget->drawTexture(0,0,fboWrapper.tWidth,fboWrapper.tHeight,
                                            fboWrapper.bindedTexture,0,1,1,z );
               // pDrawWidget->useShader(0);

                pDrawWidget->bindBuffer(pDrawWidget->getMainFBO().frameBuffer);
                pDrawWidget->drawTexture(0,0,pDrawWidget->getPingPongFBO().tWidth,
                pDrawWidget->getPingPongFBO().tHeight,
                pDrawWidget->getPingPongFBO().bindedTexture,0,1,1,z );
       //NEWNEWNEWNEWNEWNENWNENWNENWNENWNENWNENW
*/
        //pDrawWidget->getOglFuncs()->glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
        // pDrawWidget->bindBuffer(0);
        //qDebug() << "MAIN FBO:"<<pDrawWidget->getMainFBO().frameBuffer;
        pDrawWidget->bindBuffer(pDrawWidget->getMainFBO().frameBuffer);

        //pDrawWidget->useShader(0);

        /* if(aspectRatio)
        {
            if (width>height)
            pDrawWidget->paintBufferOnScreen(fboWrapper,x, y, width, width, z);
            else pDrawWidget->paintBufferOnScreen(fboWrapper,x, y, height, height, z);
        }
        else*/


        pDrawWidget->paintBufferOnScreen(fboWrapper,x+xDelta, y+yDelta, width, height, z, rotationAngle+shaderAngle,  shaderScaleX, shaderScaleY);
        // pDrawWidget->context()->functions()->glUseProgram(0);
    }
    else
        qWarning() << "In curent draw element fboWraper is not init!!!";
}

int DrawElement::getBlockIndex() const
{
    return blockIndex;
}

void DrawElement::setBlockIndex(int value)
{
    blockIndex = value;
}

int DrawElement::getBlockColumn() const
{
    return blockColumn;
}

void DrawElement::setBlockColumn(int value)
{
    blockColumn = value;
}

Group *DrawElement::getGroupWichElBelong() const
{
    return group_wich_el_belong;
}

void DrawElement::setGroupWichElBelong(Group *value)
{
    group_wich_el_belong = value;
    // qDebug() << "OOOOOOOOOOOOOOOO group_wich_el_belong = " << group_wich_el_belong;
}

QString DrawElement::getBlockBorderColor() const
{
    return block_border_color;
}

void DrawElement::setBlockBorderColor(const QString &value)
{
    block_border_color = value;
    emit borderColorChangedSignal(blockColumn, blockIndex, block_border_color);//@BAG@COLUM not init
    //emit borderColorChangedSignal(blockColumn,blockIndex,block_border_color);
}

int DrawElement::getPlayTimeUntilFreeze() const
{
    qDebug() <<"getPlayTimeUntilFreeze:"<<playTimeUntilFreeze;
    return playTimeUntilFreeze;
}

void DrawElement::setPlayTimeUntilFreeze(int value, bool emit_value)
{
    qDebug() << "setPlayTimeUntilFreeze:"<<value;
    if (value > lifeTime)
        value = lifeTime;
    playTimeUntilFreeze = value;
    if (emit_value)
        emit playTimeUntilFreezeChangeSignal(this->blockColumn,blockIndex,value);
}

float DrawElement::getBorder() const
{
    return border;
}

void DrawElement::setBorder(float value)
{
    border = value;
}

int DrawElement::getRotationAngle() const
{
    return rotationAngle;
}

void DrawElement::setRotationAngle(int value)
{
    rotationAngle = value;
}
void DrawElement::draw()
{
    
}

QVector<ShaderEffect> DrawElement::getEffects()
{
    return effects;
}
DrawElement::setEffects(QVector<ShaderEffect> effects)
{
    this->effects=effects;
}
DrawElement::addEffect(ShaderEffect effect)
{
    effects.push_back(effect);
}
DrawElement::clearEffects()
{
    effects.clear();
}


FBOWrapper DrawElement::getFBOWrapper()
{
    return fboWrapper;
}

DrawElement::setFBOWrapper(FBOWrapper wrapper)
{
    this->fboWrapper=wrapper;
}

bool DrawElement::load(QString path)
{
    QFile appFile(path);
    if(!appFile.exists())
        return false;
    //lastPath = path; //@BUG@09/09/NicolasFix
    appFile.open(QFile::ReadOnly);
    this->load(&appFile, path, VERSION);
    appFile.close();

}

bool DrawElement::load(QIODevice* device, QString projectName, float version)
{
    /*QDataStream stream(device);

    int temp_type;
    stream >> temp_type  >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
   typeId = static_cast<Element_type>(temp_type);
    icon = load_image(stream);
    load_add(stream);*/
    loadTypeId(device);
    loadRest(device, projectName, version);
}
bool DrawElement::loadTypeId(QIODevice* device)
{
    QDataStream stream(device);
    int temp_type;
    stream >> temp_type  ;

    // typeId = static_cast<Element_type>(temp_type);
    Element_type temp_2 ;
    temp_2 = (Element_type)(temp_type);
    setTypeId(temp_2);
    qDebug() << "DrawElement::load temp_type = " << getTypeId();

}
bool DrawElement::loadRest(QIODevice* device, QString projectName, float version)
{
    //qDebug() << "load rest begin";
    QDataStream stream(device);
    stream  >> key ;
    if (version > 3.00008)
        stream.readRawData((char*)&lifeTime, sizeof(quint64));
    else
    {
        int temp_time ;
        stream >> temp_time;
        lifeTime = temp_time;
    }
    stream >> tickTime;
    if (version > 3.00008)
        stream.readRawData((char*)&startDrawTime, sizeof(quint64));
    else
    {
        int temp_time ;
        stream.readRawData((char*)&temp_time, sizeof(int));
        // stream >>
        startDrawTime = temp_time ;
    }
    stream >> x >> y >> z >>
            width >> height >> keyCouter>> blockIndex >> blockColumn;
    //if (typeId == Element_type::Image)
    icon = load_image(stream);

    int effectsLength = 0;
    stream >> anim_state_time.state >>  anim_state_time.time;
    stream >> effectsLength;
    if(version > 2.94)
    {
        stream >> playTimeUntilFreeze;
        setPlayTimeUntilFreeze(playTimeUntilFreeze);
    }
    //qDebug() << "effectsLength:"<<effectsLength;
    effects.clear();
    effects.resize(effectsLength);

    /* load_add(stream);
=======


    load_add(stream);
>>>>>>> origin/Time_line_lastGood
    //qDebug() << "load add";
    int effectsLength = 0;
    stream >> effectsLength;
    //qDebug() << "effectsLength:"<<effectsLength;*/

    for (int i = 0 ; i < effectsLength;i++)
    {
        effects[i].load(stream, version);
    }

    if(version > 3.0008) // >3.001 - float feature
    {
        stream >> use_anim_time;
    }
    if(version > 3.2)
    {
        stream >> rotationAngle;
    }
    // qDebug() << "load rest end";
    load_add(stream, projectName, version);
    // qDebug() << "load add";

}

bool DrawElement::save(QIODevice* device, QString projectName, QProgressBar *bar) //-=-=-=
{
    QDataStream stream(device);

    int temp_type = static_cast<int>(typeId);
    int resultStatus=0;
    if (typeId != Element_type::Empty)
        qDebug() << "DrawElement::save playTimeUntilFreeze = " << playTimeUntilFreeze;
    stream << temp_type << key ;
    stream.writeRawData((char*)&lifeTime, sizeof(quint64));
    stream   << tickTime ;
    stream.writeRawData((char*)&startDrawTime, sizeof(quint64));
    stream << x << y << z
           << width << height << keyCouter << blockIndex << blockColumn;
    //if (typeId == Element_type::Image)
    //save_image(stream, icon);
    // qDebug() << "qwewqewqeqewqQQQQ  " << lastPath;
    if (!lastPath.isEmpty())
        resultStatus = save_image(stream,lastPath);
    else
        save_image(stream, icon );

    stream << anim_state_time.state <<  anim_state_time.time;
    stream << effects.length();
    stream << playTimeUntilFreeze;

    for (int i = 0 ; i < effects.length();i++)
        effects[i].save(stream,VERSION);

    stream << use_anim_time << rotationAngle;

    save_add(stream, projectName);
    if(bar != NULL)
    {
        bar->setValue(bar->value() + 1);
        qApp->processEvents();
    }

    //stream << border;
}

bool DrawElement::save(QString path)
{
    QFile appFile(QString(path + "." + type));
    appFile.open(QFile::WriteOnly);
    this->save(&appFile,NULL, NULL);
    appFile.close();
    /*QImage icon;
    int lifeTime;
    int tickTime;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;

    OGLWidget *pDrawWidget;
    bool bPause;
    */

}

void DrawElement::clear()
{

}

bool DrawElement::reloadLastDone()
{
    if(lastPath.isNull())
        return false;
    QByteArray ba;
    QDataStream stream( &ba, QIODevice::ReadWrite );
    //qDebug() << "MY1" << lifeTime;
    stream << key << lifeTime << tickTime << startDrawTime << x << y << z << width << height << keyCouter;
    stream.device()->reset();
    load(lastPath);
    stream >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
    //qDebug() << "MY2" << lifeTime;
}

void DrawElement::setLastPath(QString path)
{
    lastPath=path;
}

QRect DrawElement::getRect()
{
    return QRect(x, y, width, height);
}

void DrawElement::setPosition(QPoint pos)
{
    x = pos.x();
    y = pos.y();
}

DrawElement* DrawElement::getCopy(QObject parentamana)
{
    /* switch(typeId)
     {
     case Element_type::Image :
     //6666666677777777
          DrawImageElm *elm = new DrawImageElm(drawWidget, parent);
          elm->load(path);
                 elm->setTypeId(Element_type::Image);
                 elm->setKey(target.baseName());
          return (DrawElement*) elm;
     break;
     case Element_type::Text

     }
      DrawElement *elm = new DrawElement(drawWidget, parentamana);

     return (DrawElement) this; //777777
     */
    DrawElement *elm;
    memcpy(elm, this,sizeof(DrawElement));
    return elm;
}

void DrawElement::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void DrawElement::setDelay(int d)
{
    delay=d;
}

void DrawElement::setSize(QSize pos)
{
    setSize(pos.width(), pos.height());
}

void DrawElement::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void DrawElement::setRect(QRect rect)
{
    x = rect.x();
    y = rect.y();
    width = rect.width();
    height = rect.height();
}

void DrawElement::setRect(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
int DrawElement::getX() const
{
    return x;
}

void DrawElement::setX(int value)
{
    x = value;
}

int DrawElement::getY() const
{
    return y;
}

void DrawElement::setY(int value)
{
    y = value;
}

int DrawElement::getZ() const
{
    return z;
}

void DrawElement::setZ(int value)
{
    z = value;
}

quint64 DrawElement::getLifeTime()
{
    return lifeTime;
}



void DrawElement::setShowTextCursor(bool value)
{
    show_text_cursor = value;
}

bool DrawElement::getShowTextCursor()
{
    return show_text_cursor;
}

quint64 DrawElement::setLifeTime(quint64 value, bool feedBack, bool visual,bool use_value)
{
    //qDebug() << "DrawElement::setLifeTime value = "<< value;

    if (this->getTypeId() !=Element_type::Empty)
        if (value < minBlockTime)
            return -1;
    /*else
            if (value < 0)
                return -1;*/

    if (use_value)
        emit dontUseThisValue();
    /*if (typeId == Text)
    {
        DrawTextElm *tempo = (DrawTextElm*) this;
        tempo->setBNeedTime(false);
    }*/

    lifeTime = value;
    /*if(group_wich_el_belong != NULL)
        group_wich_el_belong->calcBoundRec();
    */
    if(feedBack)
    {
        emit sizeChangedSignal(blockColumn, blockIndex, value, visual);
        /*  qDebug() << "emit sizeChangedSignal(blockColumn = " <<blockColumn<<
                 "blockIndex = " <<  blockIndex << " value = " << value << " visual = " << visual;  //work
        */

    }
    return value;
}

quint64 DrawElement::getStartDrawTime() const
{
    return startDrawTime;
}

quint64 DrawElement::setStartDraw(quint64 value)
{
    startDrawTime = value;
    return value;
    /*if(group_wich_el_belong != NULL)
        group_wich_el_belong->calcBoundRec();*/
}

QImage DrawElement::getIcon() const
{
    return icon;
}

void DrawElement::setIcon(const QImage &value)
{
    icon = value;
    //icon = QImage("E:/картинки/Фото0051.jpg");
}

bool DrawElement::getPause() const
{
    return bPause;
}

void DrawElement::setPause(bool value)
{
    bPause = value;
}

void DrawElement::setType(const char name[])
{
    strcpy(type, name);
}

QString DrawElement::getType()
{
    return QString(type);
}

void DrawElement::setTypeId( Element_type val)
{
    typeId = val;
}

Element_type DrawElement::getTypeId()
{
    return this->typeId;
}

void DrawElement::pause()
{
    bPause = true;
}

void DrawElement::stop()
{
    ////qDebug() << "stop";
    bPause = false;
    keyCouter = 0;
    bPause = false;
    tickTimer.restart();
}

void DrawElement::start()
{
    if (!bPause)
        keyCouter = 0;
    bPause = false;

    /*
     * NOT NEED SLOW
     *
     * reloadLastDone();
     *
     */


    //qDebug() << "START" << lastPath;
}

void DrawElement::restart()
{
    keyCouter = 0;
    tickTimer.restart();
}

bool DrawElement::load_add(QDataStream &stream, QString projectPATH, float version)
{

}

bool DrawElement::save_add( QDataStream &stream, QString projectPATH)
{

}

bool DrawElement::save_image(QDataStream &stream, QImage img)
{
    stream << img.size().width() << img.size().height() << (int)img.format();

    QByteArray ba;
    QBuffer buffer(&ba); // QBuffer inherits QIODevice
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer,"PNG", 100);

    buffer.close();
    stream << ba.length() << ba;
    //stream.writeRawData((const char*)img.bits(), img.byteCount());
    qDebug() <<"image saved:"<<img.byteCount();
}


bool DrawElement::save_image(QDataStream &stream, QString filePath)
{
    stream << (int)0 << (int)0 << (int)0;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    if (filePath.isEmpty())
    {
        stream << 0;//0 bytes of image;
        return -1;

    }
    QByteArray ba = file.readAll();

    stream << ba.length() << ba;
    file.close();
    qDebug() << "SAVE_IMAGE";
    //stream.writeRawData((const char*)img.bits(), img.byteCount());
    //qDebug() <<"image saved:"<<img.byteCount();
}

QMovie *DrawElement::load_Movie(QDataStream &stream)
{
    int w, h, format;
    stream >> w >> h >> format;
    QByteArray ba;
    int baLength=0;
    stream >> baLength;
    stream >> ba;
    QMovie *mov;
    QBuffer buffer(&ba); // QBuffer inherits QIODevice
    buffer.open(QIODevice::ReadOnly);
    mov = new QMovie(&buffer, ba);
    //img_temp.load(&buffer,"PNG");

    buffer.close();
    //stream.readRawData((char*)img_temp.bits(), img_temp.byteCount());
    return mov;
}

QImage DrawElement::load_image(QDataStream &stream)
{
    int w, h, format;
    stream >> w >> h >> format;
    QByteArray ba;
    int baLength=0;
    stream >> baLength;
    stream >> ba;
    QImage img_temp(w, h, (QImage::Format)format);
    img_temp.loadFromData(ba);

    //stream.readRawData((char*)img_temp.bits(), img_temp.byteCount());
    return img_temp;
}


int DrawElement::getTickTime() const
{
    return tickTime;
}

void DrawElement::setTickTime(int value)
{
    tickTime = value;
    // //qDebug()<<"tickTime3:"<<tickTime;
}

QSize  DrawElement::getSize()
{
    return QSize(width,height);
}



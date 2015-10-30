#include "drawbrush.h"
#include "../TimeLine/listcontroll.h"

DrawBrushElm::DrawBrushElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    //add first group of points;
    // QVector<QPoint>  qPoints;
    //coordGroup.append(qPoints);
    
    //QVector<BrushBeginingIndex> brushBeginings;
    //brushBeginingIndexes.append(brushBeginings);
    setType("");
    setTypeId(Element_type::Brushh);
}



QVector<QPoint> DrawBrushElm::getCoords()
{
    return coords;
}
QVector<BrushBeginingIndex> DrawBrushElm::getBrushes(){
    return brushes;
}

bool DrawBrushElm::load_add(QDataStream &stream, QString projectPATH, float version)
{
    clear();
    QVector<QImage> images;
    QVector<int> imagesIndexed;
    stream >> coords;
    //qDebug()<<"LOADED coords len:"<<coords.length();//<<" values:"<<coords[0]<<" "<<coords[1];
    /*for (QPoint coord : coords)
     {
         //qDebug() <<"Point:"<<coord;
     }*/
    int brushCount = 0;
    stream >> brushCount;
    int imgBrushCount = 0;
    stream >>  imgBrushCount;
    QByteArray arr;
    for (int i = 0 ;i< imgBrushCount; i++) {
        int index = 0;
        stream >> index;
        imagesIndexed.push_back(index);
        images.push_back(load_image(stream));
        
    }
    //qDebug() <<"imagesIndexed:"<<imagesIndexed.toList();
    qDebug() << "load brushes:"<<imgBrushCount;
    for (int i = 0; i <brushCount;i++)
    {
        BrushBeginingIndex brushBeginingIndex;
        Brush data;
        //stream >> data.patchToImage;
        // data.img = load_image(stream );
        
        // data.img=load_image(stream);
        //data.color_img=load_image(stream);
        stream  >> data.size >> data.opacity >> data.blur >> data.color_main >> data.dispers >>
                data.delta_count >> data.count >> data.size_delta >> data.angle_delta >> data.afinn;
        stream >> data.imageIndex >> brushBeginingIndex.pointIndex;
        qDebug() << "loaded:"<< data.size << data.opacity << data.blur << data.color_main << data.dispers <<
                    data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn<< data.imageIndex << brushBeginingIndex.pointIndex;
        /*if (data.imageIndex==-1){
            data.img = QImage(1,1,QImage::Format_ARGB32_Premultiplied);
            data.img.fill(Qt::black);
            //data.color_img = BrushPainter::getInstance()->applyColor(data);
            if (pDrawWidget!=NULL && pDrawWidget->isShaderSupported())
                 data.color_img = data.img;
            else
             data.color_img = BrushPainter::getInstance()->applyColor(data);
            //qDebug() <<"DEFAULT INDEX";
        }
        else*/
        for (int j = 0 ; j < imagesIndexed.length();j++)
        {
            if (data.imageIndex==imagesIndexed[j])
            {
                qDebug() << "imagesIndexed["<<j<<"]==data.imageIndex:"
                         <<imagesIndexed[j]<<"=="<<data.imageIndex;
                data.img = images[j];
                // data.color_img = BrushPainter::getInstance()->applyColor(data);
                /*
        if (pDrawWidget!=NULL && pDrawWidget->isShaderSupported())
             data.color_img = data.img;
        else
         data.color_img = BrushPainter::getInstance()->applyColor(data);
         */
                
            }
        }
        brushBeginingIndex.brush=data;
        brushes.push_back(brushBeginingIndex);
    }
    
    if(coords.size() > 0)
        tickTime = playTimeUntilFreeze/coords.size();
}
bool DrawBrushElm::setDrawWidget(OGLWidget *value){

    if(value == pDrawWidget && value != NULL)
    {
        //  qDebug() << "VALUE  " << fboWrapper.errorStatus;
        if(renderFbo.errorStatus != 0 &&  pDrawWidget->isInit()){
            renderFbo = pDrawWidget->initFboWrapper(pDrawWidget->getWax(),pDrawWidget->getWay());//TODO
        return false;
        }
    }

    if (!DrawElement::setDrawWidget(value))
    {
       return false;
    }

    for (int i=0;i<brushes.length();i++)
    {
        if (pDrawWidget!=NULL && pDrawWidget->isShaderSupported())
            brushes[i].brush.color_img = brushes[i].brush.img;
        else
            brushes[i].brush.color_img = BrushPainter::getInstance()->applyColor(brushes[i].brush);
    }
    return true;
    
}

bool DrawBrushElm::save_add(QDataStream &stream, QString projectPATH)
{
    //QVector<QImage> brushImages;
    stream << coords;
    stream << brushes.length();
    QSet<int> usedImageIndexes;

    for (BrushBeginingIndex brushI : brushes)
    {
        if (brushI.brush.imageIndex!=-1)
            usedImageIndexes.insert(brushI.brush.imageIndex);
    }
    int usedImageIndexesCount=usedImageIndexes.size();

    qDebug() << "save usedImageIndexes:"<<usedImageIndexesCount;
    
    //pDrawWidget->m_manager;
    QString path = "\\Preset\\Brushes";
    QString new_path =  pDrawWidget->m_manager.getBrushDir().currentPath()+path;
    //QDir dir(new_path);
    // pDrawWidget->m_manager.brushPathsList
    if(!pDrawWidget->m_manager.brushPathsList.isEmpty())
    {
        stream << usedImageIndexesCount;
    for(int i = 0; i < usedImageIndexesCount; i++)
    {
        int brushImageIndex = usedImageIndexes.values()[i];
        //qDebug() << "new_path:"<<new_path + "\\" + usedImageIndexes.values()[i];

        //brushImages.push_back();
        stream <<usedImageIndexes.values()[i];
        int resultStatus = 0;
        qDebug() << "last path:"<<lastPath;
        if (!lastPath.isEmpty() && QFile::exists(lastPath))
        {
            qDebug()<<"save img using link begin";
            resultStatus = save_image(stream,lastPath);
            qDebug()<<"save img using link end";
        }
        else
        {
            qDebug() << "last path is empty";

            QString pathOfImage;
           pathOfImage=new_path + "\\" + pDrawWidget->m_manager.brushPathsList[brushImageIndex];
            if(QFile::exists(pathOfImage))
            {
                qDebug()<<"file excist in library";
             QImage img = QImage(pathOfImage);
            save_image(stream, img );
            }
            else{
                qDebug() << "path is not excist";
                save_image(stream, brushes[brushImageIndex].brush.img );
            }
        }
        qDebug() << "end of save image";
    }
    }
    else
    {
        stream << brushes.count();
        qDebug() << "use img without path";
        for(int i = 0; i < brushes.count(); i++)
         {
            stream << brushes[i].brush.imageIndex;
             save_image(stream, brushes[i].brush.img);
         }
    }
    
    for (BrushBeginingIndex &brushBeginingIndex : brushes)
    {
        Brush &data = brushBeginingIndex.brush;
        //qDebug()<<"before save_image";
        //save_image(stream, data.img );
        //save_image(stream,data.color_img);
        //qDebug()<<"save_image";
        stream  << data.size << data.opacity << data.blur << data.color_main << data.dispers <<
                   data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn;
        stream << data.imageIndex << brushBeginingIndex.pointIndex;
        qDebug() << "saved:"<< data.size << data.opacity << data.blur << data.color_main << data.dispers <<
                    data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn<< data.imageIndex << brushBeginingIndex.pointIndex;
    }
    
    
}





void DrawBrushElm::addCoord(int x, int y)
{
    QPoint pt;
    pt.setX(x);
    pt.setY(y);
    coords.append(pt);
}

void DrawBrushElm::addCoord( QPoint pt)
{
    coords.append(pt);
}

void DrawBrushElm::clear()
{
    coords.clear();
    brushes.clear();
}
void DrawBrushElm::setLifeTime(int value, bool feedBack, bool visual)
{
    DrawElement::setLifeTime(value, feedBack, visual);
    if(feedBack)
        return;

    if(coords.size() > 0)
        tickTime = playTimeUntilFreeze/coords.size();
}
void DrawBrushElm::draw()
{
    //    //qDebug() << tickTimer.elapsed() << "  " << tickTime;
    
    
    
    int current_time = pDrawWidget->getTimeLine()->getPlayTime();
    
    if (current_time > 0)
    {
        int realKeyValue = qCeil((double)((current_time-startDrawTime)*coords.size()/playTimeUntilFreeze));
        // qDebug() << "QQQQQQQQQQQQQQQQQQQQ" << keyCouter;
        if(keyCouter == 0)
        {
            //qDebug()<<"CLEAR FRAME BUFFER";
            pDrawWidget->clearFrameBuffer(renderFbo);
            pDrawWidget->clearFrameBuffer(fboWrapper);
        }
        //qDebug() << "coords.size():"<<coords.size();
        
         /*qDebug() << "lifeTime:"<<lifeTime;
         qDebug() << "startDrawTime:"<<startDrawTime;
         qDebug() << "current_time:"<<current_time;
         qDebug() << "realKeyValue:"<<realKeyValue;
        qDebug() << "keyCouter:"<<keyCouter;*/
        //qDebug() << "fbo wrapper:"<<fboWrapper.frameBuffer;
        //qDebug() << "pDrawWidget->paintBrushInBuffer" << coords.size();
        while(keyCouter < realKeyValue)
        {
            if (keyCouter < coords.size() )
            {
                GLint curentBuff;
                glGetIntegerv(GL_FRAMEBUFFER_BINDING, &curentBuff);

                pDrawWidget->paintBrushInBuffer(currentTexture,brush, renderFbo, coords,brushes, keyCouter);
                // pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
                pDrawWidget->bindBuffer(curentBuff);
                pDrawWidget->clearFrameBuffer(curentBuff);
                //qDebug() << "CORRECT BUFFER:"<<curentBuff;
                pDrawWidget->drawTexture(0,0,renderFbo.tWidth, renderFbo.tHeight,
                                         renderFbo.bindedTexture, 0, 1, 1, z );

            }
            keyCouter++;
            //fboWrapper
        }
        // pDrawWidget->paintBufferOnScreen(pDrawWidget->getMainFBO(),x, y, width, height, z);
    }
    
    
}

/*QDataStream &operator << ( QDataStream &st, const Brush &data )
{
  st << data.img << data.color_img << data.size << data.opacity << data.blur << data.color_main << data.dispers <<
          data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn;
          
  return st;
}

QDataStream &operator >> ( QDataStream &st, Brush &data )
{
    st >> data.img >> data.color_img >> data.size >> data.opacity >> data.blur >> data.color_main >> data.dispers >>
            data.delta_count >> data.count >> data.size_delta >> data.angle_delta >> data.afinn;
}

QDataStream &operator << ( QDataStream &st, const BrushBeginingIndex &data )
{
  st  << data.brush << data.pointIndex;
  
  return st;
}

QDataStream &operator >> ( QDataStream &st, BrushBeginingIndex &data )
{
     st  >> data.brush >> data.pointIndex;
}
*/
void DrawBrushElm::addBrush(Brush brush)
{
    //qDebug() << "brushes.length():"<<brushes.length();
    // if (brushes==NULL)return;
    for (int i=0;i<brushes.length();i++){
        // //qDebug() << "i:"<<i;
        //qDebug() << "pointIndex         :   "<<brushes[i].pointIndex;
        //qDebug() << "coords.length()          :   "<<coords.length();
        // if (i==0) continue;
        
        if (brushes[i].pointIndex==coords.length()){
            brushes[i].brush=brush;
            //qDebug () << "BRUSH ALREADY EXCIST:"<<i;
            return;
            
        }
    }
    BrushBeginingIndex beginIndex;
    beginIndex.brush=brush;
    beginIndex.pointIndex=coords.length();
    //qDebug() << "before append";
    brushes.append(beginIndex);
    //qDebug() << "after append";
}




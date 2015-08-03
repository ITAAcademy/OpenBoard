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
}



QVector<QPoint> DrawBrushElm::getCoords()
{
    return coords;
}
QVector<BrushBeginingIndex> DrawBrushElm::getBrushes(){
    return brushes;
}

bool DrawBrushElm::load_add(QDataStream &stream)
{
     clear();
     QVector<QImage> images;
     QVector<int> imagesIndexed;
     stream >> coords;
     qDebug()<<"LOADED coords len:"<<coords.length();//<<" values:"<<coords[0]<<" "<<coords[1];
     /*for (QPoint coord : coords)
     {
         qDebug() <<"Point:"<<coord;
     }*/
     int brushCount = 0;
    stream >> brushCount;
    int imgBrushCount = 0;
           stream >>  imgBrushCount;

           for (int i = 0 ;i< imgBrushCount; i++) {
               int index = 0;
               stream >> index;
               imagesIndexed.push_back(index);
               images.push_back(load_image(stream));
           }
            qDebug() <<"imagesIndexed:"<<imagesIndexed.toList();
     qDebug() << "load brushes:"<<brushCount;
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
        if (data.imageIndex==-1){
            data.img = QImage();
            data.color_img = BrushPainter::getInstance()->applyColor(data);
        }
        else
        for (int j = 0 ; j < imagesIndexed.length();j++)
        {
            if (data.imageIndex==imagesIndexed[j])
            {
                qDebug() << "imagesIndexed["<<j<<"]==data.imageIndex:"
                         <<imagesIndexed[j]<<"=="<<data.imageIndex;
        data.img = images[j];
        data.color_img = BrushPainter::getInstance()->applyColor(data);

            }
                }
        brushBeginingIndex.brush=data;
        brushes.push_back(brushBeginingIndex);
    }

    if(coords.size() != 0)
        tickTime = lifeTime/coords.size();
}

bool DrawBrushElm::save_add(QDataStream &stream)
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
 stream << usedImageIndexesCount;
 qDebug() << "save usedImageIndexes:"<<usedImageIndexesCount;

 //pDrawWidget->m_manager;
 QString path = "\\Preset\\Brushes";
         QString new_path =  pDrawWidget->m_manager.getBrushDir().currentPath()+path;
         QDir dir(new_path);
        // pDrawWidget->m_manager.brushPathsList
         for(int i = 0; i < usedImageIndexesCount; i++)
         {
             int brushImageIndex = usedImageIndexes.values()[i];
             qDebug() << "new_path:"<<new_path + "\\" + usedImageIndexes.values()[i];
            QImage img = QImage(new_path + "\\" + pDrawWidget->m_manager.brushPathsList[brushImageIndex]);
            //brushImages.push_back();
            stream <<usedImageIndexes.values()[i];
            save_image(stream, img );
         }

    for (BrushBeginingIndex &brushBeginingIndex : brushes)
    {
        Brush &data = brushBeginingIndex.brush;
        qDebug()<<"before save_image";
        //save_image(stream, data.img );
        //save_image(stream,data.color_img);
         qDebug()<<"save_image";
   stream  << data.size << data.opacity << data.blur << data.color_main << data.dispers <<
           data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn;
    stream << data.imageIndex << brushBeginingIndex.pointIndex;
    }


}



int DrawBrushElm::SPEED_OF_RECORDING_MS = 5;

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
void DrawBrushElm::setLifeTime(int value)
{
    lifeTime = value;
    if(coords.size() != 0)
        tickTime = lifeTime/coords.size();
}
void DrawBrushElm::draw()
{
//    qDebug() << tickTimer.elapsed() << "  " << tickTime;




     if (pDrawWidget->getTimeLine()->getPlayTime()>0)
    {
          int realKeyValue = (pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)*coords.size()/lifeTime;
        if(keyCouter == 0)
            pDrawWidget->clearFrameBuffer();

        while(keyCouter <realKeyValue)
        {
            if (keyCouter < coords.size() && bPlay) pDrawWidget->paintBrushInBuffer(coords,brushes,keyCouter);
                    keyCouter++;
        }
    }
    pDrawWidget->paintBufferOnScreen(x, y, width, height, z);

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
    qDebug() << "brushes.length() before add:"<<brushes.length();
    for (int i=0;i<brushes.length();i++){
   // qDebug() << "i:"<<i;
    qDebug() << "pointIndex         :   "<<brushes[i].pointIndex;
    qDebug() << "coords.length()          :   "<<coords.length();
       // if (i==0) continue;

        if (brushes[i].pointIndex==coords.length()){
            brushes[i].brush=brush;
            return;
        }
    }
    BrushBeginingIndex beginIndex;
    beginIndex.brush=brush;
    beginIndex.pointIndex=coords.length();
brushes.append(beginIndex);
qDebug() << "brushes.length() after add:"<<brushes.length();
}




#include "drawbrush.h"

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
     stream >> coords;
     qDebug()<<"LOADED coords len:"<<coords.length();//<<" values:"<<coords[0]<<" "<<coords[1];
     /*for (QPoint coord : coords)
     {
         qDebug() <<"Point:"<<coord;
     }*/
     int brushCount = 0;
    stream >> brushCount;
     qDebug() << "load brushes:"<<brushCount;
    for (int i = 0; i <brushCount;i++)
    {
        BrushBeginingIndex brushBeginingIndex;
        Brush data;
        //stream >> data.patchToImage;
      data.img = load_image(stream );

       // data.img=load_image(stream);
        //data.color_img=load_image(stream);
        stream  >> data.size >> data.opacity >> data.blur >> data.color_main >> data.dispers >>
        data.delta_count >> data.count >> data.size_delta >> data.angle_delta >> data.afinn;
        stream >> brushBeginingIndex.pointIndex;
        data.color_img = BrushPainter::getInstance()->applyColor(data);
        brushBeginingIndex.brush=data;
        brushes.push_back(brushBeginingIndex);
    }

    if(coords.size() != 0)
        tickTime = lifeTime/coords.size();
}

bool DrawBrushElm::save_add(QDataStream &stream)
{
 stream << coords;
 stream << brushes.length();
    for (BrushBeginingIndex &brushBeginingIndex : brushes)
    {
        Brush &data = brushBeginingIndex.brush;
        qDebug()<<"before save_image";
        save_image(stream, data.img );
        //save_image(stream,data.color_img);
         qDebug()<<"save_image";
   stream  << data.size << data.opacity << data.blur << data.color_main << data.dispers <<
           data.delta_count << data.count << data.size_delta << data.angle_delta << data.afinn;
    stream << brushBeginingIndex.pointIndex;
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
    //qDebug() << tickTimer.elapsed() << "  " << tickTime;
    if(keyCouter < coords.size() && tickTimer.elapsed() > tickTime)
    {
        pDrawWidget->paintBrushInBuffer(coords,brushes,keyCouter++);
        qDebug() << "INTERES";
        tickTimer.restart();
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
    qDebug() << "brushes.length():"<<brushes.length();
    for (int i=0;i<brushes.length();i++){
   // qDebug() << "i:"<<i;
    qDebug() << "pointIndex         :   "<<brushes[i].pointIndex;
    qDebug() << "coords.length()          :   "<<coords.length();
        if (i==0) continue;

        if (brushes[i].pointIndex==coords.length()){
            brushes[i].brush=brush;
            return;
        }
    }
    BrushBeginingIndex beginIndex;
    beginIndex.brush=brush;
    beginIndex.pointIndex=coords.length();
brushes.append(beginIndex);
}




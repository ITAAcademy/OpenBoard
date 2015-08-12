#include "brushpainter.h"

/*BrushPainter::BrushPainter(QObject *parent) : QObject(parent)
{

}*/

BrushPainter::~BrushPainter()
{

}
BrushPainter* BrushPainter::p_instance = 0;
void BrushPainter::close()
{

}
 QImage BrushPainter::applyColor(Brush brush)
{
     QImage res(brush.img.size()*2, QImage::Format_RGBA8888_Premultiplied);
     res.fill(Qt::transparent);
     QPainter paint;
     paint.begin(&res);
          paint.setOpacity((double)brush.opacity/100);
     paint.drawImage(brush.img.width()/2,brush.img.height()/2, brush.img);
     paint.end();
     QGraphicsColorizeEffect *effect;
     effect = new QGraphicsColorizeEffect();
     effect->setColor(brush.color_main);
     QGraphicsBlurEffect *blur;
     blur = new QGraphicsBlurEffect();
     blur->setBlurRadius(brush.blur);
    // res = applyEffectToImage(applyEffectToImage(res, effect).scaled(brush.img.size()), blur);
      res = applyEffectToImage(res, effect);
     return res;
}
 QImage BrushPainter::applyBlur(Brush brush)
{
     QImage res(brush.img.size()*2, QImage::Format_RGBA8888_Premultiplied);
     res.fill(Qt::transparent);
     QPainter paint;
     paint.begin(&res);
          paint.setOpacity((double)brush.opacity/100);
     paint.drawImage(brush.img.width()/2,brush.img.height()/2, brush.img);
     paint.end();
     QGraphicsBlurEffect *blur;
     blur = new QGraphicsBlurEffect();
     blur->setBlurRadius(brush.blur);
     qDebug () << "set blur radius:"<<brush.blur;
    // res = applyEffectToImage(res.scaled(brush.img.size()), blur);
     res = applyEffectToImage(res, blur);
     return res;

}

QImage BrushPainter::drawBrush(Brush &brush, QSize size)
{
    QImage img(size, QImage::Format_RGBA8888);

    QGraphicsColorizeEffect *effect;
    QGraphicsBlurEffect *blur;
    effect = new QGraphicsColorizeEffect();
    blur = new QGraphicsBlurEffect();

    effect->setColor(brush.color_main);
    blur->setBlurRadius(brush.blur);
    QImage drawImg = applyEffectToImage(brush.img,effect);
    int width = drawImg.scaled(brush.size, brush.size, Qt::KeepAspectRatio).width();
    if(width < 4)
        width = 4;

    QBrush qBrush;
    QPainter paint(&img);
    paint.setBrush(qBrush);
    QImage resultImg;
    QTransform transformation;
    paint.setOpacity((double)brush.opacity/100);
    int n = (size.width() - 100 ) / (width/4);
    n--;
    for(int j = 0; j <= brush.count; j++)
        for(int i = 0; i < n; i++)
        {
            int b = brush.size_delta/2 - rand() % ((int)brush.size_delta + 1);
            int m = brush.dispers/2 - rand() % ((int)brush.dispers + 1);
         //   transformation.rotate(brush.angle_delta/2 - rand() % ((int)brush.angle_delta + 1));
            resultImg = drawImg.scaled(brush.size +  b, brush.size + b, Qt::KeepAspectRatio).transformed(transformation);
            qBrush.setTextureImage(resultImg);
            paint.drawImage(i*resultImg.width()/4,size.height()/2 - resultImg.height()/2 + m,resultImg);
        }
   // paint.fillRect(0,0,200,200,QBrush(brush.color_main, Qt::SolidPattern));

    bool bEnd = paint.end();
    return applyEffectToImage(img, blur);
    }

QImage BrushPainter::applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent)
{
    if(src.isNull()) return QImage();   //No need to do anything else!
    if(!effect) return src;             //No need to do anything else!

    QList<QGraphicsItem*> itemsList = scene.items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    { QGraphicsItem* item = (*iter); scene.removeItem(item); iter++; }

    QGraphicsPixmapItem *item = scene.addPixmap(QPixmap::fromImage(src));
    item->setGraphicsEffect(effect);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_RGBA8888_Premultiplied);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    ptr.end();
    scene.clear();
    return res;
}

QImage BrushPainter::applyMask(QImage src, QImage mask)
{
    QImage res(src.size(), src.format());
    QPixmap pix_mask = QPixmap::fromImage(mask.createAlphaMask());
    QPainter ptr(&res);
    ptr.setClipRegion(QRegion(pix_mask));
    ptr.drawImage(0, 0, src);
    ptr.end();
    return res;
}


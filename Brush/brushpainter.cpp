#include "brushpainter.h"

BrushPainter::BrushPainter(QObject *parent) : QObject(parent)
{

}

BrushPainter::~BrushPainter()
{

}

QImage BrushPainter::drawBrush(Brush &brush, QSize size)
{
    QImage img(size, QImage::Format_RGBA8888);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
    effect->setColor(brush.color_main);
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(brush.blur);
    QImage drawImg = applyEffectToImage(brush.img,effect);
    int width = drawImg.scaled(brush.size, brush.size, Qt::KeepAspectRatio).width();
    if(width < 4)
        width = 4;

    QBrush qBrush;
    QPainter paint(&img);
    paint.setBrush(qBrush);
    QImage resultImg;
    int n = (size.width() - 100 ) / (width/4);
    n--;
    for(int i = 0; i < n; i++)
    {

        int b = brush.size_delta/2 - rand() % ((int)brush.size_delta + 1);
        int m = brush.dispers/2 - rand() % ((int)brush.dispers + 1);
       // qDebug() << "QWE    " << b;
        resultImg = drawImg.scaled(brush.size +  b, brush.size + b, Qt::KeepAspectRatio);
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
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    return res;
}


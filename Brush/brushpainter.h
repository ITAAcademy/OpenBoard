#ifndef BRUSHPAINTER_H
#define BRUSHPAINTER_H
#include <QObject>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QtWidgets>
#include "QTime"

using namespace std;
struct Brush{
    QImage img = QImage(10,10,QImage::Format_RGB888);
    QImage color_img;
    float size = 50;
    float opacity = 100;
    float blur = 0;

    QColor color_main = "white";

    float dispers = 0;
    float delta_count = 0;
    float count = 0;

    float size_delta = 0;
    float angle_delta = 0;
    float afinn = 0;

};

class BrushPainter : public QObject
{
    Q_OBJECT

    QGraphicsScene scene;
public:
    explicit BrushPainter(QObject *parent = 0);
    ~BrushPainter();
    void close();
    QImage applyColor(Brush brush);
    QImage drawBrush(Brush &brush, QSize size = QSize(800,230));
    QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
    QImage applyMask(QImage src, QImage mask);
};

#endif // BRUSHPAINTER_H

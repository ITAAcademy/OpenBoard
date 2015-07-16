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
    QImage img = QImage(1,1,QImage::Format_ARGB32);
    float size = 100;
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
public:
    explicit BrushPainter(QObject *parent);
    ~BrushPainter();

    static QImage drawBrush(Brush &brush, QSize size = QSize(600,230));
    static QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
};

#endif // BRUSHPAINTER_H

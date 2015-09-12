#ifndef FILEPAINTER_H
#define FILEHPAINTER_H
#include <QObject>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QtWidgets>
#include "QTime"

using namespace std;
struct FileBrush{

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
    int imageIndex = -1;
};



class FilePainter : public QObject
{
    Q_OBJECT

private:
     QGraphicsScene scene;
  static FilePainter *p_instance;
  // Конструкторы и оператор присваивания недоступны клиентам
  FilePainter(QObject *parent = 0) {}
  FilePainter( const FilePainter& );
  FilePainter& operator=( FilePainter& );
public:
  static FilePainter *getInstance() {
      if(!p_instance)
          p_instance = new FilePainter();
      return p_instance;
  }
   // explicit FilePainter(QObject *parent = 0);
    ~FilePainter();
    void close();

};


#endif // FilePainter_H

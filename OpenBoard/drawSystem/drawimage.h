#ifndef _H
#define _H
#include "drawelement.h"

class DrawImageElm  :public DrawElement
{
    Q_OBJECT
    QImage image;
    int textureIndex = 0;
public:
    explicit DrawImageElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawImageElm();
    void draw();
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
    void setDrawImage(QImage img);

    bool setDrawWidget(OGLWidget *value);
};

#endif // _H

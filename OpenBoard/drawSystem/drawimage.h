#ifndef _H
#define _H
#include "drawelement.h"

class DrawImageElm  :public DrawElement
{
    Q_OBJECT
    QImage image;
    GLuint textureIndex = -1;
    int failedLoad = 10;
    bool bGIF = false;
    QMovie *gif = NULL;
public:
    explicit DrawImageElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawImageElm();
    void draw();
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
    void setDrawImage(QImage img);

    bool setDrawWidget(OGLWidget *value);
    bool isBGIF() const;
    void setGIF(bool value);
    QMovie *getGif() const;
    void setGif(QMovie *value);
};

#endif // _H

#ifndef _H
#define _H
#include "drawelement.h"

class DrawImageElm  :public DrawElement
{
    Q_OBJECT
    QImage image;
    QImage img_backup;
    GLuint textureIndex = -1;
    int failedLoad = 10;
    bool bGIF = false;
    QMovie *gif = NULL;

public:
    explicit DrawImageElm( OGLWidget *drawWidget = NULL, QObject *parent = 0);
    ~DrawImageElm();
    void draw();
    bool load_add(QDataStream &stream, QString projectPATH, float version);
    bool save_add(QDataStream &stream, QString projectPATH);
     void setDrawImage(QImage img,bool set_bk = true);

    bool setDrawWidget(OGLWidget *value);
    bool isBGIF() const;
    void setGIF(bool value);
    QMovie *getGif() const;
    void setGif(QMovie *value);
    void setSize(int width, int height);
    void setSize(QSize pos);
    void setBorder(float value);
};

#endif // _H

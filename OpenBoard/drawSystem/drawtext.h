#ifndef DrawTextElm_H
#define DrawTextElm_H
//#pragma once
#include <QObject>
#include "drawelement.h"
#include "../parser/parser.h"

#define LINE_HEIGHT 25

class DrawTextElm : public DrawElement
{
    Q_OBJECT

    QList <Unit*>mUnitList;
    QString loggerText;
    QString unParsestring;
    Parser myParser;
    int textCursor = 0;
    GLuint textureIndex = -1;
    int prevTextCursor = 0;
    bool bCalcTime = false;
    quint64 drawTime;
    int globalPauseLifeTime = 0;
    int globalDeltaComandSize = 0;
    int animationDelayCount = 1;
    int animationDelayStart = 1;
    int curentCh;

    QFont textFont;
    QFont mainTextFont;
    QFontMetrics *fMetrics = NULL;
    int indexInList;
    int deleteWT;

    QString font;
    bool isWord  ;
    int indexRowInList; // first str for draw

    QColor mainFillColor;

    int cursorIndex;
    QList<short int> cross;
    QList<QString> stringList;
    bool crossWithAnimation = false;
    QList <QPoint> symbolPositionList;
    QString listWords; // вся стрічка
    QString listChars; // останнє введене слово
    QList<int> listStr; // номер з якої починається і-та стрічка
    int indexW ;
    int indexRow;
    int indexFirstDrawSymbol = 0;
    int indexLastDrawSymbol = 0;
    int marginLeft;
    int marginTop;
    int line_x ,line_y ;

    int lineHeight;
    int pt;
    int scroll;
    volatile bool isCrossingNow;
    QColor fillColor;
    QVector <AnimationFigure> listOfAnimationFigure; // now use only for cross animation

    double animationPersentOfCross = 0.01;


public:
    QFont getTextFont() const;
    void setTextFont(const QFont &value);
    bool setDrawWidget(OGLWidget *value);
    QList<ColorMarker> colors;
    int curentPauseValue = 0;
    explicit DrawTextElm( OGLWidget *drawWidget = NULL, QObject *parent = 0);
    ~DrawTextElm();
    void clearBuffer();
    void draw();
    void setLifeTime(int value);
    QList<Unit *> unitList() const;
    void setUnitList(const QList<Unit *> &unitList);
    QString getUnParsestring() const;
    void setUnParsestring(const QString &valueUnParss, const QString &valueLogger);

    QString getLoggerText() const;
    void setLoggerText(const QString &value);

    int getCursorIndex() const;
    void setCursorIndex(int value);

    quint64 getDrawTime() const;

    int getTextCursor() const;
    void setTextCursor(const int &value);

    int getPrevTextCursor() const;
    void setPrevTextCursor(int value);

     void drawTextBuffer(int m_x, int m_y, int m_width, int m_height, int z = 0, bool cross = true, float scale = 1);
     void nextRow(int n   = -1, int Row = -1, bool wrap = true);

       void clearCanvas(int m_x = 0, int m_y = 0);
       void moveCursor(int n = 1, bool withWrapShift = true);

        void insertToBuffer(const QChar ch);
        void crossOutLastSymbol( int n);

        void deleteFromBuffer(int n);
        int getCountDeleteWT() const;
        void update();
        QColor getMainFillColor() const;
        void setMainFillColor(const QColor &value);
         int getCountNullString(int index);
         int getLastSymbolOfString(int index, bool symbol);
       int getFirstSymbolOfString(int index, bool symbol = false);
       QPoint convertTextBoxToBufferIndex(int index, bool symbol = false);
       int getRowFromTextBoxIndex(int index, bool symbol);
       bool drawAnimationFigure (int x, int y, int width, int height, double persent,OGLWidget::FigureType type, bool fill);
       bool drawAnimationFigure (AnimationFigure &figure);
       void setFillColor( QColor col);
       double getAnimationPersentOfCross() const;
       void setAnimationPersentOfCross(double value);
       void isLastRow();

       bool getBNeedCalcTime() const;
       void setBNeedTime(bool value);

private:
       void setTickTime(int value);
       bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
protected slots:
     void start();
public slots:
     bool crossText();
     bool crossTextDraw();
     Q_INVOKABLE void crossOutWithAnimation(int n = 1);

signals:
      void drawTextChanged();


};

#endif // DrawTextElm_H

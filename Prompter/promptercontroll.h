#ifndef EFFECTSCONTROL_H
#define EFFECTSCONTROL_H
#include <QObject>
#include <QQuickImageProvider>
#include <QDir>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView> //Not using QQmlApplicationEngine because many examples don't have a Window{}
#include <QQmlContext>
#include <QList>
#include <QStack>
#include <QDebug>
#include <QFont>
#include <QQuickItem>
#include <prompteritem.h>
#define WINDOW_SIZE_WIDTH_DEFAULT 800
#define WINDOW_SIZE_HEIGHT_DEFAULT 400
#define WINDOW_SIZE_WIDTH_MIN 300
#define WINDOW_SIZE_HEIGHT_MIN 200

enum PromptErrorStatus{PROMPT_SUCCESS,PROMPT_CONCURENT_ERROR,PROMPT_INDEX_OUT_OF_RANGE};

class PrompterManager : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    public:
    QQuickView view;
    /*
     *
 */
    QPoint framaMousePosition;
    QPoint prevMousePosition;
public:

    explicit PrompterManager(QObject *parent = 0);
    ~PrompterManager();
    void show();
    void hide();
    void close();
    QQmlContext* getRootContext();
    bool isActive();
    void setCurrentTime(int newTime);
    Q_INVOKABLE int getCurrentTime();

    Q_INVOKABLE void moveWindow( ) ;
    Q_INVOKABLE void resizeWindowWidth(bool left) ;
    Q_INVOKABLE void resizeWindowHeight(bool up) ;


    Q_INVOKABLE void  setFramaMousePosition( const int x,const int y) ;
    Q_INVOKABLE void setFramaMousePosition( const QPoint x);
    Q_INVOKABLE void setPrevMousePosition  ();
    Q_INVOKABLE int addPrompt(int startTime,int lifeTime,QString text);
    Q_INVOKABLE int setPromptStartTimeAt(int index,int startTime);
    Q_INVOKABLE int setPromptLifeTimeAt(int index,int lifeTime);
    Q_INVOKABLE int setPromptTextAt(int index,QString text);

    bool checkTimeisCorrect(int startTime, int lifeTime, int indexOfChangedElement);
    void determineAndSelectCurrentLineByTime(int time);
signals:
    void showSignal();
    void hideSignal();
    void currentTimeChanged(int val);
    void selectCurrentLineInListSignal(int val);

public slots:
    void setFocus();
    Q_INVOKABLE void update();

private:
    QList<QObject*> promptsData;
     int currentTime;
    int blockTime = 0;
    bool showed=false;
   // QStringList dataListLabels;
};

#endif // LISTCONTROLL_H

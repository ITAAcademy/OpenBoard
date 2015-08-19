#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QObject>
#include <QtCore>
#include <QtQuick>
#include <QFileDialog>

enum VIEW_STATE
{
    VIDEO_EDIT_TEXT = 0,
    VIDEO_EDIT_PRO = 1,
    VIDEO_EDIT_DEFAULT = 2,
    BRUSH_ANIMATION = 3,
    VISUAL_EFFECT = 4,
    OPENING_PROJECT = 5
};

struct ProjectStartupSetting
{
    VIEW_STATE state;
    bool advance_mode;

    // text
    QString firstImage;
    QString lastImage;
    int firsTime = 3000;
    int lastTime = 3000;
};

class ProjectCreator : public QObject
{
    Q_OBJECT

    QQuickView view;
    ProjectStartupSetting curent;
    volatile bool start;
public:
    explicit ProjectCreator(QObject *parent = 0);
    ~ProjectCreator();

    ProjectStartupSetting getCurentSetting() const;
    void setCurentSetting(const ProjectStartupSetting &value);
    bool isVisible();
    void show(bool fullScreen = false);

    static ProjectStartupSetting getProjectSetting(bool isStart, bool fullScreen = false);

    Q_INVOKABLE void close();
    Q_INVOKABLE void setProjectState( int state);
    Q_INVOKABLE void setAdvanceMode( bool state);

    Q_INVOKABLE void textMode_SetFirstImage(QString path);
    Q_INVOKABLE void textMode_SetFirstTime(QString time);
    Q_INVOKABLE void textMode_SetLastImage(QString path);
    Q_INVOKABLE void textMode_SetLastTime(QString time);
    Q_INVOKABLE bool isForStart();
    Q_INVOKABLE QString fileDialog(int OPEN_SAVE = 0);
    void setStart(bool value);

signals:

public slots:
};

#endif // PROJECTCREATOR_H

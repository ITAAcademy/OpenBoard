#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QObject>
#include <QtCore>
#include <QtQuick>

enum VIEW_STATE
{
    VIDEO_EDIT_TEXT,
    VIDEO_EDIT_PRO,
    VIDEO_EDIT_DEFAULT,
    BRUSH_ANIMATION,
    VISUAL_EFFECT
};

struct ProjectStartupSetting
{
    VIEW_STATE state;
    bool advance_mode;
};

class ProjectCreator : public QObject
{
    Q_OBJECT

    QQuickView view;
    ProjectStartupSetting curent;
public:
    explicit ProjectCreator(QObject *parent = 0);
    ~ProjectCreator();

    ProjectStartupSetting getCurentSetting() const;
    void setCurentSetting(const ProjectStartupSetting &value);
    bool isVisible();
    void show(bool fullScreen = false);

    static ProjectStartupSetting getProjectSetting(bool fullScreen);

    Q_INVOKABLE void close();
    Q_INVOKABLE void setProjectState( int state);
    Q_INVOKABLE void setAdvanceMode( bool state);

signals:

public slots:
};

#endif // PROJECTCREATOR_H

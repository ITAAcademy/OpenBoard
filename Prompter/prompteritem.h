#ifndef PROMPTERITEM_H
#define PROMPTERITEM_H
#include "qstring.h"
#include "qobject.h"

class PromptItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
     Q_PROPERTY(int lifeTime READ lifeTime WRITE setLifeTime NOTIFY lifeTimeChanged)
     Q_PROPERTY(QString promptText READ promptText WRITE setPromptText NOTIFY promptTextChanged)

public:
    PromptItem(QObject *parent=0);
    PromptItem(int startTime, int lifeTime,const QString &text);

        int startTime() const;
        void setStartTime(const int &startTime);

        int lifeTime() const;
        void setLifeTime(const int &lifeTime);

        QString promptText();
        void setPromptText(const QString &text);
signals:
    void startTimeChanged();
    void lifeTimeChanged();
    void promptTextChanged();
private:
    int m_startTime;
    int m_lifeTime;
    QString m_promptText;
};


#endif // PROMPTERITEM_H

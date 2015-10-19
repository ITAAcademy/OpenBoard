#include "prompteritem.h"

PromptItem::PromptItem(QObject *parent): QObject(parent)
{

}



PromptItem::PromptItem(int startTime, int lifeTime, const QString &text)
{
this->m_startTime=startTime;
this->m_lifeTime=lifeTime;
this->m_promptText=text;
}

int PromptItem::startTime() const
{
    return m_startTime;
}

void PromptItem::setStartTime(const int &startTime)
{
    if (startTime != m_startTime) {
            m_startTime = startTime;
            emit startTimeChanged();
    }
}

bool PromptItem::isTimeInRange(int time)
{
     if (time>=startTime && time <= startTime+lifeTime()) return true;
     return false;
}

int PromptItem::lifeTime() const
{
    return m_lifeTime;
}

void PromptItem::setLifeTime(const int &lifeTime)
{
    if (lifeTime != m_lifeTime) {
            m_lifeTime = lifeTime;
            emit lifeTimeChanged();
    }
}

QString PromptItem::promptText()
{
    return m_promptText;
}

void PromptItem::setPromptText(const QString &text)
{
    if (m_promptText!=text)
    {
        m_promptText=text;
        emit promptTextChanged();
    }
}





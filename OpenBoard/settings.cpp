#include "settings.h"


pSettings::pSettings() :
    isFirstRun(false)
    ,mSettings(0)
{

    mSettings = new QSettings("settings.ini", QSettings::IniFormat);
    loadSettings();

}

pSettings::~pSettings()
{
    saveSettings();

    if(mSettings != 0)
        delete mSettings;
}

void pSettings::saveSettings()
{
    mSettings->remove("MainWindow/font");
        mSettings->setValue("FirstRun/IsRunFirst",  true);
        mSettings->setValue("MainWindow/title",     mainWindowTitle);
        mSettings->setValue("MainWindow/position",  mainWindowRect);


        mSettings->setValue("MainWindow/fontColor",     mainWindowColor.name());

        QString fFamily = mainWindowFont.family();
        int fSize = mainWindowFont.pointSize();
        mSettings->setValue("MainWindow/fontFamily",      fFamily);
           mSettings->setValue("MainWindow/fontSize",      fSize);

           mSettings->setValue("Board/fontColor",          boardFontColor.name());

           QString fbFamily = boardFont.family();
           int fbSize = boardFont.pointSize();
           mSettings->setValue("Board/fontFamily",      fbFamily);
              mSettings->setValue("Board/fontSize",      fbSize);


}


void pSettings::loadSettings()
{

    if(mSettings->value("FirstRun/IsRunFirst").toBool() == false)
        isFirstRun = true;

    mainWindowTitle = mSettings->value("MainWindow/title") .toString();
    mainWindowRect  = mSettings->value("MainWindow/position") .toRect();

    mainWindowColor = mSettings->value("MainWindow/fontColor") .toString();
    mainWindowFont.setFamily(mSettings->value("MainWindow/fontFamily").toString());
  //  mainWindowFont = mSettings->value("MainWindow/fontColor").toString();
    mainWindowFont.setPointSize(mSettings->value("MainWindow/fontSize").toInt());

    boardFont.setFamily(mSettings->value("Board/fontFamily").toString());
    boardFont.setPointSize(mSettings->value("Board/fontSize").toInt());

 boardFontColor = mSettings->value("Board/fontColor").toString();
   //  mainWindowFont.fromString(mSettings->value("MainWindow/font") .toString());
    //QString sFont = QString(mSettings->value("Board/font").toString());
    //boardFont.fromString(sFont);
  // QFont ftemp ()
   // boardFont =  qvariant_cast<QFont>(mSettings->value("Board/font").toUInt());


}



void pSettings::setMainWindowTitle(const QString &aTitle)
{
    mainWindowTitle = aTitle;
}

void pSettings::setMainWindowRect(const QRect &aRect)
{
    mainWindowRect = aRect;
}
//!!!!!!!!!!!!!
void pSettings::setMainWindowColor(const QColor &aColor)
{
    mainWindowColor = aColor;
}

void pSettings::setMainWindowFont(const QFont &aFont)
{
    mainWindowFont = aFont;
}

//!!!!!!!!!!!
void pSettings::setBoardFont(const QFont &bFont)
{
    boardFont = bFont;
}
//!!!!!!!!!!!!!
void pSettings::setBoardFontColor(const QColor &bColor)
{
    boardFontColor = bColor;
}

const bool &pSettings::FirstRun()const
{
    return isFirstRun;
}

const QString &pSettings::getMainWindowTitle()const
{
    return mainWindowTitle;
}

const QRect &pSettings::getMainWindowRect()const
{
    return mainWindowRect;
}

const QFont &pSettings::getMainWindowFont()const
{
    return mainWindowFont;
}

const QFont &pSettings::getBoardFont()const
{
    return boardFont;
}


const QColor &pSettings::getMainWindowColor()const
{
    return mainWindowColor;
}

const QColor &pSettings::getBoardFontColor()const
{
    return boardFontColor;
}




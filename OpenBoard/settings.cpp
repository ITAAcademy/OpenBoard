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
        mSettings->setValue("MainWindow/fontItalic",      mainWindowFont.italic());
        mSettings->setValue("MainWindow/fontBold",      mainWindowFont.bold());
        mSettings->setValue("MainWindow/fontStrike",      mainWindowFont.strikeOut());
        mSettings->setValue("MainWindow/fontUnderline",      mainWindowFont.underline());

        mSettings->setValue("Board/fontColor",          boardFontColor.name());

        QString fbFamily = boardFont.family();
        int fbSize = boardFont.pointSize();
        mSettings->setValue("Board/fontFamily",      fbFamily);
        mSettings->setValue("Board/fontSize",      fbSize);
        mSettings->setValue("Board/fontItalic",      boardFont.italic());
        mSettings->setValue("Board/fontBold",      boardFont.bold());
        mSettings->setValue("Board/fontStrike",      boardFont.strikeOut());
        mSettings->setValue("Board/fontUnderline",      boardFont.underline());


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
    mainWindowFont.setItalic(mSettings->value("MainWindow/fontItalic").toBool());
    mainWindowFont.setBold(mSettings->value("MainWindow/fontBold").toBool());
    mainWindowFont.setStrikeOut(mSettings->value("MainWindow/fontStrike").toBool());
    mainWindowFont.setUnderline(mSettings->value("MainWindow/fontUnderline").toBool());

    boardFont.setFamily(mSettings->value("Board/fontFamily").toString());
    boardFont.setPointSize(mSettings->value("Board/fontSize").toInt());
    boardFont.setPointSize(mSettings->value("Board/fontSize").toInt());
    boardFont.setItalic(mSettings->value("Board/fontItalic").toBool());
    boardFont.setBold(mSettings->value("Board/fontBold").toBool());
    boardFont.setStrikeOut(mSettings->value("Board/fontStrike").toBool());
    boardFont.setUnderline(mSettings->value("Board/fontUnderline").toBool());

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




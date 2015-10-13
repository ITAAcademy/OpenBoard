#include "settings.h"
#include "qdebug.h"

pSettings::pSettings() :
    isFirstRun(false)
    ,mSettings(0)
{

    mSettings = new QSettings("settings.ini", QSettings::IniFormat);
    defaultSettings = new QSettings("default.ini",QSettings::IniFormat);
    loadSettings(mSettings);

}

pSettings::~pSettings()
{
    saveSettings(mSettings);

    if(mSettings != 0)
        delete mSettings;
}

void pSettings::saveSettings(QSettings * settings )
{
    settings->remove("MainWindow/font");
        settings->setValue("FirstRun/IsRunFirst",  true);
        settings->setValue("MainWindow/title",     mainWindowTitle);
        settings->setValue("MainWindow/position",  mainWindowRect);


        settings->setValue("MainWindow/fontColor",     mainWindowColor.name());

        QString fFamily = mainWindowFont.family();
        int fSize = mainWindowFont.pointSize();
        settings->setValue("MainWindow/fontFamily",      fFamily);
        settings->setValue("MainWindow/fontSize",      fSize);
        settings->setValue("MainWindow/fontItalic",      mainWindowFont.italic());
        settings->setValue("MainWindow/fontBold",      mainWindowFont.bold());
        settings->setValue("MainWindow/fontStrike",      mainWindowFont.strikeOut());
        settings->setValue("MainWindow/fontUnderline",      mainWindowFont.underline());

        settings->setValue("Board/fontColor",          boardFontColor.name());

        QString fbFamily = boardFont.family();
        int fbSize = boardFont.pointSize();
        settings->setValue("Board/fontFamily",      fbFamily);
        settings->setValue("Board/fontSize",      fbSize);
        settings->setValue("Board/fontItalic",      boardFont.italic());
        settings->setValue("Board/fontBold",      boardFont.bold());
        settings->setValue("Board/fontStrike",      boardFont.strikeOut());
        settings->setValue("Board/fontUnderline",      boardFont.underline());


}
void pSettings::loadDefaultSettings(){
loadSettings(defaultSettings);
}
QSettings *pSettings::getDefaultSettings() const
{
    return defaultSettings;
}

void pSettings::setDefaultSettings(QSettings *value)
{
    defaultSettings = value;
}
QSettings *pSettings::getSettings() const
{
    return mSettings;
}

void pSettings::setSettings(QSettings *settings)
{
    mSettings = settings;
}



void pSettings::loadSettings(QSettings *settings)
{

    if(settings->value("FirstRun/IsRunFirst").toBool() == false)
        isFirstRun = true;

    mainWindowTitle = settings->value("MainWindow/title") .toString();
    mainWindowRect  = settings->value("MainWindow/position") .toRect();

    mainWindowColor = settings->value("MainWindow/fontColor") .toString();
    mainWindowFont.setFamily(settings->value("MainWindow/fontFamily").toString());
  //  mainWindowFont = settings->value("MainWindow/fontColor").toString();
    mainWindowFont.setPointSize(settings->value("MainWindow/fontSize").toInt());
    mainWindowFont.setItalic(settings->value("MainWindow/fontItalic").toBool());
    mainWindowFont.setBold(settings->value("MainWindow/fontBold").toBool());
    mainWindowFont.setStrikeOut(settings->value("MainWindow/fontStrike").toBool());
    mainWindowFont.setUnderline(settings->value("MainWindow/fontUnderline").toBool());

    boardFont.setFamily(settings->value("Board/fontFamily").toString());
    boardFont.setPointSize(settings->value("Board/fontSize").toInt());
    boardFont.setPointSize(settings->value("Board/fontSize").toInt());
    boardFont.setItalic(settings->value("Board/fontItalic").toBool());
    boardFont.setBold(settings->value("Board/fontBold").toBool());
    boardFont.setStrikeOut(settings->value("Board/fontStrike").toBool());
    boardFont.setUnderline(settings->value("Board/fontUnderline").toBool());

    boardFontColor = settings->value("Board/fontColor").toString();
   //  mainWindowFont.fromString(settings->value("MainWindow/font") .toString());
    //QString sFont = QString(settings->value("Board/font").toString());
    //boardFont.fromString(sFont);
  // QFont ftemp ()
   // boardFont =  qvariant_cast<QFont>(settings->value("Board/font").toUInt());


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
     qDebug() << "setBoardFont";
}
//!!!!!!!!!!!!!
void pSettings::setBoardFontColor(const QColor &bColor)
{
    boardFontColor = bColor;
           qDebug() << "setBoardFontColor";
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




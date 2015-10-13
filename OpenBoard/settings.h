#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QRect>
#include <QFontDialog>
#include <QSettings>
#include <QMessageBox>


class pSettings
{

public:

    pSettings();
    ~pSettings();

    const bool &FirstRun()const;

    void setMainWindowTitle (const QString &aTitle);
    void setMainWindowRect  (const QRect &aRect);
    void setMainWindowFont  (const QFont &aFont);
    void setMainWindowColor (const QColor &aColor);
       void setBoardFont       (const QFont &bFont);
       void setBoardFontColor  (const QColor &bColor);

    const QString   &getMainWindowTitle ()const;
    const QRect     &getMainWindowRect  ()const;
    const QFont     &getMainWindowFont  ()const;
    const QColor    &getMainWindowColor ()const;
      const QFont   &getBoardFont       ()const;
      const QColor    &getBoardFontColor  ()const;
      void saveSettings(QSettings *settings= NULL);
      void loadSettings(QSettings *settings);
      void loadDefaultSettings();
      QSettings *getDefaultSettings() const;
      void setDefaultSettings(QSettings *value);

      QSettings *getSettings() const;
      void setSettings(QSettings *settings);

private:



      bool        isFirstRun;
      QString     mainWindowTitle;
      QRect       mainWindowRect;
    QFont       mainWindowFont;
    QColor      mainWindowColor;
       QFont     boardFont;
       QColor      boardFontColor;

    QSettings   *mSettings;
    QSettings   *defaultSettings;
};

#endif // SETTINGS_H

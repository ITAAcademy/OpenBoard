#ifndef YOUTUBEWRAPPER_H
#define YOUTUBEWRAPPER_H
#include <QNetworkReply>
#include "oauth2.h"
#include <QObject>

class YouTubeWrapper : public QObject
{
    Q_OBJECT
public:
    YouTubeWrapper(QString str,QWidget* parent = 0);
    OAuth2* getAuth();
    QFile* videoFile;
    void setUploadFileName(QString name);

private:
    QNetworkAccessManager *_networkMen;
   QNetworkAccessManager *netmen2;
   OAuth2 *qAuth;
   QWidget* m_pParent;
   QString uploadFileName;


private slots:


    void handleUploadReply(QNetworkReply *reply);
    void onLoginDone();
};

#endif // YOUTUBEWRAPPER_H

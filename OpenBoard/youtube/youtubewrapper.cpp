#include "youtubewrapper.h"
#include <youtube/oauth2.h>
#include "QFile"
#include <QSettings>
YouTubeWrapper::YouTubeWrapper(QString filePath,QWidget* parent )
{
    qAuth = new OAuth2(parent);
    videoFile= new QFile(filePath);
    m_pParent=parent;
    connect(qAuth,SIGNAL(loginDone()),this,SLOT(onLoginDone()));
}
void YouTubeWrapper::onLoginDone(){

    if (!videoFile->open(QIODevice::ReadOnly))return;
    QByteArray fileBinaryData(videoFile->readAll());
    videoFile->close();
    QNetworkRequest request;
    // forming request
    QSettings settings("OpenBoard", "OpenBoardTest");
   qDebug (settings.value("access_token").toString().toUtf8());
    request.setUrl(QUrl("https://uploads.gdata.youtube.com/feeds/api/users/default/uploads"));
        request.setRawHeader("Host","uploads.gdata.youtube.com");
        request.setRawHeader("Authorization",QByteArray("Bearer ")+settings.value("access_token").toString().toUtf8());
        request.setRawHeader("GData-Version","2");
        request.setRawHeader("X-GData-Key","key=AIzaSyCE4aN7BiJ72LpePoRFkgsY_mj7OivWGKk");
        request.setRawHeader("Slug",uploadFileName.toUtf8());
        request.setRawHeader("Content-Type","multipart/related; boundary=\"f93dcbA3\"");
        request.setRawHeader("Connection","close");
        QByteArray reqString;
        reqString.append("--f93dcbA3\r\n");
        reqString.append("Content-Type: application/atom+xml; charset=UTF-8\r\n");
        reqString.append("\r\n");
        reqString.append("<?xml version=\"1.0\"?>\r\n");
        reqString.append("<entry xmlns=\"http://www.w3.org/2005/Atom\"\r\n");
        reqString.append("xmlns:media=\"http://search.yahoo.com/mrss/\"\r\n");
        reqString.append("xmlns:yt=\"http://gdata.youtube.com/schemas/2007\">\r\n");
        reqString.append("<media:group>\r\n");
        reqString.append("<media:title type=\"plain\">Test test</media:title>\r\n");
        reqString.append("<media:description type=\"plain\">\r\n");
        reqString.append("Batafa\r\n");
        reqString.append("</media:description>\r\n");
        reqString.append("<media:category ");
        reqString.append("scheme=\"http://gdata.youtube.com/schemas/2007/categories.cat\">People\r\n");
        reqString.append("</media:category>\r\n");
        reqString.append("<media:keywords>ara,arara</media:keywords>\r\n");
        reqString.append("</media:group>\r\n");
        reqString.append("</entry>\r\n");
        reqString.append("--f93dcbA3\r\n");
        reqString.append("Content-Type: video/mpeg\r\n");
        reqString.append("Content-Transfer-Encoding: binary\r\n");
        reqString.append("\r\n");
        reqString.append(fileBinaryData);
        reqString.append("\r\n");
        reqString.append("--f93dcbA3\r\n");
        request.setRawHeader("Content-Length",QString::number(reqString.length()).toUtf8());
    netmen2 = new QNetworkAccessManager();
    connect(netmen2, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleUploadReply(QNetworkReply*)));
    QNetworkReply *rep=netmen2->post(request,reqString);
    rep->ignoreSslErrors();
}

OAuth2* YouTubeWrapper::getAuth(){
    return qAuth;
}
void YouTubeWrapper::setUploadFileName(QString name){
    uploadFileName=name;
}

void YouTubeWrapper::handleUploadReply(QNetworkReply *reply)
{
    reply->ignoreSslErrors();
    if(reply->error())
    {
    qDebug()<<reply->errorString();
    } else
   {
      qDebug()<<reply->readAll();
   }
}

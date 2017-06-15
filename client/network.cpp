#include "network.h"
#include <QNetworkAccessManager>
#include "interface.h"
#include <QDebug>



Network::Network(QObject *parent)
{
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

void Network::auth()
{
    postData->clear();

    request->setUrl(QUrl("http://194.87.98.46/hospital/server/request/auth/"));

    //postData->append("name=" + Interface::editLoginText() + "&");
    //postData->append("password=" + Interface::editPasswordText() + "&");
    postData->append("type_user=2");

    QObject::connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(onResult(QNetworkReply*)),Qt::AutoConnection);


}

void Network::onResult(QNetworkReply *reply)
{
    qDebug() << "im in net (not dark)";
}

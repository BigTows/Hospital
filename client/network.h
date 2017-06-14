#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork>
#include <QObject>


class Network: public QObject
{
    Q_OBJECT
public:
    Network(QObject * parent = 0);
    void auth();
private:
    QNetworkAccessManager * net;
    QNetworkRequest * request;
    QByteArray * postData;
public slots:
    void onResult(QNetworkReply *reply);
};

#endif // NETWORK_H

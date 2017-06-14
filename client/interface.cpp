#include "interface.h"
#include <QLineEdit>
#include <QtNetwork>
#include <QTextEdit>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>
#include <QList>


Interface::Interface(QWidget *parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg.jpg")));

    editLogin = new QLineEdit;
    editLogin->setStyleSheet("border: 1px solid lightgreen;"
                             "font : 14px;");
    editLogin->setTextMargins(10,5,10,5);

    editLogin->setText("doctor_1");

    editPassword = new QLineEdit;
    editPassword->setEchoMode(QLineEdit::Password);
    editPassword->setStyleSheet("border: 1px solid lightgreen;"
                                "font : 14px;");
    editPassword->setTextMargins(10,5,10,5);

    bt = new QPushButton("Войти", nullptr);
    bt->setStyleSheet("color: white;"
                      "border: 1px solid darkgray;"
                      "background-color: green;"
                      "font : 20px;");
    bt->setGeometry(0,0,100,30);

    connect(bt,SIGNAL(clicked(bool)),this,SLOT(on_EnterButton_Clicked()));

    scene->addWidget(editLogin);
    scene->addWidget(editPassword);
    scene->addWidget(bt);
    //scene->setFocusItem(editLogin,Qt::OtherFocusReason);

    setScene(scene);

    editLogin->move(scene->width() / 2 - editLogin->width() / 2, 200);
    editPassword->move(scene->width() / 2 - editPassword->width() / 2, 250);
    bt->move(scene->width() / 2 - bt->width() / 2, 300);
}

void Interface::main_func()
{
    QByteArray postData;
    postData.append("token=" + token + "&");
    postData.append("date=2017-06-01");

    net = new QNetworkAccessManager();
    QObject::connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    QNetworkRequest request(QUrl("http://194.87.98.46/hospital/server/request/getRecords/"));
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    net->post(request, postData);
}

void Interface::onResult(QNetworkReply *reply)
{
    if(!reply->error())
    {

           QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

           QJsonObject root = document.object();

           qDebug() << root;

           QJsonObject jv = root.value("data").toObject();

           token = jv.value("token").toString();

           if (token == "")
           {
               QJsonObject root = document.object();

                      QJsonValue jv = root.value("data");

                      if(jv.isArray())
                      {


                          QJsonArray ja = jv.toArray();

                          for(int i = 0; i < ja.count(); i++)
                          {
                              QJsonObject subtree = ja.at(i).toObject();

                              qDebug() << subtree.value("first_name").toString() + " " +
                                                   subtree.value("second_name").toString();
                          }
                      }
           }

    }

    if (token != "")
    {
        qDebug() << token;
        //token = "";
        bt->hide();
        editLogin->hide();
        editPassword->hide();
        main_func();
    }
    reply->deleteLater();
}

void Interface::on_EnterButton_Clicked()
{
    QByteArray postData;
    postData.append("name=" + editLogin->text() + "&");
    postData.append("password=" + editPassword->text() + "&");
    postData.append("type_user=2");

    net = new QNetworkAccessManager();
    QObject::connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    QNetworkRequest request(QUrl("http://194.87.98.46/hospital/server/request/auth/"));
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    net->post(request, postData);
}

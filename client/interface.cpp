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
#include <QInputDialog>

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
                      //"border: 1px solid darkgray;"
                      "background-color: green;"
                      "font : 20px;");
    bt->setGeometry(0,0,100,30);

    connect(bt,SIGNAL(clicked(bool)),this,SLOT(on_EnterButton_Clicked()));

    scene->addWidget(editLogin);
    scene->addWidget(editPassword);
    scene->addWidget(bt);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    setScene(scene);

    editLogin->move(scene->width() / 2 - editLogin->width() / 2, 200);
    editPassword->move(scene->width() / 2 - editPassword->width() / 2, 250);
    bt->move(scene->width() / 2 - bt->width() / 2, 300);
}


void Interface::main_func()
{/*
    QByteArray postData;
    postData.append("token=" + token + "&");
    postData.append("date=2017-06-13");

    postData.append("token=" + token + "&");
    postData.append("id_user=1234123412341234&");
    postData.append("text=test keklol123   ");

    net = new QNetworkAccessManager();

    QObject::connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    QNetworkRequest request(QUrl("http://194.87.98.46/hospital/server/request/getRecords/"));
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    net->post(request, postData);

    /*QNetworkRequest request(QUrl("http://194.87.98.46/hospital/server/request/addHistory/"));
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    net->post(request, postData);*/

    getRecords();
}

void Interface::auth()
{
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/auth/"));

    postData.append("name=" + editLogin->text() + "&");
    postData.append("password=" + editPassword->text() + "&");
    postData.append("type_user=2");

    net = new QNetworkAccessManager();

    QObject::connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(onAuthResult(QNetworkReply*)));

    net->post(request, postData);
}

void Interface::getRecords()
{
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/getRecords/"));

    postData.append("token=" + token + "&");
    postData.append("date=" + date);
    qDebug() << date;


    net = new QNetworkAccessManager();

    QObject::connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(ongetRecordsResult(QNetworkReply*)));

    net->post(request, postData);
}



void Interface::hide_auth_window()
{
    level == 999;
    bt->hide();
    editLogin->hide();
    editPassword->hide();
}

void Interface::draw_list()
{
    list = new QListWidget();
    list->setStyleSheet("background-color: lightblue;");
    list->resize(700,550);
    list->move(50,25);

    connect(list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));

    qDebug() << mas.size();
    for (int i = 0; i < mas.size(); i++)
    {
        qDebug() << i;
        list->addItem(mas[i].mid(16));
    }

    scene->addWidget(list);
}

void Interface::draw_calendar()
{
    calendar = new QCalendarWidget;
    scene->addWidget(calendar);
    QPushButton * showbt = new QPushButton;
    showbt->setText("Показать");
    showbt->move(0,400);
    scene->addWidget(showbt);
    connect(showbt,SIGNAL(clicked(bool)),this,SLOT(on_showbt_Clicked()));
}

void Interface::addHistory()
{
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/addHistory/"));

    postData.append("token=" + token + "&");
    postData.append("id_user=" + mas[list->currentRow()].mid(0,16) + "&");
    postData.append("text=" + str);
    qDebug() << str;

    net = new QNetworkAccessManager();

    net->post(request, postData);
}

void Interface::itemClicked(QListWidgetItem *item)
{

    str = QInputDialog::getText( 0, "Направление", "Текст:", QLineEdit::Normal, "");
    if (str != "")
    {
        addHistory();
    }

}

void Interface::on_showbt_Clicked()
{
    //qDebug() << calendar->selectedDate().year();
    draw_list();

    date = QString::number(calendar->selectedDate().year()) + "-" + QString::number(calendar->selectedDate().month());
    date += "-" + QString::number(calendar->selectedDate().day());

    //qDebug() << date;
    calendar->hide();
    getRecords();
}

void Interface::onAuthResult(QNetworkReply *reply)
{
    if(!reply->error())
    {

           QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

           QJsonObject root = document.object();

           QJsonObject jv = root.value("data").toObject();

           token = jv.value("token").toString();

           level = root.value("level").toInt();

    }

    if (level == 0)
    {
        hide_auth_window();
        draw_calendar();
        //getRecords();
    }
    else
        level = 999;

    reply->deleteLater();
}

void Interface::ongetRecordsResult(QNetworkReply *reply)
{

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    QJsonValue jv = root.value("data");

    qDebug() << root;

    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();

            for(int i = 0; i < ja.count(); i++)
               {
                   QJsonObject subtree = ja.at(i).toObject();

                   mas.insert(mas.end(), subtree.value("id_user").toString() + subtree.value("date").toString().mid(11) + "   " +
                              subtree.value("second_name").toString() + " " +
                              subtree.value("first_name").toString() + " " +
                              subtree.value("middle_name").toString()
                              );

               //    qDebug() << subtree.value("first_name").toString() + " " +
                //                        subtree.value("second_name").toString();
                   qDebug() << subtree.value("date").toString();
               }
     }
    level = root.value("level").toInt();

    if (level == 0)
    {
        draw_list();
    }
    // qDebug() << level;
}

void Interface::on_EnterButton_Clicked()
{
    auth();
}

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
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg3.jpg")));

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
                      "font : 16px;"
                      "font-weight:bold;");
    bt->setGeometry(0,0,100,30);
    bt->setDefault(true);

    connect(bt,SIGNAL(clicked(bool)),this,SLOT(on_EnterButton_Clicked()));
    connect(editPassword, SIGNAL(returnPressed()), this, SLOT(on_EnterButton_Clicked()));
    connect(editLogin, SIGNAL(returnPressed()), this, SLOT(on_EnterButton_Clicked()));

    backButton = new QPushButton;
    backButton->setStyleSheet("color: white;"
                      "background-color: green;"
                      "font: 13px;"
                      "font-weight:bold;");
    backButton->setText("Назад");

    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(onbackButtonClick()));

    list = new QListWidget;
    list->setStyleSheet("background-color: lightblue;"
                        "font: 15px;");
    list->resize(700,500);
    list->move(50,50);

    connect(list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));

    label = new QLabel;
    label->setText("Неверный логин или пароль");
    label->setStyleSheet("color: red;"
                         "background:transparent;");
    label->hide();

    scene->addWidget(editLogin);
    scene->addWidget(editPassword);
    scene->addWidget(bt);
    scene->addWidget(backButton);
    scene->addWidget(list);
    scene->addWidget(label);

    hideListfucn();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    setScene(scene);

    //размеры виджета определяются только после его графического отображения, поэтому, для того,
    //чтобы использовать её размеры, необходимо сперва добавить её на сцену.

    editLogin->move(scene->width() / 2 - editLogin->width() / 2, 200);
    editLogin->setFocus();
    editPassword->move(scene->width() / 2 - editPassword->width() / 2, 250);
    bt->move(scene->width() / 2 - bt->width() / 2, 300);
    backButton->move(list->x(), list->y() / 2 - backButton->height() / 2);
    label->move(bt->x() + bt->width() / 2 - label->width() / 2, bt->y() + bt->height() * 1.5);
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

void Interface::getRecords(bool from)
{
    mas.clear();
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/getRecords/"));

    postData.append("token=" + token + "&");
    if (from)
    {
    postData.append("date=" + date.toString("yyyy-MM-dd") + "&");
    postData.append("period=true");
    }
    else
        postData.append("date=" + date.toString("yyyy-MM-dd"));
    qDebug() << date.toString();


    net = new QNetworkAccessManager();

    QObject::connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(ongetRecordsResult(QNetworkReply*)));

    net->post(request, postData);
}



void Interface::hide_auth_window()
{
    level = 999;
    bt->hide();
    editLogin->hide();
    editPassword->hide();
    label->hide();
}

void Interface::fill_list()
{
    list->show();
    list->clear();
    backButton->show();

    QTextCharFormat charformat;
    charformat.setBackground(QBrush(QColor(0, 230, 94, 100)));
    for (unsigned int i = 0; i < mas.size(); i++)
        calendar->setDateTextFormat(mas[i].date,charformat);

    for (unsigned int i = 0; i < mas.size(); i++)
        list->addItem(mas[i].time + "    " + mas[i].second_name + " " + mas[i].first_name + " " + mas[i].middle_name + "    " + mas[i].id_user);

}

void Interface::draw_calendar()
{
    calendar = new QCalendarWidget;
    scene->addWidget(calendar);

    calendar->setGeometry(0,0,scene->width(),scene->height());

    connect(calendar,SIGNAL(activated(QDate)),this,SLOT(calendarSelection()));


    date.setDate(1900,01,01);
    getRecords(true);

}

void Interface::addHistory()
{
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/addHistory/"));

    postData.append("token=" + token + "&");
    postData.append("id_user=" + mas[list->currentRow()].id_user + "&");
    postData.append("text=" + str_getText);
    qDebug() << str_getText;

    net = new QNetworkAccessManager();

    net->post(request, postData);
}

void Interface::hideListfucn()
{
    list->hide();
    backButton->hide();
}

void Interface::loadPicture()
{
    request.setUrl(QUrl("https://pp.userapi.com/c620126/v620126184/15af5/a171MPR6ArM.jpg"));

    net = new QNetworkAccessManager();

    connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(onloadPictureResult(QNetworkReply*)));

    net->get(request);
}

void Interface::itemClicked(QListWidgetItem *item)
{
    str_getText = QInputDialog::getText( 0, "Направление", "Текст:", QLineEdit::Normal, "");
    if (str_getText != "")
    {
        addHistory();
    }

}

void Interface::calendarSelection()
{

    date = calendar->selectedDate();

    calendar->hide();

    getRecords(false);
}

void Interface::onbackButtonClick()
{
    hideListfucn();
    calendar->show();
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
    }
    else
    {
        label->show();
        level = 999;
    }

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

                   mas.insert(mas.end(), MyUser());
                   mas[i].id_user = subtree.value("id_user").toString();
                   mas[i].second_name = subtree.value("second_name").toString();
                   mas[i].first_name = subtree.value("first_name").toString();
                   mas[i].middle_name = subtree.value("middle_name").toString();
                   mas[i].time = subtree.value("date").toString().mid(11);
                   mas[i].date = QDate::fromString(subtree.value("date").toString().left(10), "yyyy-MM-dd");
                   qDebug() << mas[i].date;
               }
     }
    level = root.value("level").toInt();

    if (level == 0)
    {
        fill_list();
    }
}

void Interface::onloadPictureResult(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
       {
           QByteArray data = reply->readAll();
           QImage image = QImage::fromData(data);
           backButton->setIcon(QIcon(QPixmap::fromImage(image)));
       }
}

void Interface::on_EnterButton_Clicked()
{
    auth();
}

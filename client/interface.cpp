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
#include <QVBoxLayout>
#include <QPixmap>

Interface::Interface(QWidget *parent)
{

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);

    const QUrl url = QDir::currentPath() + "/bg3.jpg";
    QString test = url.path();

    scene->setBackgroundBrush(QBrush(QImage(test)));

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
    list->resize(440,500);
    list->move(10,50);

    connect(list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));

    //kek


    label = new QLabel;
    label->setText("Неверный логин или пароль");
    label->setStyleSheet("color: red;"
                         "background:transparent;");
    label->hide();

    for (unsigned int i = 0; i < 7; i++)
    {
        mas_label << new QLabel();
        mas_label[i]->setStyleSheet("font: 15px;"
                                    "background-color: rgba(173,216,230,80%);"
                                    "padding-left: 5px");
    }
    mas_label[0]->setStyleSheet("background-color: rgba(173,216,230,80%);"
                                "padding-left: 100px");

    layout = new QVBoxLayout();

    for (unsigned int i = 0; i<7; i++)
    {
         layout->addWidget(mas_label[i]);
         mas_label[i]->hide();
    }

    frame = new QFrame;
    frame->resize(330, 500);
    frame->setStyleSheet("background-color: rgba(0, 0, 0, 30%)");
    frame->setLayout(layout);
    frame->hide();

    timer = new QTimer;
    timer->setInterval(8000);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerTimeout()));

    scene->addWidget(editLogin);
    scene->addWidget(editPassword);
    scene->addWidget(bt);
    scene->addWidget(backButton);
    scene->addWidget(label);
    scene->addWidget(list);
    scene->addWidget(frame);

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
    backButton->hide();
    label->move(bt->x() + bt->width() / 2 - label->width() / 2, bt->y() + bt->height() * 1.5);
    frame->move(list->x() + list->width() + 10, list->y());
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

void Interface::getRecords(bool from, QDate date)
{
        mas.clear();
        postData.clear();

        request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/getRecords/"));

        postData.append("token=" + token + "&");
        postData.append("date=" + date.toString("yyyy-MM-dd") + "&");
        if (from)
            postData.append("period=true");

        qDebug() << postData;

        net = new QNetworkAccessManager();

        QObject::connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(ongetRecordsResult(QNetworkReply*)));
        QObject::connect(net, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

        net->post(request, postData);
}



void Interface::hide_auth_window()
{
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

    for (unsigned int i = 0; i < mas.size(); i++)
        list->addItem(mas[i].time + "   " + mas[i].second_name + " " + mas[i].first_name + " " + mas[i].middle_name);

    //updateCalendar();
}

void Interface::draw_calendar()
{
    calendar = new QCalendarWidget;
    scene->addWidget(calendar);

    calendar->setGeometry(0,0,scene->width(),scene->height());

    connect(calendar,SIGNAL(activated(QDate)),this,SLOT(calendarSelection()));

    updateCalendar();
}

void Interface::addHistory()
{
    postData.clear();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/addHistory/"));

    postData.append("token=" + token + "&");
    postData.append("id_user=" + mas[list->currentRow()].id_user + "&");
    postData.append("text=" + str_getText);

    net = new QNetworkAccessManager();

    net->post(request, postData);
}

void Interface::hideListfucn()
{
    list->hide();
    backButton->hide();
    frame->hide();
}

void Interface::loadPicture(QString photo)
{
    request.setUrl(QUrl(photo));
    qDebug() << photo;

    net = new QNetworkAccessManager();

    connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(onloadPictureResult(QNetworkReply*)));

    net->get(request);
}

void Interface::getUser()
{
    postData.clear();
    SelectedUser = MyUser();

    request.setUrl(QUrl("http://194.87.98.46/hospital/server/request/getUser/"));

    postData.append("token=" + token + "&");
    postData.append("id_user=" + mas[list->currentRow()].id_user);
    qDebug() << postData;

    net = new QNetworkAccessManager();

    connect(net,SIGNAL(finished(QNetworkReply*)),this,SLOT(ongetUserResult(QNetworkReply*)));

    net->post(request, postData);
}

void Interface::updateCalendar()
{

    QDate date;
    date.setDate(1900,01,01);
    getRecords(true, date);
    loop.exec();

    static int kek = mas.size();

    qDebug() << kek;
    qDebug() << mas.size();

    if (kek != mas.size())
    {
        blink();
        kek = mas.size();
    }

    calendar->setDateTextFormat(QDate() , QTextCharFormat());

    QTextCharFormat charformat;
    charformat.setBackground(QBrush(QColor(0, 230, 94, 100)));

    for (unsigned int i = 0; i < mas.size(); i++)
        calendar->setDateTextFormat(mas[i].date,charformat);
}

void Interface::fillProfile()
{
    for (unsigned int i = 0; i<7; i++)
         mas_label[i]->show();

    mas_label[0]->setPixmap(SelectedUser.pixPhoto);
    mas_label[1]->setText(SelectedUser.second_name + " " + SelectedUser.first_name + " " + SelectedUser.middle_name);
    mas_label[2]->setText(SelectedUser.id_user);
    mas_label[3]->setText(SelectedUser.email);
    mas_label[4]->setText(SelectedUser.phone);
    mas_label[5]->setText((SelectedUser.sex == "1") ? "М" : "Ж");
    mas_label[6]->setText(SelectedUser.date.toString("yyyy-MM-dd"));
}

void Interface::blink()
{
    FLASHWINFO info;

    info.cbSize = sizeof(info);
    info.hwnd = (HWND)QWidget::winId();
    info.dwFlags = FLASHW_TRAY;
    info.dwTimeout = 0;
    info.uCount = 3;

    FlashWindowEx(&info);
}

void Interface::itemDoubleClicked(QListWidgetItem *item)
{
    str_getText = QInputDialog::getText( 0, "Направление", "Текст:", QLineEdit::Normal, "");
    if (str_getText != "")
    {
        addHistory();
    }

}

void Interface::itemClicked(QListWidgetItem *item)
{
    getUser();
}

void Interface::calendarSelection()
{
    QDate date;
    date = calendar->selectedDate();

    timer->stop();
    calendar->hide();
    frame->show();

    list->clear();

    getRecords(false, date);
}

void Interface::onbackButtonClick()
{
    hideListfucn();

    for (unsigned int i = 0; i<7; i++)
         mas_label[i]->hide();

    timer->setInterval(8000);
    timer->start();

    onTimerTimeout();
    calendar->show();
}

void Interface::onTimerTimeout()
{
    updateCalendar();
}

void Interface::onAuthResult(QNetworkReply *reply)
{
    if(!reply->error())
    {

           QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

           QJsonObject root = document.object();

           //qDebug() << root;

           QJsonObject jv = root.value("data").toObject();

           token = jv.value("token").toString();



        if (root.value("level").toInt() == 0)
        {
            hide_auth_window();
            draw_calendar();
            timer->start();
        }
        else
            label->show();

    }

    reply->deleteLater();
}

void Interface::ongetRecordsResult(QNetworkReply *reply)
{

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    QJsonValue jv = root.value("data");

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
                   mas[i].time = subtree.value("date").toString().mid(11,5);
                   mas[i].date = QDate::fromString(subtree.value("date").toString().left(10), "yyyy-MM-dd");
                   //qDebug() << mas[i].date;
               }
     }

    if (root.value("level").toInt() == 0)
        fill_list();

}

void Interface::onloadPictureResult(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
       {
           QByteArray data = reply->readAll();
           QImage image = QImage::fromData(data).scaled(100, 100, Qt::KeepAspectRatio);
           SelectedUser.pixPhoto = QPixmap::fromImage(QImage::fromData(data).scaled(100, 100, Qt::KeepAspectRatio));
       }
    fillProfile();
}

void Interface::ongetUserResult(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    QJsonObject jv = root.value("data").toObject();

    SelectedUser.id_user = jv.value("polis").toString();
    SelectedUser.second_name = jv.value("second_name").toString();
    SelectedUser.first_name = jv.value("first_name").toString();
    SelectedUser.middle_name = jv.value("middle_name").toString();
    SelectedUser.time = jv.value("date").toString().mid(11);
    SelectedUser.date = QDate::fromString(jv.value("date").toString().left(10), "yyyy-MM-dd");
    SelectedUser.email = jv.value("email").toString();
    SelectedUser.phone = jv.value("phone").toString();
    SelectedUser.photo = jv.value("photo").toString();
    SelectedUser.sex = jv.value("sex").toString();

    if (jv.value("level").toInt() == 0)
    {
        loadPicture(SelectedUser.photo);
    }
}

void Interface::on_EnterButton_Clicked()
{
    auth();
}

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtNetwork>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <vector>
#include <QCalendarWidget>
#include <QLabel>
#include "user.h"

class Interface:  public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    void auth();
    void getRecords();
    void hide_auth_window();
    void fill_list();
    void draw_calendar();
    void addHistory();
    void hideListfucn();
    void loadPicture();
private:
    QGraphicsScene * scene;
    QLineEdit * editLogin;
    QLineEdit * editPassword;
    QListWidget * list;
    QPushButton * bt;
    QNetworkAccessManager * net;
    QCalendarWidget * calendar;
    QPushButton * showButton;
    QPushButton * backButton;
    QLabel * label;

    QString token = "";
    QString str = "";
    int level = 999;
    //QString name = "";

    std::vector<MyUser> mas;

    QByteArray postData;
    QNetworkRequest request;
private slots:
    void onAuthResult(QNetworkReply *reply);
    void ongetRecordsResult(QNetworkReply *reply);
    void onloadPictureResult(QNetworkReply *reply);
    void on_EnterButton_Clicked();
    void itemClicked(QListWidgetItem* item);
    void calendarSelection();
    void onbackButtonClick();
};

#endif // INTERFACE_H

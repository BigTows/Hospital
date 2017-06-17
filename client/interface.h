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


class Interface:  public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    void main_func();
    void auth();
    void getRecords();
    void hide_auth_window();
    void draw_list();
    void draw_calendar();
    void addHistory();
private:
    QGraphicsScene * scene;
    QLineEdit * editLogin;
    QLineEdit * editPassword;
    QListWidget * list;
    QPushButton * bt;
    QNetworkAccessManager * net;
    QCalendarWidget * calendar;

    QString token = "";
    QString str = "";
    QString date = "";
    int level = 999;
    QString name = "";

    std::vector<QString> mas;

    QByteArray postData;
    QNetworkRequest request;
private slots:
    void onAuthResult(QNetworkReply *reply);
    void ongetRecordsResult(QNetworkReply *reply);
    void on_EnterButton_Clicked();
    void itemClicked(QListWidgetItem* item);
    void on_showbt_Clicked();
};

#endif // INTERFACE_H

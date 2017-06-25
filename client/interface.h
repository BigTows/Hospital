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
#include <QFrame>
#include <QVBoxLayout>
#include <windows.h>

class Interface:  public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    void auth();
    void getRecords(bool from, QDate date);
    void hide_auth_window();
    void fill_list();
    void draw_calendar();
    void addHistory();
    void hideListfucn();
    void loadPicture(QString photo);
    void getUser();
    void updateCalendar();
    void fillProfile();
    void blink();
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
    QFrame * frame;
    QTimer * timer;
    QVBoxLayout * layout;

    QString token = "";
    QString str_getText = "";
    QEventLoop loop;

    std::vector<MyUser> mas;
    QList< QLabel*> mas_label;
    MyUser SelectedUser;

    QByteArray postData;
    QNetworkRequest request;
private slots:
    void onAuthResult(QNetworkReply *reply);
    void ongetRecordsResult(QNetworkReply *reply);
    void onloadPictureResult(QNetworkReply *reply);
    void ongetUserResult(QNetworkReply *reply);
    void on_EnterButton_Clicked();
    void itemDoubleClicked(QListWidgetItem* item);
    void itemClicked(QListWidgetItem* item);
    void calendarSelection();
    void onbackButtonClick();
    void onTimerTimeout();
};

#endif // INTERFACE_H

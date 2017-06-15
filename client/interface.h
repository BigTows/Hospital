#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtNetwork>
#include <QLineEdit>
#include <QPushButton>


class Interface:  public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    void main_func();
    void auth();
    void getRecords();
    static QString editLoginText();
    static QString editPasswordText();
private:
    QGraphicsScene * scene;
    QLineEdit * editLogin;
    QLineEdit * editPassword;
    QPushButton * bt;
    QNetworkAccessManager * net;
    QString token = "";
    int level = 999;
    QString name = "";
    QByteArray postData;
    QNetworkRequest request;
private slots:
    void onAuthResult(QNetworkReply *reply);
    void ongetRecordsResult(QNetworkReply *reply);
    void on_EnterButton_Clicked();
};

#endif // INTERFACE_H

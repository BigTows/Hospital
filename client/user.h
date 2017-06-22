#ifndef USER_H
#define USER_H

#include <QPixmap>
#include <QString>

struct MyUser
{
    QString id_user;
    QString first_name;
    QString second_name;
    QString middle_name;
    QDate date;
    QString time;
    QString email;
    QString phone;
    QString photo;
    QString sex;
    QPixmap pixPhoto;
};


#endif // USER_H

#ifndef USER_H
#define USER_H

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
};


#endif // USER_H

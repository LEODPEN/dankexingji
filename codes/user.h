#ifndef USER_H
#define USER_H


#include<QString>
#include<QApplication>
class Room;
class User
{
public:
    User() {}
    User(QString account,QString password);
    QString setAccount();
    QString setPassword();
    QString resetPassword(QString newPassword);
    bool check(QString input);
    QString account;
    QString password;
};
#endif // USER_H

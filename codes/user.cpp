#include "user.h"
#include <QString>

User::User(QString account, QString password):
    account(account),password(password){}


QString User::setAccount()
{return account;}

QString User::setPassword()
{return password;}

QString User::resetPassword(QString newPassword)
{password=newPassword;return password;}

bool User::check(QString input)
{if(input==password)return true;
else return false;}

#ifndef MANAGER_H
#define MANAGER_H

#include"hotel.h"
#include"room.h"
#include"user.h"
#include"database.h"
#include<QList>
#include<QVector>
#include <QString>
class Room;
class Hotel;
class managerwindow;
class Manager: public User
{
    friend class Database;
public:
    QString myHName;
    Manager(){}
    Manager(QString account, QString password,QString myHName);
    void setParent(managerwindow* parent);
    void checkin(Room* pRoom);

};

#endif // MANAGER_H

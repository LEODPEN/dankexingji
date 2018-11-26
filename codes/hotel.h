#ifndef HOTEL_H
#define HOTEL_H

#include <QString>
#include"manager.h"
#include"room.h"
#include"database.h"
#include"enum.h"

class Customer;
class Manager;
class Room;
class Hotel
{
    friend class Database;
    friend class edithotel;
public:
    Hotel() {}
    //用于显示在酒店页面上的构造函数
    Hotel(QString hotelName,enumLoc Location,QString Tel,double Point);
    //用于数据库读写时的构造函数
    Hotel(QString hotelName, QString location, QString Tel,double Point,int cusNum);
    //获得顾客评价
    double getPoint();
    //设为酒店评价
    void setPoint(double);
    //得到顾客的5分评价，后面的函数以此类推
    void get5();
    void get4();
    void get3();
    void get2();
    void get1();
    //显示酒店名称
    QString showHName();
    //显示位置
    QString showLocation();
    //显示电话
    QString showTel();
    //显示评价
    QString showPoint();
    int cusTotal;
private:
    QString hotelName;
    //枚举型的位置
    enumLoc Location;
    //电话
    QString Tel;
    //评价
    double Point;
    //总评价人数
};


#endif // HOTEL_H

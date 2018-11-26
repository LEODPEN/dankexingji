#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include"hotel.h"
#include"customer.h"
#include"manager.h"
#include"editroom.h"
#include"database.h"
#include"enum.h"
class customerwindow;
class Customer;
class Manager;

class Room
{
    friend class editroom;
    friend class Database;
    friend class Customer;
    friend class Manager;
public:
    Room(){Sum=-1;State=none;}
    //用于显示在各个窗口上的构造函数
    Room(QString roomName,enumKind Kind,int Price,QString Description,int Sum,enumState State);
    //用于数据库读写的构造函数
    Room(QString roomName,QString kind,int Price,QString Description,int Sum,QString state);
    //在选定一个房间预定时，myRoom会copy这个房间的信息
    void copy(Room &pRoom);
    //显示房间名
    QString showRName();
    //显示房间类型
    QString showKind();
    //显示价格
    QString showPrice();
    //显示描述
    QString showDes();
    //显示余量
    QString showSum();
    //显示状态
    QString showState();
    //显示对应的酒店名
    QString showHotelName();
    //显示对应的顾客账号
    QString showcusAccount();
    //获取状态
    enumState getState();
    //通过酒店名称和酒店绑定
    void ConnectToHotel(QString hName);
    //通过顾客账号和顾客绑定
    void ConnectToCus(QString mAccount);
    //状态变为“未预订”，后面的以此类推
    void StateToNone();
    void StateToObserved();
    void StateToOccupied();
    void StateToPayback();
    void StateToEnded();
    //余量加一
    void plusSum();
    //余量减一
    void minusSum();
    QString getRoomname(){return roomName;}
    int Sum;
 private:
    enumKind Kind;
    enumState State;
    int Price;
    QString roomName;
    QString Description;
    QString hotelName;
    //房间对应的顾客账号
    QString cusAccount;

};
#endif // ROOM_H

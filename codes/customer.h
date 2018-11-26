#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "user.h"
#include"hotel.h"
#include"database.h"
#include<QString>
#include<QVector>
using namespace std;
class customerwindow;
class Room;
class Hotel;
class Customer : public User
{
friend class Database;
friend class bosswindow;
public:
    //顾客订单上的房间，只能加入一间,初始化这个房间,用初始状态来进行后面的判定操作
    Room *myRoom;//room*
    //我的记录里的房间列表
    QVector<Room> myRecord;
    Customer(){}
    Customer(QString account, QString password,int bill);
    void setParent(customerwindow* parent);
    void setHotel(Hotel* rowHotel);
    QString showHotelName();
    int showBill();
    Hotel* getHotel();
    int totalbill;
    int bill;
public slots:
    void CusLogout();
private:
    customerwindow*parent;

    Hotel* pHotel;
};
#endif // CUSTOMER_H

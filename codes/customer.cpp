#include "customer.h"
#include"customerwindow.h"
#include"ui_customerwindow.h"
#include<QDebug>


//所有需要处理的房间订单列表
extern QList<Room*>WaitingList;
//所有的房间列表
extern QVector<Room>roomList;
//所有的酒店列表
extern QVector<Hotel>hotelList;


//构造函数及初始化
Customer::Customer(QString account, QString password, int bill):
    User(account,password),bill(bill)
{
    parent=NULL;
    pHotel=NULL;
    myRoom=NULL;
    totalbill=bill;
    this->bill=0;
}

//与顾客窗口绑定
void Customer::setParent(customerwindow *parent)
{this->parent=parent;}

//顾客选定酒店后和酒店绑定
void Customer::setHotel(Hotel *rowHotel)
{this->pHotel=rowHotel;}

//显示顾客所在的酒店名称
QString Customer::showHotelName()
{return pHotel->showHName();}

//显示消费金额
int Customer::showBill()
{return bill;}

Hotel* Customer::getHotel()
{return pHotel;}


//顾客结束行程时的清空函数
void Customer::CusLogout()
{
    //对应客房余量加一
    for(int i=0;i<roomList.size();i++)
        if(myRoom->roomName==roomList[i].showRName())
           { roomList[i].plusSum();break;}
    //该房间信息被加入“我的记录”
    myRecord.append(*myRoom);
    //房间状态重新变成“未预订”
    myRoom=NULL;
    //消费金额清零
    //totalbill+=bill;
    bill=0;
    pHotel=NULL;
    parent=NULL;
    return;
}





















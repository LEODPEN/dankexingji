#include "room.h"
Room::Room(QString roomName,enumKind Kind, int Price, QString Description, int Sum,enumState State):
Kind(Kind),Price(Price),Description(Description),Sum(Sum),State(State)
{
    State=none;
    this->roomName=QString(roomName);
    this->Description=QString(Description);
}

Room::Room(QString roomName,QString kind, int Price, QString Description, int Sum,QString state):
Price(Price),Sum(Sum)
{
    if(kind=="单人间")Kind=single;
    if(kind=="大床房")Kind=couple;
    if(kind=="标间")Kind=friends;
    if(kind=="家庭房")Kind=family;
    if(kind=="套房")Kind=suite;

    if(state=="未预订")State=none;
    if(state=="付款并预定")State=observed;
    if(state=="入住")State=occupied;
    if(state=="退款")State=payback;
    if(state=="退房")State=ended;
    this->roomName=QString(roomName);
    this->Description=QString(Description);
}

void Room::copy(Room &pRoom)
{
    roomName=QString(pRoom.getRoomname());
    if(pRoom.showKind()=="单人间")Kind=single;
    if(pRoom.showKind()=="大床房")Kind=couple;
    if(pRoom.showKind()=="标间")Kind=friends;
    if(pRoom.showKind()=="家庭房")Kind=family;
    if(pRoom.showKind()=="套房")Kind=suite;
    State=observed;
    Sum=pRoom.showSum().toInt();
    Price=pRoom.showPrice().toInt();
    Description=QString(pRoom.showDes());
    hotelName=QString(pRoom.showHotelName());
}

QString Room::showRName(){return roomName;}
QString Room::showHotelName(){return hotelName;}
QString Room::showcusAccount(){return cusAccount;}
QString Room::showSum(){return QString::number(Sum);}
QString Room::showPrice(){return QString::number(Price);}
QString Room::showDes(){return Description;}
enumState Room::getState(){return State;}

QString Room::showKind(){
    switch (Kind) {
    case single:return(QString(QStringLiteral("单人间")));
    case couple:return(QString(QStringLiteral("大床房")));
    case friends:return(QString(QStringLiteral("标间")));
    case family:return(QString(QStringLiteral("家庭房")));
    case suite:return(QString(QStringLiteral("套房")));
    default:return QString();
    }
}
QString Room::showState(){
    switch (State) {
    case none:return(QString(QStringLiteral("未预订")));
    case observed:return(QString(QStringLiteral("预订并付款")));
    case occupied:return(QString(QStringLiteral("入住")));
    case payback:return(QString(QStringLiteral("退款")));
    case ended:return(QString(QStringLiteral("退房")));
    default:return QString();
    }
}

void Room::StateToNone()
{
    State=none;
}
void Room::StateToObserved()
{
    State=observed;
}

void Room::StateToOccupied()
{
    State=occupied;
}
void Room::StateToPayback()
{
     State=payback;
}
void Room::StateToEnded()
{
   State=ended;
}

void Room::plusSum()
{
    this->Sum++;
}

void Room::minusSum()
{
    this->Sum--;
}
void Room::ConnectToHotel(QString hName)
{
    hotelName=hName;
}
void Room::ConnectToCus(QString mAccount)
{
    cusAccount=mAccount;
}

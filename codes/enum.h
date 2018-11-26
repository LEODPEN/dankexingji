#ifndef ENUM_H
#define ENUM_H
#include "room.h"
#include"hotel.h"
class Hotel;
class Room;
//客房房型：单人间，大床房，标间，家庭房，套房
enum enumKind{single,couple,friends,family,suite};
//客房状态：未预订，预订并付款，入住，退款，退房
enum enumState{none,observed,occupied,payback,ended};
//地区
enum enumLoc{Haidian,Chaoyang,Fengtai,Dongcheng,Xicheng};
//QList<Room*>rList;
//QList<Hotel*>hList;


#endif // ENUM_H

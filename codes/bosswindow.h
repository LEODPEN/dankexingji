#ifndef BOSSWINDOW_H
#define BOSSWINDOW_H
#include<QList>
#include <QMainWindow>
#include"boss.h"
#include"loginwindow.h"
#include"hotel.h"
#include"room.h"
#include"editroom.h"
#include"edithotel.h"
#include"addroom.h"
#include"addaccount.h"
#include"addhotel.h"
#include"customer.h"
#include"enum.h"
namespace Ui
{
  class bosswindow;
}
class Room;
class Customer;
class editroom;
class edithotel;
class addroom;
class addaccount;
class addman;
class addhotel;
class Boss;
class Manager;
class Hotel;

class bosswindow:public QMainWindow
{
    Q_OBJECT
public:
    explicit bosswindow(loginwindow*parent,Boss*pBoss);
    ~bosswindow();
    Room* getRoom(int row);
    Hotel* getHotel(int row);
private:
    Ui::bosswindow *ui;
    Boss*pBoss;
    loginwindow*parent;
    editroom*w1;
    addroom*w2;
    addaccount*w3;
    addhotel*w4;
    edithotel*w5;
    QList<Customer*>cusList;
    QList<Manager*>mList;
    QList<Room*>rList;
    QList<Hotel*>hList;
private slots:void roomQuery1();
              void roomQuery2();
              void hotelQuery1();
              void hotelQuery2();
              void roomEdit();
              void roomAdd();
              void roomDel();
              void logout();
              void exitProgram();
              void cusQuery();
              void cusDel();
              void manAdd();
              void manDel();
              void manQuery();
              void hotelAdd();
              void hotelDel();
              void hotelEdit();
              void save();
public slots:void roomShow();
             void cusShow();
             void manShow();
             void hotelShow();
};

#endif // BOSSWINDOW_H




















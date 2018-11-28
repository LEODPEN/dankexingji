/*   
    copyright@pfdsh 
            446110075@qq.com 
*/
#include"loginwindow.h"
#include"customerwindow.h"
#include"hotel.h"
#include"room.h"
#include"customer.h"
#include"manager.h"
#include"database.h"
#include"boss.h"
#include"executive.h"
#include"enum.h"
#include <QApplication>
#include<QVector>
#include<QList>
using namespace std;
QVector<Hotel>decideList;//new hotel
QVector<Manager>manList;//1 to 1
QVector<Room> roomList;// all
QVector<Hotel>hotelList;// all
QVector<Customer> customerList;
QVector<Executive>exeList;//1
QVector<Boss>bossList;//1
QList<Room*> WaitingList;// 1 to many
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginwindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground,true);
    w.show();
    Database myDatabase;
    myDatabase.memory();
    /*Hotel wtf("酒店一",Haidian,"1008611",0.0);
    hotelList.push_back(wtf);
    Manager fwtf("2017011888","123456","酒店一");
    manList.push_back(fwtf);*/
    //Customer pf("18782515896","123456",0);
    //customerList.push_back(pf);
    //customerwindow w1(&w,&pf);
    //w1.show();
    return a.exec();
}

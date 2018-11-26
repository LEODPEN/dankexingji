#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H
#include <QMainWindow>
#include<QtWidgets>
#include"ui_customerwindow.h"
#include"hcomment.h"
#include"qwidget.h"
#include"loginwindow.h"
#include"customer.h"
#include"hotel.h"
#include"room.h"
#include"enum.h"
#include<QVector>
using namespace std;
extern QVector<Room>roomList;
extern QVector<Hotel>hotelList;
namespace Ui {
class customerwindow;
}
class loginwindow;
class customerwindow:public QMainWindow
{
    Q_OBJECT
public:
    customerwindow(){}
    explicit customerwindow(loginwindow *parent,Customer *pCustomer);
    ~customerwindow();
    Room *getRoom(int row);
    Hotel *getHotel(int row);
private slots:
    //进入酒店
    void triggerIn();
    //按名称查询酒店
    void triggerQueryH1();
    //按位置查询酒店
    void triggerQueryH2();
    //按名称查询客房
    void triggerQueryR1();
    //按客房类型查询酒店
    void triggerQueryR2();
    //预订某客房并付款
    void triggerSend();
    //显示全部房间列表
    void triggershowR();
    //显示全部酒店列表
    void triggershowH();
    //退款
    void triggerPayback();
    //退房
    void triggerEnd();
    //结束行程
    void leave();
    //评价酒店
    void commentOnHotel();
    //储存信息
    void save();
public slots:
    //退出登录
    void logout();
    //退出系统
    void exitProgram();
    //显示最近订单
    void showOrder();
    //显示我的记录
    void showRecord();
private:
    Ui::customerwindow *ui;
    //评价酒店的窗口
    hcomment*w1;
    loginwindow*parent;
    Customer* pCustomer;
    //用来指我的记录的房间列表的指针
    QVector<Room*>record;
    QList<Room*>rList;
    QList<Hotel*>hList;
};
#endif // CUSTOMERWINDOW_H

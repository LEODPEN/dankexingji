#include"executive.h"
#include "database.h"
#include "customer.h"
#include"boss.h"
#include"room.h"
#include"hotel.h"
extern QVector<Room>roomList;
extern QVector<Hotel>hotelList;
extern QVector<Customer>customerList;
extern QList<Room*>WaitingList;
extern QVector<Manager>manList;
extern QVector<Boss>bossList;
extern QVector<Executive>exeList;
Database::Database()
{
    createConnection();
    createTables();
}
Database::~Database(){}
bool Database::createConnection()
{
    db=QSqlDatabase::addDatabase("QSQLITE","connection");
    db.setDatabaseName("dsh.db");
    db.setUserName("dsh");
    db.setPassword("dsh");
    if(!db.open())
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("打开数据库失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        return false;
    }
     return true;
}
bool Database::createTables()
{
    QSqlQuery query(db);
    //创建顾客表
    query.prepare("create table IF NOT EXISTS Customer"
                "(account VARCHAR PRIMARY KEY,password  VARCHAR,bill INT)");
    if(!query.exec())
    {
        QMessageBox msg;
        msg.setText("Fatal error!Failed to create table Customer!");
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        return false;
    }
    //创建老板表
    query.prepare("create table IF NOT EXISTS Boss"
                "(account VARCHAR PRIMARY KEY,password  VARCHAR)");
    if (!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Boss!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
    //创建经理表
    query.prepare("create table IF NOT EXISTS Manager"
                "(account VARCHAR PRIMARY KEY,password  VARCHAR,hotelname  VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Manager!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
    //创建系统管理员表
    query.prepare("create table IF NOT EXISTS Executive"
                "(account VARCHAR PRIMARY KEY,password  VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Executive!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
    //创建房间表
    query.prepare("create table IF NOT EXISTS Room"
                "(roomName VARCHAR,Price INT,Sum INT,kind VARCHAR,Description VARCHAR,State VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Room!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
    //创建酒店表
    query.prepare("create table IF NOT EXISTS Hotel"
                "(hotelName VARCHAR,location VARCHAR,Tel VARCHAR,Point DOUBLE,cusTotal INT)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table hotelList!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
}
//打开数据库初始化顾客列表
bool Database::initialCustomer()
{
    QSqlQuery query(db);
    query.exec("select * from Customer");
    while(query.next())
    {
        QString account=query.value(0).toString();
        QString password=query.value(1).toString();
        int bill=query.value(2).toInt();
        Customer c(account,password,bill);
        customerList.append(c);
    }
    return true;
}
//打开数据库初始化酒店老板列表
bool Database::initialBoss()
{
    QSqlQuery query(db);
    query.exec("select*from Boss");
    while(query.next())
   {
    QString account=query.value(0).toString();
    QString password=query.value(1).toString();
    Boss b(account,password);
    bossList.append(b);
   }
    return true;
}
//初始化经理列表
bool Database::initialManager()
{
    QSqlQuery query(db);
    query.exec("select*from Manager");
    while(query.next())
    {
        QString account=query.value(0).toString();
        QString password=query.value(1).toString();
        QString myHName=query.value(2).toString();
        Manager m(account,password,myHName);
        manList.append(m);
    }
    return true;
}
//初始化系统管理员列表
bool Database::initialExecutive()
{
    QSqlQuery query(db);
    query.exec("select * from Executive");
    while(query.next())
    {
        QString account=query.value(0).toString();
        QString password=query.value(1).toString();
        Executive e(account,password);
        exeList.append(e);
    }
    return true;
}
//初始化客房
bool Database::initialRoom()
{
    QSqlQuery query(db);
    query.exec("select * from Room");
    while(query.next())
    {
        QString roomName=query.value(0).toString();
        QString kind=query.value(1).toString();
        int price=query.value(2).toInt();
        QString Description=query.value(3).toString();
        int Sum=query.value(4).toInt();
        QString State=query.value(5).toString();
        Room r(roomName,kind,price,Description,Sum,State);
        roomList.append(r);
    }
    return true;
}
//初始化酒店
bool Database::initialHotel()
{
    QSqlQuery query(db);
    query.exec("select * from Hotel");
    while(query.next())
    {
        QString hotelName=query.value(0).toString();
        QString location=query.value(1).toString();
        QString Tel=query.value(2).toString();
        double Point=query.value(3).toDouble();
        int cusNum = query.value(4).toInt();
        Hotel h(hotelName,location,Tel,Point,cusNum);
        //Hotel(QString hotelName, QString location, QString Tel,double Point,int cusNum);
        hotelList.append(h);
    }
    return true;
}
bool Database::memory()
{
    QSqlQuery query(db);
    query.exec("DELETE from Boss");
    query.prepare("insert into Boss values(?,?)");
       query.bindValue(0,bossList[0].account);
       query.bindValue(1,bossList[0].password);
    bool success=query.exec();
    if(!success)
    {QMessageBox msg;
    msg.setText(QStringLiteral("更新老板表失败!"));
    msg.setWindowTitle(QStringLiteral("Error！"));
    msg.exec();
}
    query.exec("DELETE from Customer");
    query.prepare("insert into Customer values(?,?,?)");
    for(int i=0;i<customerList.size();i++)
      {
        query.bindValue(0,customerList[i].account);
        query.bindValue(1,customerList[i].password);
        query.bindValue(2,customerList[i].totalbill);
        bool success=query.exec();
        if(!success)
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新顾客表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}
    query.exec("DELETE from Executive");
    query.prepare("insert into Executive values(?,?)");
       query.bindValue(0,exeList[0].account);
        query.bindValue(1,exeList[0].password);
        if(!query.exec())
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新系统管理员表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}
    query.exec("DELETE from Manager");
    query.prepare("insert into Manager values(?,?,?)");
    for(int i=0;i<manList.size();i++)
      {
        query.bindValue(0,manList[i].account);
        query.bindValue(1,manList[i].password);
        query.bindValue(2,manList[i].myHName);
        bool success=query.exec();
        if(!success)
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新经理表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}
    query.exec("DELETE from Room");
    query.prepare("insert into Room values(?,?,?,?,?,?)");
    for(int i=0;i<roomList.size();i++)
      {
        query.bindValue(0,roomList[i].showRName());
        query.bindValue(1,roomList[i].showKind());
        query.bindValue(2,roomList[i].showPrice().toInt());
        query.bindValue(3,roomList[i].showDes());
        query.bindValue(4,roomList[i].showSum().toInt());
        query.bindValue(5,roomList[i].showState());
        bool success=query.exec();
        if(!success)
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新房间表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}
    query.exec("DELETE from Hotel");
    query.prepare("insert into Hotel values(?,?,?,?,?)");
    for(int i=0;i<hotelList.size();i++)
      { query.bindValue(0,hotelList[i].showHName());
        query.bindValue(1,hotelList[i].showLocation());
        query.bindValue(2,hotelList[i].showTel());
        query.bindValue(3,hotelList[i].getPoint());
        query.bindValue(4,hotelList[i].cusTotal);
        //Hotel(QString hotelName, QString location, QString Tel,double Point,int cusNum);
        bool success=query.exec();
        if(!success)
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新酒店表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}
        return true;
}

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include"bosswindow.h"
#include"customerwindow.h"
#include"managerwindow.h"
#include"executivewindow.h"
#include"customer.h"
#include"manager.h"
#include"executive.h"
#include"boss.h"
#include<QMessageBox>
#include"qstring.h"
#include"database.h"
extern QVector<Customer>customerList;
extern QVector<Boss>bossList;
extern QVector<Executive>exeList;
extern QVector<Manager>manList;

loginwindow::loginwindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::loginwindow)
{

    if(bossList.size()==0){
        Boss s;
        bossList.push_back(s);
    }
    if(exeList.size()==0)
    {
        Executive d;
        exeList.push_back(d);
    }
    Database myDataBase;
    myDataBase.initialExecutive();
    myDataBase.initialBoss();
    myDataBase.initialCustomer();
    myDataBase.initialRoom();
    myDataBase.initialManager();
    myDataBase.initialHotel();
     w1=NULL;
     w2=NULL;
     w3=NULL;
     w4=NULL;
     ui->setupUi(this);
     r=new registerwindow(this);
     connect(ui->bRegister,SIGNAL(clicked(bool)),r,SLOT(show()));
     connect(ui->bRegister,SIGNAL(clicked()),this,SLOT(hide()));
     connect(ui->bLogin,SIGNAL(clicked()),this,SLOT(login()));
 }

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::login()
{
    QString account=ui->lAccount->text();
    QString password=ui->lPassword->text();
    if(account.isEmpty())
    {
        QMessageBox msgBox;
         msgBox.setText(QStringLiteral("请输入账号！"));
         msgBox.setWindowTitle(QStringLiteral("Error！"));
         msgBox.exec();return;
    }
if(password.isEmpty())
{
    QMessageBox msgBox;//密码不能为空
     msgBox.setText(QStringLiteral("请输入密码！"));
     msgBox.setWindowTitle(QStringLiteral("Error！"));
     msgBox.exec();return;
}
for(int i=0;i<customerList.size();i++)
      if(customerList.size()!=0&&account==customerList[i].setAccount())//先从顾客列表里进行查找
           { if(customerList[i].check(password))//判断账号密码是否吻合，如果相符进入顾客界面
                {if (w1!=NULL) {delete w1; w1=NULL;}
                 if (w2!=NULL) {delete w2; w2=NULL;}
                 if (w3!=NULL) {delete w3; w3=NULL;}
                 if (w4!=NULL) {delete w4; w4=NULL;}
                 w1=new customerwindow(this,&customerList[i]);
                 this->close();
                 w1->show();return;}
             else {QMessageBox msgBox;//如果不符，提示错误
                   msgBox.setText(QStringLiteral("手机号或密码错误！"));
                   msgBox.setWindowTitle(QStringLiteral("Error！"));
                   msgBox.exec();return;}}
for(int i=0;i<bossList.size();i++)//再从酒店老板列表里进行查找，同理
          if(bossList.size()!=0&&account==bossList[i].setAccount())
                   { if(bossList[i].check(password))
                    {if (w1!=NULL) {delete w1; w1=NULL;}
                     if (w2!=NULL) {delete w2; w2=NULL;}
                     if (w3!=NULL) {delete w3; w3=NULL;}
                     if (w4!=NULL) {delete w4; w4=NULL;}
                     w2=new bosswindow(this,&bossList[i]);
                     this->close();
                     w2->show();return;}
                 else {QMessageBox msgBox;
                      msgBox.setText(QStringLiteral("工作证号或密码错误！"));
                      msgBox.setWindowTitle(QStringLiteral("Error！"));
                      msgBox.exec();return;}}
for(int i=0;i<manList.size();i++)//再从酒店经理列表里进行查找，同理
          if(manList.size()!=0&&account==manList[i].setAccount())
                   { if(manList[i].check(password))
                    {if (w1!=NULL) {delete w1; w1=NULL;}
                     if (w2!=NULL) {delete w2; w2=NULL;}
                     if (w3!=NULL) {delete w3; w3=NULL;}
                     if (w4!=NULL) {delete w4; w4=NULL;}
                     w3=new managerwindow(this,&manList[i]);
                     this->close();
                     w3->show();return;}
             else if(manList[i].setPassword()=="")
                    {QMessageBox msgBox;
                     msgBox.setText(QStringLiteral("请先注册！"));
                     msgBox.setWindowTitle(QStringLiteral("Error！"));
                     msgBox.exec();return;}
                else {QMessageBox msgBox;
                      msgBox.setText(QStringLiteral("工作证号或密码错误！"));
                      msgBox.setWindowTitle(QStringLiteral("Error！"));
                      msgBox.exec();return;}}
           //最后从系统管理员列表里进行查找,只有一个得默认加进去？
           if(account=="dsh"&&password=="123")//exeList[0].setAccount()
                { if(exeList[0].check(password))
                    {if (w1!=NULL) {delete w1; w1=NULL;}
                     if (w2!=NULL) {delete w2; w2=NULL;}
                     if (w3!=NULL) {delete w3; w3=NULL;}
                     if (w4!=NULL) {delete w4; w4=NULL;}
                     w4=new executivewindow(this,&exeList[0]);
                     this->close();
                     w4->show();return;}
                 else {QMessageBox msgBox;
                      msgBox.setText(QStringLiteral("工作证号或密码错误！"));
                      msgBox.setWindowTitle(QStringLiteral("Error！"));
                      msgBox.exec();return;}}
QMessageBox msgBox;//如果均没有找到，则提示注册信息
msgBox.setText(QStringLiteral("该用户不存在！"));
msgBox.setInformativeText(QStringLiteral("请注册信息！"));
msgBox.setWindowTitle(QStringLiteral("Error！"));
msgBox.exec();
}

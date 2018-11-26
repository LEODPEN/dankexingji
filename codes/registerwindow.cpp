#include "registerwindow.h"
#include "qmessagebox.h"
#include"qdebug.h"
#include"customerwindow.h"
#include"customer.h"
#include"manager.h"
#include"boss.h"
#include"loginwindow.h"
#include"executive.h"
#include<QObject>
extern QVector<Customer>customerList;
extern QVector<Boss>bossList;
extern QVector<Manager>manList;
extern QVector<Executive>exeList;
registerwindow::registerwindow(loginwindow*l):
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);
    parent=l;
    connect(ui->bCancel,SIGNAL(clicked()),parent,SLOT(show()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->bRegister,SIGNAL(clicked()),this,SLOT(sendInfo()));
}

registerwindow::~registerwindow()
{
    delete ui;
}
//检查账号密码是否合法
bool registerwindow::check()
{
    bool flag=true;
    if (password.length()<6||password.length()>15){
            QMessageBox msg;
            msg.setText(QStringLiteral("密码长度应在6至15位之间！"));
            msg.exec();
            flag=false;}
    else if (!(password2==password)) {
            QMessageBox msg;
            msg.setText(QStringLiteral("两次输入密码不同！"));
            msg.exec();
            flag=false;}
    else if(account.isEmpty())
          { QMessageBox msg;
             msg.setText(QStringLiteral("请输入手机号或工作证号！"));
             msg.exec();
             flag=false;}
    return flag;
}
//这个里面的信息没有包含酒店老板和系统管理员这样仅有一个的人
void registerwindow::sendInfo()
{
    account=ui->lAccount->text();
    password=ui->lPassword->text();
    password2=ui->lPassword2->text();
//如果账号密码合法，接下来检查是否已经注册
    if(check())
{
     //判断顾客是否已注册，手机号是否有效
    if (account.length()==11)
    {
        for(int i=0;i<customerList.size();i++)
            if(account==customerList[i].setAccount())
            {
                QMessageBox msg;
                msg.setText(QStringLiteral("该顾客已注册！"));
                msg.setWindowTitle(QStringLiteral("Error"));
                msg.exec();return;
            }
        //如果account是手机号检查是否均为数字
        for (int i=0;i<11;i++)
          if (!account[i].isNumber())
          { QMessageBox msg;
            msg.setText(QStringLiteral("手机号无效！"));
            msg.exec();return;}
        //注册成功
        Customer newCustomer(account,password,0);
        //Customer(QString account, QString password,int totalbill);
        customerList.push_back(newCustomer);
        QMessageBox msg;
        msg.setText(QStringLiteral("顾客注册成功！"));
        msg.setWindowTitle(QStringLiteral("Success"));
        msg.exec();
        this->close();
        parent->show();
    }
//现在检查酒店经理
else if(account.length()==10&&account.startsWith("2017011"))
{
    int i;
    for(i=0;i<manList.size();i++)
{
        if(account==manList[i].setAccount()&&manList[i].setPassword()!="")
        {QMessageBox msg;
            msg.setText(QStringLiteral("该经理已注册！"));
            msg.setWindowTitle(QStringLiteral("Error"));
            msg.exec();return;}
        if(account==manList[i].setAccount()&&manList[i].setPassword()==""){
                    manList[i].resetPassword(password);
                    QMessageBox msg;
                    msg.setText(QStringLiteral("经理注册成功！"));
                    msg.setWindowTitle(QStringLiteral("Success"));
                    msg.exec();
                    this->close();
                    parent->show();
                    return;}
}

    if(i==manList.size())
     {QMessageBox msg;
     msg.setText(QStringLiteral("注册信息无效！"));
     msg.setWindowTitle(QStringLiteral("Error"));
     msg.exec(); return;}
}
//如果账号密码不合法要报错
    else
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("注册信息无效！"));
        msg.setWindowTitle(QStringLiteral("Error"));
        msg.exec();
        return;
    }
}
else{QMessageBox msg;
    msg.setText(QStringLiteral("系统错误！"));
    msg.setWindowTitle(QStringLiteral("Error"));
    msg.exec();
    return;}

}
























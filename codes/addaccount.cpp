#include "addaccount.h"
#include "ui_addaccount.h"
#include<QMessageBox>
extern QVector<Manager>manList;
addaccount::addaccount(bosswindow *parent) :
    parent(parent),
    ui(new Ui::addaccount)
{
    ui->setupUi(this);
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(sendInfo()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));
}

addaccount::~addaccount()
{
    delete ui;
}
void addaccount::sendInfo(){
    temp1=ui->lAccount->text() ;
    if(ui->lAccount->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("工作证号不能为空！"));
        msg.exec();return;}
    if(!(temp1.startsWith("2017011"))||!(temp1.length()==10))
             {QMessageBox msg;
              msg.setText(QStringLiteral("经理工作证号不合法！"));
              msg.exec();return;}
    for(int i=0;i<manList.size();i++)
            if(temp1==manList[i].setAccount())
            {QMessageBox msg;
                msg.setText(QStringLiteral("该经理已存在！"));
                msg.exec();return;}
    temp2=ui->lmyHName->text();
    if(ui->lmyHName->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("所在酒店名不能为空！"));
        msg.exec();return;}
        Manager newManager(temp1,"",temp2);
        manList.append(newManager);
        QMessageBox msg;
        msg.setText(QStringLiteral("添加信息成功！"));
        msg.exec();
        parent->manShow();

    this->close();
}


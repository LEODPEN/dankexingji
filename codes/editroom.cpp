#include "editroom.h"
#include "ui_editroom.h"
#include"bosswindow.h"
#include<QMessageBox>

editroom::editroom(bosswindow* parent,Room*pRoom):
    parent(parent),pRoom(pRoom),
    ui(new Ui::editroom)
{
    ui->setupUi(this);
    ui->lRName->setText(pRoom->showRName());
    ui->lPrice->setText(pRoom->showPrice());
    ui->cKind->setCurrentText(pRoom->showKind());
    ui->lSum->setText(pRoom->showSum());
    ui->lDes->setText(pRoom->showDes());
    //打开窗口，但是还不能编辑
    ui->lPrice->setEnabled(false);
    ui->lRName->setEnabled(false);
    ui->lSum->setEnabled(false);
    ui->lDes->setEnabled(false);
    ui->cKind->setEnabled(false);
    connect(ui->bEdit,SIGNAL(clicked()),this,SLOT(edit()));
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(sendInfo()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));

}
//开始编辑客房信息
void editroom::edit()
{
    ui->lPrice->setEnabled(true);
    ui->lRName->setEnabled(true);
    ui->cKind->setEnabled(true);
    ui->lSum->setEnabled(true);
    ui->lDes->setEnabled(true);
}

void editroom::sendInfo(){
    newRName=ui->lRName->text();
    newPrice=ui->lPrice->text().toInt();
    newSum=ui->lSum->text().toInt();
    newDes=ui->lDes->text();
    int temp=ui->cKind->currentIndex();
    switch (temp) {
    case 1:newKind=single;newkind=QStringLiteral("单人间");break;
    case 2:newKind=couple;newkind=QStringLiteral("大床房");break;
    case 3:newKind=friends;newkind=QStringLiteral("标间");break;
    case 4:newKind=family;newkind=QStringLiteral("家庭房");break;
    case 5:newKind=suite;newkind=QStringLiteral("套房");break;
    default:break;
    }
    if(newRName==""||newPrice<=0)
       { QMessageBox msg;
        msg.setText(QStringLiteral("输入信息不合法"));
        msg.exec();return;}
    if(newDes==""||newSum<=0)
       { QMessageBox msg;
        msg.setText(QStringLiteral("输入信息不合法"));
        msg.exec();return;}
    pRoom->roomName=newRName;
    pRoom->Price=newPrice;
    pRoom->Kind=newKind;
    pRoom->Sum=newSum;
    pRoom->Description=newDes;
    QMessageBox msg;
    msg.setText(QStringLiteral("修改信息成功！"));
    msg.exec();
    parent->roomShow();
    this->close();
}
editroom::~editroom()
{
    delete ui;
}





















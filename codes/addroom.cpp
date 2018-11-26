#include "addroom.h"
#include "ui_addroom.h"
#include<QMessageBox>
extern QVector<Room>roomList;
addroom::addroom(bosswindow *parent) :
    parent(parent),
    ui(new Ui::addroom)
{
    ui->setupUi(this);
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(sendInfo()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));
}

addroom::~addroom()
{
    delete ui;
}
void addroom::sendInfo()
{
    newRName=ui->lRName->text();
    newPrice=ui->lPrice->text().toInt();
    newSum=ui->lSum->text().toInt();
    newDes=ui->lDes->text();
    int temp=ui->cKind->currentIndex();
    switch (temp)
    {
    case 1:newKind=single;newkind=QStringLiteral("单人间");break;
    case 2:newKind=couple;newkind=QStringLiteral("大床房");break;
    case 3:newKind=friends;newkind=QStringLiteral("标间");break;
    case 4:newKind=family;newkind=QStringLiteral("家庭房");break;
    case 5:newKind=suite;newkind=QStringLiteral("套房");break;
    default: break;
    }
    if(ui->lRName->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("客房名称不能为空！"));
        msg.exec();return;}
    if(ui->lPrice->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("尚未输入客房价格！"));
        msg.exec();return;}
    if(ui->lSum->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("尚未设置客房余量！"));
        msg.exec();return;}
    if(ui->lDes->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("尚未输入客房描述！"));
        msg.exec();return;}
    if(ui->lPrice->text()<=0)
       { QMessageBox msg;
        msg.setText(QStringLiteral("客房价格不合法！"));
        msg.exec();return;}
    if(ui->lSum->text()<=0)
       { QMessageBox msg;
        msg.setText(QStringLiteral("客房余量不合法！"));
        msg.exec();return;}
    if(ui->cKind->currentIndex()==0)
       { QMessageBox msg;
        msg.setText(QStringLiteral("未选择客房类型！"));
        msg.exec();return;}
    for(int i=0;i<roomList.size();i++)
        if(newRName==roomList[i].showRName())
        {QMessageBox msg;
            msg.setText(QStringLiteral("该客房已存在！"));
            msg.exec();return;
        }
    Room newRoom(newRName,newkind,newPrice,newDes,newSum,"none");//两种方式都可以
    //Room(QString roomName,QString kind,int Price,QString Description,int Sum,QString state);
    roomList.append(newRoom);
    QMessageBox msg;
    msg.setText(QStringLiteral("添加信息成功！"));
    msg.exec();
    parent->roomShow();
    this->close();
}

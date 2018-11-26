#include "addhotel.h"
#include "ui_addhotel.h"
#include<QMessageBox>
extern QVector<Hotel>hotelList;
extern QVector<Hotel>decideList;
addhotel::addhotel(bosswindow *parent):
    parent(parent),
    ui(new Ui::addhotel)
{
    ui->setupUi(this);
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(sendInfo()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));
}

addhotel::~addhotel()
{
    delete ui;
}
void addhotel::sendInfo()
{
    newHName=ui->lHName->text();
    newTel=ui->lTel->text();
    int temp=ui->cLoc->currentIndex();
    switch (temp) {
    case 1:newLoc=Haidian;newloc=QStringLiteral("海淀区");break;
    case 2:newLoc=Chaoyang;newloc=QStringLiteral("朝阳区");break;
    case 3:newLoc=Fengtai;newloc=QStringLiteral("丰台区");break;
    case 4:newLoc=Dongcheng;newloc=QStringLiteral("东城区");break;
    case 5:newLoc=Xicheng;newloc=QStringLiteral("西城区");break;
    default:
    break;
    }
    if(ui->lHName->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("酒店名称不能为空！"));
        msg.exec();return;}
    if(ui->lTel->text()=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("尚未输入联系电话！"));}
    //注意：酒店位置默认选择海淀区
    for(int i=0;i<hotelList.size();i++)
        if(newHName==hotelList[i].showHName())
        {QMessageBox msg;
            msg.setText(QStringLiteral("该酒店已存在！"));
            msg.exec();return;
        }
    Hotel newHotel(newHName,newLoc,newTel,0.0);
    decideList.push_back(newHotel);
    QMessageBox msg1;
    msg1.setText(QStringLiteral("申请已发出！"));
    msg1.exec();
    parent->hotelShow();
    this->close();
}

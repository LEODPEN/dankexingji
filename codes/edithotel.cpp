#include "edithotel.h"
#include "ui_edithotel.h"
#include"bosswindow.h"
#include<QMessageBox>

edithotel::edithotel(bosswindow *parent,Hotel*pHotel):
    parent(parent),pHotel(pHotel),
    ui(new Ui::edithotel)
{
    ui->setupUi(this);
    ui->lHName->setText(pHotel->showHName());
    ui->cLoc->setCurrentText(pHotel->showLocation());
    ui->lTel->setText(pHotel->showTel());
    //打开窗口，但是还不能编辑
    ui->lHName->setEnabled(false);
    ui->lTel->setEnabled(false);
    ui->cLoc->setEnabled(false);
    connect(ui->bEdit,SIGNAL(clicked()),this,SLOT(Hedit()));
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(HsendInfo()));
    connect(ui->bCancel,SIGNAL(clicked()),this,SLOT(close()));
}
//开始编辑酒店信息
void edithotel::Hedit()
{
    ui->lHName->setEnabled(true);
    ui->lTel->setEnabled(true);
    ui->cLoc->setEnabled(true);
}

void edithotel::HsendInfo(){
    newHName=ui->lHName->text();
    newTel=ui->lTel->text();
    int temp=ui->cLoc->currentIndex();
    switch (temp) {
    case 1:newLoc=Haidian;newloc=QStringLiteral("海淀区");break;
    case 2:newLoc=Chaoyang;newloc=QStringLiteral("朝阳区");break;
    case 3:newLoc=Fengtai;newloc=QStringLiteral("丰台区");break;
    case 4:newLoc=Dongcheng;newloc=QStringLiteral("东城区");break;
    case 5:newLoc=Xicheng;newloc=QStringLiteral("西城区");break;
    default: break;
    }
    if(newHName==""||newTel=="")
       { QMessageBox msg;
        msg.setText(QStringLiteral("输入信息不合法"));
        msg.exec();return;}
    pHotel->Location=newLoc;
    pHotel->hotelName=newHName;
    pHotel->Tel=newTel;
    QMessageBox msg;
    msg.setText(QStringLiteral("修改信息成功！"));
    msg.exec();
    parent->hotelShow();
    this->close();
}
edithotel::~edithotel()
{
    delete ui;
}


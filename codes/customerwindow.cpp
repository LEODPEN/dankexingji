#include "customerwindow.h"
#include "ui_customerwindow.h"
#include"qmessagebox.h"
#include"qtablewidget.h"
#include"customer.h"
#include"room.h"
#include"qwidget.h"
#include"QMainWindow.h"
#include<QString>
#include"hotel.h"
#include<QVector>
#include<QList>
using namespace std;
extern QVector<Room> roomList;
extern QVector<Hotel>hotelList;
extern QVector<Customer> customerList;
extern QList<Room*> WaitingList;
extern Database myDataBase;
customerwindow::customerwindow(loginwindow *parent,Customer*pCustomer) :
    parent(parent), pCustomer(pCustomer),w1(NULL),
    ui(new Ui::customerwindow)
{
    ui->setupUi(this);
    ui->lFull->hide();
    pCustomer->setParent(this);
    if(pCustomer->myRoom==NULL) { pCustomer->myRoom=new Room();}//是否新人
    //判断顾客是否已进入某酒店，如果已进入不可再进入其他酒店
    if(pCustomer->getHotel()!=NULL)
    {
        ui->bIn->setEnabled(false);
        //判断顾客是否已预订某房间,如果已预订不能再预定其他房间,未预订时对房间的所有操作不可用
        if(pCustomer->myRoom->Sum==-1||pCustomer->myRoom->getState()==none)
        {
            ui->bBook->setEnabled(true);
            ui->bPayback->setEnabled(false);
            ui->bEnded->setEnabled(false);
            ui->bComment->setEnabled(false);
            ui->bOut->setEnabled(false);
        }
        else
        {
            ui->bBook->setEnabled(false);

            if(pCustomer->myRoom->getState()==observed)
            {
                ui->bPayback->setEnabled(true);//预订后只选择退款
                ui->bEnded->setEnabled(false);
                ui->bComment->setEnabled(false);
                ui->bOut->setEnabled(false);
            }
            //入住后只可选择退房
            if(pCustomer->myRoom->getState()==occupied)
            {
                ui->bPayback->setEnabled(false);
                ui->bEnded->setEnabled(true);
                ui->bComment->setEnabled(false);
                ui->bOut->setEnabled(false);
            }
            //退款后只可选择结束行程
            if(pCustomer->myRoom->getState()==payback)
            {
                ui->bPayback->setEnabled(false);
                ui->bEnded->setEnabled(false);
                ui->bComment->setEnabled(false);
                ui->bOut->setEnabled(true);
            }
            //只有正常退房可以评价，新出来的需要样本，因此必须评价！
            if(pCustomer->myRoom->getState()==ended)
            {
                ui->bPayback->setEnabled(false);
                ui->bEnded->setEnabled(false);
                ui->bComment->setEnabled(true);
                ui->bOut->setEnabled(true);
            }
        }
    }
    else { ui->bIn->setEnabled(true); }
    triggershowH();
    triggershowR();
    showOrder();
    showRecord();
    //酒店页面上的信号和槽
    connect(ui->bshowH,SIGNAL(clicked()),this,SLOT(triggershowH()));
    connect(ui->bIn,SIGNAL(clicked()),this,SLOT(triggerIn()));
    connect(ui->bQueryH1,SIGNAL(clicked()),this,SLOT(triggerQueryH1()));
    connect(ui->bQueryH2,SIGNAL(clicked()),this,SLOT(triggerQueryH2()));
    //客房页面上的信号和槽
    connect(ui->bQueryR1,SIGNAL(clicked()),this,SLOT(triggerQueryR1()));
    connect(ui->bQueryR2,SIGNAL(clicked()),this,SLOT(triggerQueryR2()));
    connect(ui->bshowR,SIGNAL(clicked()),this,SLOT(triggershowR()));
    connect(ui->bBook,SIGNAL(clicked()),this,SLOT(triggerSend()));
    //最近订单上的信号和槽
    connect(ui->bmyRefresh,SIGNAL(clicked()),this,SLOT(showOrder()));
    connect(ui->bPayback,SIGNAL(clicked()),this,SLOT(triggerPayback()));
    connect(ui->bEnded,SIGNAL(clicked()),this,SLOT(triggerEnd()));
    connect(ui->bComment,SIGNAL(clicked()),this,SLOT(commentOnHotel()));
    connect(ui->bOut,SIGNAL(clicked()),this,SLOT(leave()));
    //我的记录上的信号和槽
    connect(ui->bLogout,SIGNAL(clicked()),this,SLOT(logout()));
    connect(ui->bExit,SIGNAL(clicked()),this,SLOT(exitProgram()));
    connect(ui->brr,SIGNAL(clicked()),this,SLOT(showRecord()));
}

customerwindow::~customerwindow()
{
    delete ui;
}
//将所指的客房行数转化为指针
Room* customerwindow::getRoom(int row)
{
    return rList[row];
}
//将所指的酒店行数转化为指针
Hotel* customerwindow::getHotel(int row)
{
    return hList[row];
}
//显示全部客房，如果客房余量为零，弹出提示且不可进行后续操作
void customerwindow::triggershowR()
{
    rList.clear();
    //清空两个搜索栏和之前的房间表里显示的东西
    ui->lQueryR->clear();
    ui->cQueryR->clear();
    ui->rTable->clear();
    //五栏信息
    ui->rTable->setColumnCount(5);
    ui->rTable->setRowCount(0);
    ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")) );
    ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")) );
    ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")) );
    ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")) );
    ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")) );
    //设置表格属性
    ui->rTable->setColumnWidth(0,450);
    ui->rTable->setColumnWidth(1,450);
    ui->rTable->setColumnWidth(2,250);
    ui->rTable->setColumnWidth(3,250);
    ui->rTable->setColumnWidth(4,550);
    //显示客房信息
    for(int i=0; i<roomList.size(); i++)
    {
        if(roomList[i].Sum!=0)
        {
            rList.push_back(&roomList[i]);
        }
    }
    ui->rTable->setRowCount(rList.size());
    for(int i =0; i<rList.size(); i++)
    {
        if(rList.size()!=0)
        {
            ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
            ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
            ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
            ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
            ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));
        }
    }
    //若顾客选择的客房余量为零不可进行对此房间的后续操作
    //要不然自动删除余量为零的在列表中
    return;
}
//显示全部酒店
void customerwindow::triggershowH()
{
    hList.clear();

    ui->lQueryH->clear();
    ui->cQueryH->clear();
    ui->hTable->clear();
    ui->hTable->setColumnCount(4);
    ui->hTable->setRowCount(0);
    ui->hTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->hTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("酒店位置")) );
    ui->hTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("联系电话")));
    ui->hTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("酒店评价")) );
    ui->hTable->setColumnWidth(0,650);
    ui->hTable->setColumnWidth(1,450);
    ui->hTable->setColumnWidth(2,450);
    ui->hTable->setColumnWidth(3,250);

    for(int i=0; i<hotelList.size(); i++)
    {
        hList.push_back(&hotelList[i]);
    }
        ui->hTable->setRowCount(hList.size());
    for(int i =0;i<hList.size();i++)
    {
        if(hList.size()!=0)
        {
            ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
            ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
            ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
            ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));
        }
    }
    return;
}
//查询酒店名称
void customerwindow::triggerQueryH1()
{
    if(ui->lQueryH->text()=="")
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入酒店名称！"));
        msg.exec();
        return;
    }
    hList.clear();
    ui->hTable->clear();
    ui->hTable->setColumnCount(4);
    ui->hTable->setRowCount(0);
    ui->hTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->hTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("酒店位置")) );
    ui->hTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("联系电话")));
    ui->hTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("酒店评价")) );
    ui->hTable->setColumnWidth(0,650);
    ui->hTable->setColumnWidth(1,450);
    ui->hTable->setColumnWidth(2,450);
    ui->hTable->setColumnWidth(3,250);
    QString temp=ui->lQueryH->text();
    int count=0;
    for(int i=0; i<hotelList.size(); i++)
        if(hotelList[i].showHName()==temp)
        {
            hList.append(&hotelList[i]);
            count++;
        }
    if(count==0)
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("您所查找的酒店不存在！"));
        msg.exec();
        return;
    }
    else
    {
        ui->hTable->setRowCount(hList.size());
        for(int i=0; i<hList.size(); i++)
        {
            ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
            ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
            ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
            ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));  
        }
    }
    return;
}
//查询房间名称
void customerwindow::triggerQueryR1()
{
    if(ui->lQueryR->text()=="")
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入客房名称！"));
        msg.exec();
        return;
    }
    rList.clear();
    ui->rTable->clear();
    ui->rTable->setColumnCount(5);
    ui->rTable->setRowCount(0);
    ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")) );
    ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")) );
    ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
    ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")) );
    ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")) );
    ui->rTable->setColumnWidth(0,450);
    ui->rTable->setColumnWidth(1,450);
    ui->rTable->setColumnWidth(2,250);
    ui->rTable->setColumnWidth(3,250);
    ui->rTable->setColumnWidth(4,550);
    QString temp=ui->lQueryR->text();
    int count=0;
    for(int i=0; i<roomList.size(); i++)
        if(roomList[i].showRName()==temp)
        {
            rList.append(&roomList[i]);
            count++;
        }
    if(count==0)
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("您所查找的客房不存在！"));
        msg.exec();
        return;
    }
    else
    {
        ui->rTable->setRowCount(rList.size());
        for(int i=0; i<rList.size(); i++)
        {
            ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
            ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
            ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
            ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
            ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));
        }
    }
    return;
}
//根据酒店位置查询酒店
void customerwindow::triggerQueryH2()
{
    hList.clear();
    QString temp=ui->cQueryH->currentText();
    ui->hTable->clear();
    ui->hTable->setColumnCount(4);
    ui->hTable->setRowCount(0);
    ui->hTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->hTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("酒店位置")) );
    ui->hTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("联系电话")));
    ui->hTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("酒店评价")) );
    ui->hTable->setColumnWidth(0,240);
    ui->hTable->setColumnWidth(1,240);
    ui->hTable->setColumnWidth(2,240);
    ui->hTable->setColumnWidth(3,240);
    for(int i=0; i<hotelList.size(); i++)
        if(hotelList[i].showLocation()==temp)//地区
        {
            hList.append(&hotelList[i]);
        }
    ui->hTable->setRowCount(hList.size());
    for(int i=0; i<hList.size(); i++)
    {
        if(hList.size()!=0){
        ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
        ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
        ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
        ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));}
    }
    return;
}

//根据客房类型查询客房
void customerwindow::triggerQueryR2()
{
    rList.clear();
    QString temp=ui->cQueryR->currentText();
    ui->rTable->clear();
    ui->rTable->setColumnCount(5);
    ui->rTable->setRowCount(0);
    ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")));
    ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")));
    ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
    ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")));
    ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")));
    ui->rTable->setColumnWidth(0,240);
    ui->rTable->setColumnWidth(1,240);
    ui->rTable->setColumnWidth(2,240);
    ui->rTable->setColumnWidth(3,240);
    ui->rTable->setColumnWidth(4,240);
    for(int i=0; i<roomList.size(); i++)
        if(roomList[i].showKind()==temp)
        {
            rList.append(&roomList[i]);
        }
    ui->rTable->setRowCount(rList.size());
    for(int i=0; i<rList.size(); i++)
            {
        if(rList.size()!=0){
                ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
                ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
                ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
                ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
                ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));
                           }
            }
    return;
}

//退出登录，顾客窗口关闭，登录窗口重新弹出，账号和密码栏均清空
void customerwindow::logout()
{
    if(pCustomer->myRoom->Sum==-1) {delete pCustomer->myRoom; pCustomer->myRoom=NULL;}
    this->close();
    parent->show();
    parent->ui->lPassword->clear();
    parent->ui->lAccount->clear();
    return;
}
//退出系统
void customerwindow::exitProgram()
{
    QMessageBox msgBox;
    msgBox.setFixedWidth(500);
    msgBox.setText(QStringLiteral("您确定要退出系统吗？"));
    msgBox.setInformativeText("请确认数据已保存");
    QPushButton *bYes=msgBox.addButton(QStringLiteral("是"),QMessageBox::ButtonRole::NoRole);
    QPushButton *bNo=msgBox.addButton(QStringLiteral("否"),QMessageBox::ButtonRole::NoRole);
    connect(bYes,SIGNAL(clicked()),&msgBox,SLOT(close()));
    connect(bYes,SIGNAL(clicked()),this,SLOT(close()));
    connect(bYes,SIGNAL(clicked()),this,SLOT(save()));
    connect(bNo,SIGNAL(clicked()),&msgBox,SLOT(close()));
    msgBox.exec();
    return;
}
void customerwindow::save()
{
    Database myDataBase;
    myDataBase.memory();
}
//退房后离开
void customerwindow::leave()
{
    //获取酒店评价
    if(pCustomer->getHotel()->getPoint()==5)
    { pCustomer->getHotel()->get5();}
    if(pCustomer->getHotel()->getPoint()==4)
    { pCustomer->getHotel()->get4();}
    if(pCustomer->getHotel()->getPoint()==3)
    { pCustomer->getHotel()->get3();}
    if(pCustomer->getHotel()->getPoint()==2)
    { pCustomer->getHotel()->get2();}
    if(pCustomer->getHotel()->getPoint()==1)
    { pCustomer->getHotel()->get1();}
    pCustomer->CusLogout();
    this->close();
    parent->show();
    parent->ui->lPassword->clear();
    return;
}
//显示最近订单
void customerwindow::showOrder()
{
    if(pCustomer->myRoom->Sum!=-1){
    ui->lHName->setText(QString(pCustomer->showHotelName()));
    ui->lRName->setText(QString(pCustomer->myRoom->showRName()));
    ui->lPrice->setText(QString(pCustomer->myRoom->showPrice()));
    ui->lState->setText(QString(pCustomer->myRoom->showState()));}
    return;
}

//显示我的记录
void customerwindow::showRecord()
{
    record.clear();
    ui->recordTable->clear();
    ui->recordTable->setColumnCount(3);
    ui->recordTable->setRowCount(0);
    ui->recordTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->recordTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房种类")) );
    ui->recordTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
    ui->recordTable->setColumnWidth(0,280);
    ui->recordTable->setColumnWidth(1,280);
    ui->recordTable->setColumnWidth(2,240);
    for(int i=0; i<pCustomer->myRecord.size(); i++)
    {record.push_back(&(pCustomer->myRecord[i]));}
    ui->recordTable->setRowCount(record.size());
    for(int i = 0; i < record.size(); i++)
    {
        if(record.size()!=0)
        {
            ui->recordTable->setItem(i,0,new QTableWidgetItem(record[i]->showHotelName()));
            ui->recordTable->setItem(i,1,new QTableWidgetItem(record[i]->showRName()));
            ui->recordTable->setItem(i,2,new QTableWidgetItem(record[i]->showPrice()));
        }
    }
    return;
}

void customerwindow::triggerSend()
{
    int row=ui->rTable->currentRow();
    if(row>=0)
    {
        //myRoom去copy选中的那个客房,该客房加入所有待处理的列表中
        for(int i=0; i<roomList.size(); i++)
            if(getRoom(row)->showRName()==roomList[i].showRName())
            {
                pCustomer->myRoom->copy(roomList[i]);
                pCustomer->myRoom->ConnectToCus(pCustomer->setAccount());
                pCustomer->myRoom->ConnectToHotel(pCustomer->showHotelName());
                WaitingList.append(pCustomer->myRoom);//这样才有对应cus关系和hotel关系
                pCustomer->bill=roomList[i].showPrice().toInt();
                roomList[i].minusSum();//总线加减
            }
        QMessageBox msg;
        msg.setText(QStringLiteral("已预订!"));
        msg.exec();
        showOrder();
        ui->bPayback->setEnabled(true);
        ui->bEnded->setEnabled(false);
        ui->bComment->setEnabled(false);
        ui->bOut->setEnabled(false);
        return;
    }
    else
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("未选中任何客房！"));
        msg.exec();
        return;
    }
}

//选择酒店进入酒店
void customerwindow::triggerIn()
{
    if(pCustomer->getHotel()!=NULL)
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("您已经进入某酒店界面，请在客房选择！"));
        msg.exec();
        ui->bIn->setEnabled(false);
        return;
    }
    else
    {
        int row=ui->hTable->currentRow();
        //将酒店所处的行数转化为酒店并设置按钮是否可用
        if(row>=0)
        {
            pCustomer->setHotel(getHotel(row));
            QMessageBox msg;
            msg.setText(QStringLiteral("您已成功入店！"));
            msg.exec();
            ui->bBook->setEnabled(true);
            ui->bPayback->setEnabled(false);
            ui->bEnded->setEnabled(false);
            ui->bComment->setEnabled(false);
            ui->bOut->setEnabled(false);
            return;
        }
        else
        {
            QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何酒店！"));
            msg.exec();
            ui->bBook->setEnabled(false);
            ui->bPayback->setEnabled(false);
            ui->bEnded->setEnabled(false);
            ui->bComment->setEnabled(false);
            ui->bOut->setEnabled(false);
            return;
        }
    }
}

//退款并设置按钮是否可用
void customerwindow::triggerPayback()
{

    pCustomer->myRoom->StateToPayback();
    ui->bPayback->setEnabled(false);
    ui->bEnded->setEnabled(false);
    ui->bComment->setEnabled(false);
    ui->bOut->setEnabled(true);
    QMessageBox msg;
    msg.setText(QStringLiteral("您已成功退款！"));
    msg.exec();
}

void customerwindow::triggerEnd()
{
    pCustomer->myRoom->StateToEnded();
    pCustomer->totalbill+=pCustomer->showBill();//计算总的钱！
    ui->bPayback->setEnabled(false);
    ui->bEnded->setEnabled(false);
    ui->bComment->setEnabled(true);
    ui->bOut->setEnabled(true);
    QMessageBox msg;
    msg.setText(QStringLiteral("您已成功退房！"));
    msg.exec();
}

// 评价酒店
void customerwindow::commentOnHotel()
{
    w1=new hcomment(this,pCustomer->getHotel(),pCustomer->myRoom);
    w1->show();
}

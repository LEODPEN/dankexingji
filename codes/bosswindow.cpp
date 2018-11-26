#include "bosswindow.h"
#include "ui_bosswindow.h"
#include"editroom.h"
#include<QMessageBox>
extern QVector<Room> roomList;
extern QVector<Hotel> hotelList;
extern QVector<Customer> customerList;
extern QVector<Manager>manList;
extern QList<Room*>WaitingList;
bosswindow::bosswindow(loginwindow* parent,Boss*pBoss):
    parent(parent),pBoss(pBoss),w1(NULL),w2(NULL),w3(NULL),w4(NULL),w5(NULL),
    ui(new Ui::bosswindow)
{
    ui->setupUi(this);
    pBoss->setParent(this);
    roomShow();
    cusShow();
    manShow();
    hotelShow();
    connect(ui->broomQuery1,SIGNAL(clicked()),this,SLOT(roomQuery1()));//按房间名查找房间
    connect(ui->broomQuery2,SIGNAL(clicked()),this,SLOT(roomQuery2()));//按类型名别查找房间
    connect(ui->broomShow,SIGNAL(clicked()),this,SLOT(roomShow()));//显示所有客房
    connect(ui->broomEdit,SIGNAL(clicked()),this,SLOT(roomEdit()));//编辑房间
    connect(ui->broomAdd,SIGNAL(clicked()),this,SLOT(roomAdd()));//添加房间
    connect(ui->broomDel,SIGNAL(clicked()),this,SLOT(roomDel()));//删除房间
    connect(ui->bcusShow,SIGNAL(clicked()),this,SLOT(cusShow()));//显示所有顾客
    connect(ui->bcusQuery,SIGNAL(clicked()),this,SLOT(cusQuery()));//查询顾客
    connect(ui->bcusDel,SIGNAL(clicked()),this,SLOT(cusDel()));//删除无效的顾客账号
    connect(ui->bmanShow,SIGNAL(clicked()),this,SLOT(manShow()));//显示所有经理信息
    connect(ui->bmanAdd,SIGNAL(clicked()),this,SLOT(manAdd()));//添加经理账号
    connect(ui->bmanDel,SIGNAL(clicked()),this,SLOT(manDel()));//删除无效的经理账号
    connect(ui->bmanQuery,SIGNAL(clicked()),this,SLOT(manQuery()));//查询经理账号
    connect(ui->bhotelAdd,SIGNAL(clicked()),this,SLOT(hotelAdd()));//添加酒店信息
    connect(ui->bhotelDel,SIGNAL(clicked()),this,SLOT(hotelDel()));//删除酒店信息
    connect(ui->bhotelEdit,SIGNAL(clicked()),this,SLOT(hotelEdit()));//编辑酒店信息
    connect(ui->bhotelQuery1,SIGNAL(clicked()),this,SLOT(hotelQuery1()));//按酒店名查找酒店
    connect(ui->bhotelQuery2,SIGNAL(clicked()),this,SLOT(hotelQuery2()));//按地区别查找酒店
    connect(ui->bhotelShow,SIGNAL(clicked()),this,SLOT(hotelShow()));//显示所有酒店
    connect(ui->bLogout,SIGNAL(clicked()),this,SLOT(logout()));//退出登录
    connect(ui->bExit,SIGNAL(clicked()),this,SLOT(exitProgram()));//退出系统
}
bosswindow::~bosswindow()
{
    delete ui;
}

Room* bosswindow::getRoom(int row)
{//将所指的房间行数转化为指针
    return rList[row];
}
Hotel* bosswindow::getHotel(int row)
{
    return hList[row];
}
void bosswindow::roomShow()
{//显示全部房间
   ui->lroomQuery->clear();
   rList.clear();
   ui->rTable->clear();
   ui->rTable->setColumnCount(5);
   ui->rTable->setRowCount(0);
   ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")) );
   ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")) );
   ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
   ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")) );
   ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")) );
   ui->rTable->setColumnWidth(0,240);
   ui->rTable->setColumnWidth(1,240);
   ui->rTable->setColumnWidth(2,240);
   ui->rTable->setColumnWidth(3,240);
   ui->rTable->setColumnWidth(4,240);
   for(int i=0;i<roomList.size();i++)
       rList.append(&roomList[i]);
   ui->rTable->setRowCount(rList.size());
   for(int i=0;i<rList.size();i++)
   {
       if(rList.size()!=0){
   ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
   ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
   ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
   ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
   ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));}}
   return;
}
//按名称查询客房
void bosswindow::roomQuery1()
{
    rList.clear();
    if(ui->lroomQuery->text()==""){
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入客房名称！"));
        msg.exec();
        return;}
    ui->rTable->clear();
    ui->rTable->setColumnCount(5);
    ui->rTable->setRowCount(0);
    ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")) );
    ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")) );
    ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
    ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")) );
    ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")) );
    ui->rTable->setColumnWidth(0,240);
    ui->rTable->setColumnWidth(1,240);
    ui->rTable->setColumnWidth(2,240);
    ui->rTable->setColumnWidth(3,240);
    ui->rTable->setColumnWidth(4,240);
    QString temp=ui->lroomQuery->text();
    for(int i=0;i<roomList.size();i++)
    if(roomList[i].showRName()==temp)
          { rList.append(&roomList[i]);}
    if(rList.size()==0){QMessageBox msg;
                msg.setText(QStringLiteral("您所查找的客房不存在！"));
                msg.exec();
                return;}
    else
    {ui->rTable->setRowCount(rList.size());
        for(int i=0;i<rList.size();i++)
                {
                 ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
                 ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
                 ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
                 ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
                 ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));}}
                 return;
}
//按房间类型查询客房
void bosswindow::roomQuery2()
{
    rList.clear();
    QString temp=ui->cQuery->currentText();
    ui->rTable->clear();
    ui->rTable->setColumnCount(5);
    ui->rTable->setRowCount(0);
    ui->rTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("客房名称")) );
    ui->rTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("客房类型")) );
    ui->rTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("客房价格")));
    ui->rTable->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("客房余量")) );
    ui->rTable->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("客房描述")) );
    ui->rTable->setColumnWidth(0,240);
    ui->rTable->setColumnWidth(1,240);
    ui->rTable->setColumnWidth(2,240);
    ui->rTable->setColumnWidth(3,240);
    ui->rTable->setColumnWidth(4,240);
    for(int i=0;i<roomList.size();i++)
    if(roomList[i].showKind()==temp)
          { rList.append(&roomList[i]);}
    ui->rTable->setRowCount(rList.size());
    for(int i=0;i<rList.size();i++)
                {
        if(rList.size()!=0){
                 ui->rTable->setItem(i,0,new QTableWidgetItem(rList[i]->showRName()));
                 ui->rTable->setItem(i,1,new QTableWidgetItem(rList[i]->showKind()));
                 ui->rTable->setItem(i,2,new QTableWidgetItem(rList[i]->showPrice()));
                 ui->rTable->setItem(i,3,new QTableWidgetItem(rList[i]->showSum()));
                 ui->rTable->setItem(i,4,new QTableWidgetItem(rList[i]->showDes()));}}
                 return;
}


void bosswindow::hotelShow()
{//显示全部酒店
   hList.clear();
   ui->lroomQuery->clear();
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
   for(int i=0;i<hotelList.size();i++)
       hList.append(&hotelList[i]);
   ui->hTable->setRowCount(hList.size());
   for(int i=0;i<hList.size();i++)
   {
       if(hList.size()!=0){
       ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
       ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
       ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
       ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));}}
   return;
}
//按名称查询酒店
void bosswindow::hotelQuery1()
{
    if(ui->lhotelQuery->text()==""){
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入酒店名称！"));
        msg.exec();
        return;}
    hList.clear();
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
    QString temp=ui->lhotelQuery->text();
    for(int i=0;i<hotelList.size();i++)
    if(hotelList[i].showHName()==temp)
          { hList.append(&hotelList[i]);}
    if(hList.size()==0){QMessageBox msg;
                msg.setText(QStringLiteral("您所查找的酒店不存在！"));
                msg.exec();
                return;}
    else
    {
        ui->hTable->setRowCount(hList.size());
        for(int i=0;i<hList.size();i++)
                {
                 ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
                 ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
                 ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
                 ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));}}
                 return;
}

//按地区查找酒店
void bosswindow::hotelQuery2()
{
    hList.clear();
    QString temp=ui->cQuery2->currentText();
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
    for(int i=0;i<hotelList.size();i++)
    if(hotelList[i].showLocation()==temp)
          { hList.append(&hotelList[i]);}
    ui->hTable->setRowCount(hList.size());
     for(int i=0;i<hList.size();i++)
       {
         if(hList.size()!=0){
        ui->hTable->setItem(i,0,new QTableWidgetItem(hList[i]->showHName()));
        ui->hTable->setItem(i,1,new QTableWidgetItem(hList[i]->showLocation()));
        ui->hTable->setItem(i,2,new QTableWidgetItem(hList[i]->showTel()));
        ui->hTable->setItem(i,3,new QTableWidgetItem(hList[i]->showPoint()));}}
                 return;
}
void bosswindow::roomEdit(){//编辑客房信息
    int row=ui->rTable->currentRow();
    if(row>=0)
    {w1=new editroom(this,getRoom(row));
     w1->show(); roomShow();return;}
    else {QMessageBox msg;
        msg.setText(QStringLiteral("未选中任何客房！"));
        msg.exec();
        return; }
}
void bosswindow::roomAdd(){//添加客房信息
    w2=new addroom(this);
    w2->show();
    return;}
void bosswindow::roomDel(){//删除客房信息
    int row=ui->rTable->currentRow();
    if(row<0){QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何客房！"));
            msg.exec();}
    else {int index=0;
        for(int i=0;i<roomList.size();i++)
            if( rList[row]->showRName()==roomList[i].showRName()){
                    index=i;break; }
    QMessageBox msg;
    msg.setText(QStringLiteral("确定删除该客房吗？"));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int temp= msg.exec();
    switch (temp) {
   case QMessageBox::Yes:roomList.removeAt(index);
                         roomShow();
                         {QMessageBox msg2;
                         msg2.setText(QStringLiteral("删除客房成功！"));
                         msg2.exec();}
                         break;
   case QMessageBox::No:break;}
}}
void bosswindow::hotelEdit(){//编辑酒店信息
    int row=ui->hTable->currentRow();
    if(row>=0)
    {w5=new edithotel(this,getHotel(row));//添加函数
     w5->show(); hotelShow();return;}
    else {QMessageBox msg;
        msg.setText(QStringLiteral("未选中任何酒店！"));
        msg.exec();
        return; }
}

void bosswindow::hotelAdd(){//添加酒店信息
    w4=new addhotel(this);
    w4->show();
    return;}
void bosswindow::hotelDel(){//删除酒店信息
    int row=ui->hTable->currentRow();
    if(row<0){QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何酒店！"));
            msg.exec();}
    else {int index=0;
        for(int i=0;i<hotelList.size();i++)
            if( hList[row]->showHName()==hotelList[i].showHName()){
                    index=i;break; }
    QMessageBox msg;
    msg.setText(QStringLiteral("确定删除该酒店吗？"));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int temp= msg.exec();
    switch (temp) {
   case QMessageBox::Yes:hotelList.removeAt(index);
                         roomShow();
                         {QMessageBox msg2;
                         msg2.setText(QStringLiteral("删除酒店成功！"));
                         msg2.exec();}
                         break;
   case QMessageBox::No:break;}
}}

void bosswindow::logout(){//退出登录
        this->close();
        parent->show();
        parent->ui->lAccount->clear();
        parent->ui->lPassword->clear();
        return;}
void bosswindow::exitProgram(){//退出系统
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
    return;}
void bosswindow::save(){
    Database myDataBase;
    myDataBase.memory();
}

void bosswindow::cusShow(){//显示所有顾客信息
    ui->lcusQuery->clear();
    cusList.clear();
    ui->cusTable->clear();
    ui->cusTable->setColumnCount(3);
    ui->cusTable->setRowCount(0);
    ui->cusTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("用户手机号")) );
    ui->cusTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("用户密码")) );
    ui->cusTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("用户消费总金额")));
    ui->cusTable->setColumnWidth(0,400);
    ui->cusTable->setColumnWidth(1,400);
    ui->cusTable->setColumnWidth(2,400);
    for(int i=0;i<customerList.size();i++)
        cusList.append(&customerList[i]);
    for(int i=0;i<cusList.size();i++)
    { ui->cusTable->setRowCount(i+1);
    ui->cusTable->setItem(i,0,new QTableWidgetItem(cusList[i]->setAccount()));
    ui->cusTable->setItem(i,1,new QTableWidgetItem(cusList[i]->setPassword()));
    ui->cusTable->setItem(i,2,new QTableWidgetItem(QString::number(cusList[i]->totalbill)));}
    return;
}
void bosswindow::cusQuery(){//查询某位顾客
    if(ui->lcusQuery->text()==""){
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入用户手机号！"));
        msg.exec();
        return;}
    cusList.clear();
    ui->cusTable->clear();
    ui->cusTable->setColumnCount(3);
    ui->cusTable->setRowCount(0);
    ui->cusTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("用户手机号")) );
    ui->cusTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("用户密码")) );
    ui->cusTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("用户消费总金额")));
    ui->cusTable->setColumnWidth(0,300);
    ui->cusTable->setColumnWidth(1,300);
    ui->cusTable->setColumnWidth(2,300);
    QString temp=ui->lcusQuery->text();
    int count=0;
    for(int i=0;i<customerList.size();i++)
    if(customerList[i].setAccount()==temp)
          { cusList.append(&customerList[i]);
            count++;break;}
    if(count==0){QMessageBox msg;
                msg.setText(QStringLiteral("您所查找的用户不存在！"));
                msg.exec();cusShow();
                return;}
    else for(int i=0;i<cusList.size();i++)
    { ui->cusTable->setRowCount(i+1);
    ui->cusTable->setItem(i,0,new QTableWidgetItem(cusList[i]->setAccount()));
    ui->cusTable->setItem(i,1,new QTableWidgetItem(cusList[i]->setPassword()));
    ui->cusTable->setItem(i,2,new QTableWidgetItem(QString::number(cusList[i]->totalbill)));}
    return;
}
void bosswindow::cusDel(){//删除长期不登录的无效顾客信息
    int row=ui->cusTable->currentRow();
    if(row<0){QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何用户账号！"));
            msg.exec();}
    else if(cusList[row]->getHotel()!=NULL)
    {QMessageBox msg;
        msg.setText(QStringLiteral("该顾客行程未结束，不能删除该账号！"));
        msg.exec();}
    else {int index=0;
        for(int i=0;i<customerList.size();i++)
            if( cusList[row]->account==customerList[i].account){
                    index=i;break; }
    QMessageBox msg;
    msg.setText(QStringLiteral("确定删除该顾客账号么？"));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int temp= msg.exec();
    switch (temp) {
   case QMessageBox::Yes:customerList.removeAt(index);
                         roomShow();
                         {QMessageBox msg2;
                         msg2.setText(QStringLiteral("删除顾客账号成功！"));
                         msg2.exec();}
                         break;
   case QMessageBox::No:break;}
   cusShow();
}}
void bosswindow::manShow(){//显示所有经理信息
    ui->lmanQuery->clear();
    mList.clear();
    ui->manTable->clear();
    ui->manTable->setColumnCount(3);
    ui->manTable->setRowCount(0);
    ui->manTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("经理工作证号")) );
    ui->manTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("经理密码")) );
    ui->manTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("对应酒店")) );
    ui->manTable->setColumnWidth(0,600);
    ui->manTable->setColumnWidth(1,600);
    ui->manTable->setColumnWidth(2,600);
    for(int i=0;i<manList.size();i++)
        mList.append(&manList[i]);
    for(int i=0;i<mList.size();i++)
    { ui->manTable->setRowCount(i+1);
    ui->manTable->setItem(i,0,new QTableWidgetItem(mList[i]->setAccount()));
    ui->manTable->setItem(i,1,new QTableWidgetItem(mList[i]->setPassword()));
    ui->manTable->setItem(i,2,new QTableWidgetItem(mList[i]->myHName));
    }
    return;}
void bosswindow::manAdd(){//添加经理账号
    w3=new addaccount(this);
    w3->show();
    return;}
void bosswindow::manDel(){//删除经理账号
    int row=ui->manTable->currentRow();
    if(row<0){QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何用户账号！"));
            msg.exec();return;}
     int index=0;
     for(int i=0;i<WaitingList.size();i++)
      if(WaitingList[i]->showHotelName()==mList[row]->myHName)
      {
          QMessageBox msg;
        msg.setText(QStringLiteral("该经理正在工作中，不能删除该账号！"));
        msg.exec();return;}

        for(int i=0;i<manList.size();i++)
            if( mList[row]->setAccount()==manList[i].setAccount()){
                    index=i;break; }
    QMessageBox msg;
    msg.setText(QStringLiteral("确定删除该经理账号么？"));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int temp= msg.exec();
    switch (temp) {
   case QMessageBox::Yes:manList.removeAt(index);
                         roomShow();
                         {QMessageBox msg2;
                         msg2.setText(QStringLiteral("删除经理账号成功！"));
                         msg2.exec();}
                         break;
   case QMessageBox::No:break;}
   manShow();
}
void bosswindow::manQuery(){//查询某位经理
    if(ui->lmanQuery->text()==""){
        QMessageBox msg;
        msg.setText(QStringLiteral("请输入经理工作证号！"));
        msg.exec();
        return;}
    mList.clear();
    ui->manTable->clear();
    ui->manTable->setColumnCount(3);
    ui->manTable->setRowCount(0);
    ui->manTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("经理工作证号")) );
    ui->manTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("经理密码")) );
    ui->manTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("对应酒店")) );
    ui->manTable->setColumnWidth(0,600);
    ui->manTable->setColumnWidth(1,600);
    ui->manTable->setColumnWidth(2,600);
    QString temp=ui->lmanQuery->text();
    int count=0;
    for(int i=0;i<manList.size();i++)
    if(manList[i].setAccount()==temp)
          { mList.append(&manList[i]);
            count++;break;}
    if(count==0){QMessageBox msg;
                msg.setText(QStringLiteral("您所查找的经理不存在！"));
                msg.exec();manShow();
                return;}
    else
       {ui->manTable->setRowCount(mList.size());
        for(int i=0;i<mList.size();i++)
    {
        ui->manTable->setItem(i,0,new QTableWidgetItem(mList[i]->setAccount()));
        ui->manTable->setItem(i,1,new QTableWidgetItem(mList[i]->setPassword()));
        ui->manTable->setItem(i,2,new QTableWidgetItem(mList[i]->myHName));
    }}
    return; }


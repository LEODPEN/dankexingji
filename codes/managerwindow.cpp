#include "managerwindow.h"
#include "ui_managerwindow.h"
#include"room.h"
#include"qmessagebox.h"
 extern QList<Room*>WaitingList;
extern QVector<Customer>customerList;
extern Database myDataBase;
managerwindow::managerwindow(loginwindow *parent,Manager*pMan):parent(parent),pMan(pMan),
     ui(new Ui::managerwindow)
{
    ui->setupUi(this);
    showmyTodo();
    showmyDone();
    showmyEnded();
    connect(ui->bRefresh,SIGNAL(clicked()),this,SLOT(showmyTodo()));
    connect(ui->bcheckIn,SIGNAL(clicked()),this,SLOT(triggerchekIn()));
    connect(ui->bRefresh1,SIGNAL(clicked()),this,SLOT(showmyDone()));
    connect(ui->bRefresh2,SIGNAL(clicked()),this,SLOT(showmyEnded()));
    connect(ui->bLogout,SIGNAL(clicked()),this,SLOT(logout()));
    connect(ui->bExit,SIGNAL(clicked()),this,SLOT(exitProgram()));
}
managerwindow::~managerwindow()
{
    delete ui;
}


Room* managerwindow::getRoom(int row){
    return mTodo[row];
}

void managerwindow::showmyTodo(){
    mTodo.clear();
    ui->myTodo->clear();
    ui->myTodo->setColumnCount(3);
    ui->myTodo->setRowCount(0);
    ui->myTodo->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("顾客账号")));
    ui->myTodo->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("房间名称")));
    ui->myTodo->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("房间价格")));
    ui->myTodo->setColumnWidth(0,320);
    ui->myTodo->setColumnWidth(1,320);
    ui->myTodo->setColumnWidth(2,320);
    for(int i=0;i<WaitingList.size();i++)
        if(WaitingList[i]->showHotelName()==pMan->myHName)
     mTodo.push_back(WaitingList[i]);
    ui->myTodo->setRowCount(mTodo.size());
    for(int i=0;i<mTodo.size();i++)
     {
        if(mTodo.size()!=0){
     ui->myTodo->setItem(i,0,new QTableWidgetItem(mTodo[i]->showcusAccount()));
     ui->myTodo->setItem(i,1,new QTableWidgetItem(mTodo[i]->showRName()));
     ui->myTodo->setItem(i,2,new QTableWidgetItem(mTodo[i]->showPrice()));}}
    return;
}
void managerwindow::triggerchekIn()
{
    int row=ui->myTodo->currentRow();
    if(row<0) {QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何房间！"));
            msg.exec();}
    else{
        pMan->checkin(mTodo[row]);
        for(int i=0;i<WaitingList.size();i++)
        {if(WaitingList[i]->showHotelName()==mTodo[row]->showHotelName()
                    &&WaitingList[i]->showcusAccount()==mTodo[row]->showcusAccount())
            {WaitingList[i]->StateToOccupied();WaitingList.removeAt(i);}}
        mDone.push_back(mTodo[row]);
        mTodo.removeAt(row);
        QMessageBox msg;
        msg.setText(QStringLiteral("已办理入住！"));
        msg.exec();
    }
}
void managerwindow::showmyDone()
{
    ui->myDone->clear();
    ui->myDone->setColumnCount(3);
    ui->myDone->setRowCount(0);
    ui->myDone->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("顾客账号")));
    ui->myDone->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("房间名称")));
    ui->myDone->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("房间价格")));
    ui->myDone->setColumnWidth(0,320);
    ui->myDone->setColumnWidth(1,320);
    ui->myDone->setColumnWidth(2,320);
    for(int i=0;i<mDone.size();i++)
        if(mDone[i]->getState()==none)
        {
            mEnded.push_back(mDone[i]);
            mDone.removeAt(i);
        }
    for(int i=0;i<mDone.size();i++)
    {
     ui->myDone->setRowCount(i+1);
     ui->myDone->setItem(i,0,new QTableWidgetItem(mDone[i]->showcusAccount()));
     ui->myDone->setItem(i,1,new QTableWidgetItem(mDone[i]->showRName()));
     ui->myDone->setItem(i,2,new QTableWidgetItem(mDone[i]->showPrice()));  }
    return;
}
void managerwindow::showmyEnded()
{
    ui->myEnded->clear();
    ui->myEnded->setColumnCount(3);
    ui->myEnded->setRowCount(0);
    ui->myEnded->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("顾客账号")));
    ui->myEnded->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("房间名称")));
    ui->myEnded->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("房间价格")));
    ui->myEnded->setColumnWidth(0,320);
    ui->myEnded->setColumnWidth(1,320);
    ui->myEnded->setColumnWidth(2,320);
    ui->myEnded->setRowCount(mEnded.size());
    for(int i=0;i<mEnded.size();i++)
    {
     ui->myEnded->setItem(i,0,new QTableWidgetItem(mEnded[i]->showcusAccount()));
     ui->myEnded->setItem(i,1,new QTableWidgetItem(mEnded[i]->showRName()));
     ui->myEnded->setItem(i,2,new QTableWidgetItem(mEnded[i]->showPrice()));  }
    return;
}

void managerwindow::logout()
{
   this->close();
   parent->show();
   parent->ui->lPassword->clear();
   return;
}

void managerwindow::exitProgram()
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
}
void managerwindow::save(){
    Database myDataBase;
    myDataBase.memory();
}

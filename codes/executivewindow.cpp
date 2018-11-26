#include "executivewindow.h"
#include "ui_executivewindow.h"
#include"hotel.h"
#include"qmessagebox.h"
#include"customerwindow.h"
#include"addhotel.h"
extern QVector<Hotel>hotelList;
extern QVector<Hotel>decideList;
executivewindow::executivewindow(loginwindow *parent,Executive*pExe) :parent(parent),pExe(pExe),
     ui(new Ui::executivewindow)
{
    ui->setupUi(this);
    showDecide();
    showDone();
    connect(ui->bRefresh,SIGNAL(clicked()),this,SLOT(showDecide()));
    connect(ui->bOK,SIGNAL(clicked()),this,SLOT(triggerOk()));
    connect(ui->bNo,SIGNAL(clicked()),this,SLOT(triggerNo()));
    connect(ui->bRefresh1,SIGNAL(clicked()),this,SLOT(showDone()));
    connect(ui->bLogout,SIGNAL(clicked()),this,SLOT(logout()));
    connect(ui->bExit,SIGNAL(clicked()),this,SLOT(exitProgram()));
}
executivewindow::~executivewindow()
{
    delete ui;
}


void executivewindow::showDecide()
{
    Decide.clear();
    ui->decideTable->clear();
    ui->decideTable->setColumnCount(3);
    ui->decideTable->setRowCount(0);
    ui->decideTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->decideTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("酒店位置")) );
    ui->decideTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("联系电话")) );
    ui->decideTable->setColumnWidth(0,320);
    ui->decideTable->setColumnWidth(1,320);
    ui->decideTable->setColumnWidth(2,320);
    for(int i=0;i<decideList.size();i++)
     Decide.push_back(&decideList[i]);
    for(int i=0;i<Decide.size();i++)
     {ui->decideTable->setRowCount(i+1);
     ui->decideTable->setItem(i,0,new QTableWidgetItem(Decide[i]->showHName()));
     ui->decideTable->setItem(i,1,new QTableWidgetItem(Decide[i]->showLocation()));
     ui->decideTable->setItem(i,2,new QTableWidgetItem(Decide[i]->showTel()));}
    return;
}
Hotel* executivewindow::gethotel(int row)
{return Decide[row];}

void executivewindow::triggerOk()
{
    int row=ui->decideTable->currentRow();
    if(row<0) {QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何酒店！"));
            msg.exec();}
    else{
        Done.push_back(Decide[row]);
        hotelList.append(*Decide[row]);
        decideList.removeAt(row);
        QMessageBox msg;
        msg.setText(QStringLiteral("已同意创建该酒店！"));
        msg.exec();
    }

}
void executivewindow::showDone()
{
    //Done.clear();
    ui->doneTable->clear();
    ui->doneTable->setColumnCount(3);
    ui->doneTable->setRowCount(0);
    ui->doneTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("酒店名称")) );
    ui->doneTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("酒店位置")) );
    ui->doneTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("联系电话")) );
    ui->doneTable->setColumnWidth(0,320);
    ui->doneTable->setColumnWidth(1,320);
    ui->doneTable->setColumnWidth(2,320);
    for(int i=0;i<Done.size();i++)
    {
     ui->doneTable->setRowCount(i+1);
     ui->doneTable->setItem(i,0,new QTableWidgetItem(Done[i]->showHName()));
     ui->doneTable->setItem(i,1,new QTableWidgetItem(Done[i]->showLocation()));
     ui->doneTable->setItem(i,2,new QTableWidgetItem(Done[i]->showTel()));  }
    return;
}
void executivewindow::triggerNo()
{
    int row=ui->decideTable->currentRow();
    if(row<0) {QMessageBox msg;
            msg.setText(QStringLiteral("未选中任何酒店！"));
            msg.exec();}
    else{
        Done.push_back(Decide[row]);
        Decide.removeAt(row);
        decideList.removeAt(row);
        QMessageBox msg;
        msg.setText(QStringLiteral("已拒绝创建该酒店！"));
        msg.exec();
    }

}
void executivewindow::logout(){
   this->close();
   parent->show();
   parent->ui->lPassword->clear();
   parent->ui->lAccount->clear();
   return;}
void executivewindow::exitProgram()
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
void executivewindow::save(){
    Database myDataBase;
    myDataBase.memory();
}

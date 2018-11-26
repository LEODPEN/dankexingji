#include "hcomment.h"
#include "ui_hcomment.h"
#include"customerwindow.h"


hcomment::hcomment(customerwindow*w1,Hotel*pHotel,Room *pRoom) :
    w1(w1),pHotel(pHotel),pRoom(pRoom),
    ui(new Ui::hcomment)
{
    ui->setupUi(this);
    connect(ui->b5,SIGNAL(clicked()),this,SLOT(give5()));//评价5分
    connect(ui->b4,SIGNAL(clicked()),this,SLOT(give4()));//评价4分
    connect(ui->b3,SIGNAL(clicked()),this,SLOT(give3()));//评价3分
    connect(ui->b2,SIGNAL(clicked()),this,SLOT(give2()));//评价2分
    connect(ui->b1,SIGNAL(clicked()),this,SLOT(give1()));//评价1分
}

void hcomment::give5()
{
    pHotel->getPoint();
    pHotel->setPoint(5.0);
    QMessageBox msg;
    msg.setText(QStringLiteral("评价成功！"));
    msg.setWindowTitle(QStringLiteral("Success"));
    msg.exec();
    this->close();
}
void hcomment::give4(){
    pHotel->getPoint();
    pHotel->setPoint(4.0);
    QMessageBox msg;
    msg.setText(QStringLiteral("评价成功！"));
    msg.setWindowTitle(QStringLiteral("Success"));
    msg.exec();
    this->close();
}

void hcomment::give3()
{
    pHotel->getPoint();
    pHotel->setPoint(3.0);
    QMessageBox msg;
    msg.setText(QStringLiteral("评价成功！"));
    msg.setWindowTitle(QStringLiteral("Success"));
    msg.exec();
    this->close();
}
void hcomment::give2()
{
    pHotel->getPoint();
    pHotel->setPoint(2.0);
    QMessageBox msg;
    msg.setText(QStringLiteral("评价成功！"));
    msg.setWindowTitle(QStringLiteral("Success"));
    msg.exec();
    this->close();
}

void hcomment::give1(){
    pHotel->getPoint();
    pHotel->setPoint(1.0);
    QMessageBox msg;
    msg.setText(QStringLiteral("评价成功！"));
    msg.setWindowTitle(QStringLiteral("Success"));
    msg.exec();
    this->close();
    }
hcomment::~hcomment()
{
    delete ui;
}

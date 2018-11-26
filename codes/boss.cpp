#include "boss.h"
#include"qmessagebox.h"

Boss::Boss(QString account, QString password):
    User(account,password),parent(parent)
{}
void Boss::setParent(bosswindow* parent)
{
    this->parent=parent;
}

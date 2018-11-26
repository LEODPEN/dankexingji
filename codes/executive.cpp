#include "executive.h"

Executive::Executive(QString account, QString password):
    User(account,password),parent(parent)
{}
void Executive::setParent(executivewindow* parent)
{
    this->parent=parent;
}

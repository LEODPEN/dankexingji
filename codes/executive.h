#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include"user.h"
#include"executivewindow.h"
#include <QString>
class executivewindow;

class Executive:public User

{public:
    Executive(){account="dsh";password="123";}
    Executive(QString account,QString password);
    void setParent(executivewindow *parent);
private:
    executivewindow *parent;
};
#endif // EXECUTIVE_H

#ifndef BOSS_H
#define BOSS_H

#include"user.h"
#include"database.h"
#include"bosswindow.h"
#include<QString>
class bosswindow;

class Boss: public User
{
    friend class Database;
private:
    bosswindow *parent;
public:
    Boss(){account = "pfpfpf";password="pfpfpf";}
    Boss(QString account, QString password);
    void setParent(bosswindow* parent);
};

#endif // BOSS_H

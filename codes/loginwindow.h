#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include"ui_loginwindow.h"
#include"registerwindow.h"

namespace Ui {class loginwindow;}
class managerwindow;
class registerwindow;
class customerwindow;
class bosswindow;
class executivewindow;
class loginwindow:public QMainWindow
{
    Q_OBJECT
friend class customerwindow;
friend class bosswindow;
friend class managerwindow;
friend class datawindow;
friend class executivewindow;
public:
   explicit loginwindow(QWidget *parent = 0);
   ~loginwindow();
   Ui::loginwindow *ui;
public slots:
   void login();
private:
   registerwindow*r;
   customerwindow*w1;
   bosswindow*w2;
   managerwindow*w3;
   executivewindow*w4;
};

#endif // LOGINWINDOW_H

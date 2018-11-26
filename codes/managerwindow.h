#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include"loginwindow.h"
#include"ui_managerwindow.h"
#include"manager.h"
#include"room.h"
#include"enum.h"
namespace Ui {
class managerwindow;
}
class Room;
extern QList<Room*>rList;
class managerwindow : public QMainWindow
{
    Q_OBJECT

public:
    managerwindow(){}
     managerwindow(loginwindow*parent,Manager*pMan);
    ~managerwindow();
    //将所指的客房行数转化为指针
    Room* getRoom(int row);
private:
    loginwindow*parent;
    Manager* pMan;
    Ui::managerwindow *ui;
    //所在酒店所有的待处理订单
    QVector<Room*>mTodo;
    //所在酒店所有的已处理订单
    QVector<Room*>mDone;
    //所在酒店所有的已完成订单
    QVector<Room*>mEnded;
private slots:
    //在整个TodoList中只选取酒店名与经理酒店名相同的房间显示在“待处理订单”栏
    void showmyTodo();
    //将待处理的房间状态改为入住，同时将其加入myDone并同时从TodoList和myTodo中移除
    void triggerchekIn();
    //显示myDone中的房间，判断如果其中有房间状态再次变为“未预订”时该房间进入myEnded并从myDone中移除
    void showmyDone();
    //显示myEnded中的房间
    void showmyEnded();
    void logout();
    void exitProgram();
    void save();
};

#endif // MANAGERWINDOW_H

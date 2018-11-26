#ifndef EXECUTIVEWINDOW_H
#define EXECUTIVEWINDOW_H

#include <QMainWindow>
#include"loginwindow.h"
#include"ui_executivewindow.h"
#include"executive.h"
#include"hotel.h"

namespace Ui {
class executivewindow;
}
class Executive;
class executivewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit executivewindow(loginwindow*parent,Executive*pExe);
    ~executivewindow();
    Hotel* gethotel(int row);//将所指的行数变为该行酒店的指针
private:
    loginwindow*parent;
    Executive* pExe;
    Ui::executivewindow *ui;
    QVector<Hotel*>Decide;//所有需要决定的酒店列表
    QVector<Hotel*>Done;//所有已经决定了的酒店列表
private slots:
    void showDecide();//显示所有待决定的酒店列表
    void triggerOk();//同意某酒店建立并将其加入已决定列表
    void triggerNo();//不同意某酒店建立并将其加入已决定列表
    void showDone();//显示已决定的酒店列表
    void logout();
    void exitProgram();
    void save();
};

#endif // EXECUTIVEWINDOW_H

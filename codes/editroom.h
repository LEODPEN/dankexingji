#ifndef EDITROOM_H
#define EDITROOM_H
#include <QWidget>
#include"bosswindow.h"
#include"room.h"
#include"enum.h"
namespace Ui {
class editroom;
}
class Room;
class editroom:public QMainWindow
{
     Q_OBJECT
public:
    editroom();
    explicit editroom(bosswindow *parent,Room*pRoom);
    ~editroom();
    Ui::editroom *ui;
private:
    bosswindow*parent;
    Room*pRoom;
    QString newRName;
    int newPrice;
    enumKind newKind;
    int newSum;
    QString newkind;
    QString newDes;
private slots:
    void sendInfo();
    void edit();
};

#endif // EDITROOM_H

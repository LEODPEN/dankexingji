#ifndef ADDROOM_H
#define ADDROOM_H

#include <QWidget>
#include"bosswindow.h"
#include"room.h"
#include"enum.h"
namespace Ui {
class addroom;
}

class addroom : public QMainWindow
{
    Q_OBJECT

public:
    explicit addroom(bosswindow *parent);
    ~addroom();

private:
    Ui::addroom *ui;
    bosswindow *parent;
    QString newRName;
    int newPrice;
    QString newKind;
    int newSum;
    QString newkind;
    QString newDes;
private slots:
    void sendInfo();
};
#endif // ADDROOM_H

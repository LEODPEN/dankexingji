#ifndef ADDHOTEL_H
#define ADDHOTEL_H
#include <QWidget>
#include"bosswindow.h"
#include"hotel.h"
#include"enum.h"
namespace Ui {
class addhotel;
}
class Hotel;
class addhotel:public QMainWindow
{
     Q_OBJECT
public:
    explicit addhotel(bosswindow *parent);
    ~addhotel();

private:
     Ui::addhotel *ui;
    bosswindow*parent;
    QString newHName;
    enumLoc newLoc;
    QString newTel;
    QString newloc;
private slots:
    void sendInfo();

};

#endif // ADDHOTEL_H

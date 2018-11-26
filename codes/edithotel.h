#ifndef EDITHOTEL_H
#define EDITHOTEL_H
#include <QWidget>
#include"bosswindow.h"
#include"hotel.h"
#include"enum.h"
namespace Ui {
class edithotel;
}
class Hotel;
class edithotel:public QMainWindow
{
     Q_OBJECT
public:
    edithotel();
    explicit edithotel(bosswindow *parent,Hotel*pHotel);
    ~edithotel();
    Ui::edithotel *ui;
private:
    bosswindow*parent;
    Hotel*pHotel;
    QString newHName;
    enumLoc newLoc;
    QString newTel;
    QString newloc;
private slots:
    void HsendInfo();
    void Hedit();
};

#endif // EDITHOTEL_H

#ifndef HCOMMENT_H
#define HCOMMENT_H


#include <QWidget>
#include"ui_customerwindow.h"
#include"hotel.h"
#include"room.h"
namespace Ui {
class hcomment;
}

class hcomment : public QMainWindow
{
    Q_OBJECT

public:
    explicit hcomment(customerwindow*w1,Hotel*pHotel,Room *pRoom);
    ~hcomment();

private:
    Ui::hcomment *ui;
    customerwindow*w1;
    Hotel* pHotel;
    Room *pRoom;
private slots:
    void give5();
    void give4();
    void give3();
    void give2();
    void give1();
};

#endif // HCOMMENT_H

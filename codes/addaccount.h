#ifndef ADDACCOUNT_H
#define ADDACCOUNT_H

#include <QWidget>
#include"bosswindow.h"
namespace Ui {
class addaccount;
}

class addaccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit addaccount(bosswindow *parent);
    ~addaccount();

private:
    Ui::addaccount *ui;
    bosswindow *parent;
    QString temp1;
    QString temp2;
private slots:void sendInfo();
};

#endif // ADDACCOUNT_H

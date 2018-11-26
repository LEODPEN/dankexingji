#include "manager.h"
extern QVector<Hotel>hotelList;
extern QVector<Customer>customerList;
//extern QList<Room*>WaitingList;
Manager::Manager( QString account, QString password,QString myHName):
    User(account,password),myHName(myHName){}

void Manager::checkin(Room* pRoom)
{
     pRoom->StateToOccupied();
}

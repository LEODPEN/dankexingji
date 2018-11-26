#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include<Qtsql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlError>
#include<QtSql/QSqlRecord>
#include<QtSql/QSqlTableModel>
#include<QtDebug>
#include<QtSql/QSqlField>
#include<QMessageBox>

class Database:public QObject
{
    Q_OBJECT
public:
    Database();
    ~Database();
    QSqlDatabase db;
public:
    bool initialCustomer();
    bool initialManager();
    bool initialBoss();
    bool initialExecutive();
    bool initialRoom();
    bool initialHotel();
private:bool createConnection();
    bool createTables();

public slots:bool memory();
};


#endif // DATABASE_H

#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication> //SQL
#include <QtSql> //SQL
#include <QSqlDatabase> //SQL
#include <QString>
#include <QDebug>
#include <assert.h>

class DatabaseManager {
public:
    DatabaseManager() {};

    void connect() {
    _db.setHostName("localhost");
    _db.setDatabaseName("RobotDB");
    _db.setUserName("root");
    _db.setPassword("password");


    _db.open();

    if (!_db.open()) { //Check for failure.
        qDebug() << "Error: \033[1;31m" << _db.lastError().text() << "\033[0m";
        assert(false);
    }
}
    void disconnect();

private:
    QSqlDatabase _db;
};

#endif
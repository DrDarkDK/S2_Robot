#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication> //SQL
#include <QtSql> //SQL
#include <QSqlDatabase> //SQL
#include <QString>
#include <QDebug>

class DatabaseManager {
public:
    DatabaseManager() {};

    void connect();
    void disconnect();

private:
    QSqlDatabase _db;
};

#endif
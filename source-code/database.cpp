#include <assert.h> //assert()

#include "database.h"


DatabaseManager::DatabaseManager() {
    _db = QSqlDatabase::addDatabase("QMYSQL");

    _db.setHostName("localhost");
    _db.setDatabaseName("RobotDB");
    _db.setUserName("root");
    _db.setPassword("password");
};


/*
void DatabaseManager::connect() {
    _db.open();

    if (!_db.open()) { //Check for failure.
        qDebug() << "Error: \033[1;31m" << _db.lastError().text() << "\033[0m";
        assert(false);
    }
}

void DatabaseManager::disconnect() {
    _db.close();
}
*/
#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication> //SQL
#include <QtSql> //SQL
#include <QSqlDatabase> //SQL
#include <QString>
#include <QDebug>
#include <assert.h>
#include <chrono>
#include <thread>

class DatabaseManager {
public:
    DatabaseManager() {};

    void connect() {
        _db = QSqlDatabase::addDatabase("QMYSQL");
        _db.setHostName("localhost");
        _db.setDatabaseName("RobotDB");
        _db.setUserName("root");
        _db.setPassword("#Superdeadcasp2004");

        _db.open();

        if (!_db.open()) { //Check for failure.
            qDebug() << "Error: \033[1;31m" << _db.lastError().text() << "\033[0m";
            assert(false);
        }
    }

    void disconnect() {
        _db.close();
    };

    void savePosition(std::vector<double> arg_coordinates) {
        assert(arg_coordinates.size() == 2);
        double coordX = arg_coordinates[0];
        double coordY = arg_coordinates[1];

        QSqlQuery query;
        query.prepare("INSERT INTO movement (posX, posY, posZ) VALUES (:posX, :posY, :posZ)");
        query.bindValue(":posX", coordX);
        query.bindValue(":posY", coordY);
        query.bindValue(":posZ", 0);


        if (!query.exec()) {
            qDebug() << "Error inserting into the table:" << query.lastError().text();
        } else {
            qDebug() << "Insert successful!";
        }
    };

    /*const void saveVoltage(const double& arg_voltage) {
        assert(arg_voltage >= 0); //Negative voltage
        std::string time;

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_time);

        time = std::put_time(now_tm, "%d/%m - %H:%M");

        QSqlQuery query;
        query.prepare("INSERT INTO voltage_data (timestamp, voltage) VALUES (:time, :voltage)");
        query.bindValue(":time", time);
        query.bindValue(":voltage", arg_voltage);


        if (!query.exec()) {
            qDebug() << "Error inserting into the table:" << query.lastError().text();
        } else {
            qDebug() << "Insert successful!";
        }
    }*/

private:
    QSqlDatabase _db;
};

#endif
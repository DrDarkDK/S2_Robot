#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QProcessEnvironment>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // her indsættes navnet på det angivne password
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString dbPassword = env.value("DB_PASSWORD", "");  // selve password

    // forbindelse til database 
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("skakrobotdatabase");
    db.setUserName("root");
    db.setPassword(dbPassword);  // her anvendes passwordet

    // forsøger at åbne database
    if (!db.open()) {
        qDebug() << "Error:" << db.lastError().text();
        qDebug() << "Failed to open database. Did you remember to set the database password?";
        qDebug() << "In the terminal, write:";
        qDebug() << "export DB_PASSWORD='your_database_password_here'";
        return -1;  // fejl ved forkert password
    }
    qDebug() << "Connected successfully, exiting...";
    return 0;  // Lukker program når det er færdigt

}

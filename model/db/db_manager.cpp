#include <model/db/db_manager.h>

const QString DbManager::DRIVER = "QSQLITE";
const QString DbManager::dbPath = "./storage";

bool DbManager::isDbConnected(){
    return database.isOpen();
}

bool DbManager::connectDb(){
    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(":memory:");
        if(db.open()){
            return true;
        }else{
            qCritical() << "DbManager::connectDb - ERROR: " << db.lastError().text();
            return false;
        }
    }
    else{
        qCritical() << "DbManager::connectDb - ERROR: no driver " << DRIVER << " available";
        return false;
    }

}

bool DbManager::initDb(){
    return database.isOpen();
}

QSqlQuery* DbManager::getQuery(){
    return new QSqlQuery();
}

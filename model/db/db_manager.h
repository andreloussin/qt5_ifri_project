#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class DbManager{
private:
    static QSqlDatabase database;
    static bool isDbConnected ();
    static bool connectDb ();
    static bool initDb ();
public:
    static const QString dbPath;
    static const QString DRIVER;
    static QSqlQuery* getQuery ();
//    static void

    
};


#endif

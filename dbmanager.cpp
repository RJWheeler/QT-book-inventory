#include "dbmanager.h"
#include <vector>
#include <string>
#include <QVector>
#include <iostream>

using namespace std;
dbManager::dbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
    }
    m_db.close();
}
// checks the connection to the database and creates a table
string dbManager::createDB(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    QSqlQuery CreateQuery;
    bool success = false;
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
    }
    CreateQuery.prepare("CREATE TABLE BOOK( ISBN INTEGER PRIMARY KEY UNIQUE, TITLE STRING, PUBLISHED INTEGER)");
    if(CreateQuery.exec()){
        success = true;
    }
    else{
        qDebug() << "Create table error:" << CreateQuery.lastError();
    }
    QSqlQuery InsertQuery;
    InsertQuery.prepare("INSERT INTO BOOK (ISBN, TITLE, PUBLISHED) VALUES (:ISBN, 'Good Morning', 2023)");
    InsertQuery.bindValue(":ISBN", 22222222);
    if(InsertQuery.exec()){
        success = true;
    }
    else{
        qDebug() << "Insert to table error:" << InsertQuery.lastError();
    }
    m_db.close();
    if(success == true){
        return "Created table";
    }
    else{
        return "Failed";
    }
}

// checks database connection and queries the database
vector<string> dbManager::queryDB()
{
    vector<string> results;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("books.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
    }
    QSqlQuery query("SELECT * FROM BOOK");
    int idName = query.record().indexOf("ISBN");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        string result = name.toStdString();
        results.push_back(result);
    }
       m_db.close();
       return results;
}


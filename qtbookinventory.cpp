#include "qtbookinventory.h"
#include "log.h"
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <QSqlRecord>
using namespace std;
QTBookinventory::QTBookinventory()
{

}

QVector<QVariant>QTBookinventory::bookSearchByTitle(QString title)
{
    Log log;
    QVector<QVariant> results;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM BookInventory WHERE TITLE = ? ");
    query.addBindValue(title);
    query.exec();
    int idISBN = query.record().indexOf("ISBN");
    int idTitle = query.record().indexOf("TITLE");
    int idAuthor = query.record().indexOf("AUTHOR");
    int idYear = query.record().indexOf("YEAR");
    int idPrice = query.record().indexOf("PRICE");
    int idQty = query.record().indexOf("QUANTITY");
    while (query.next())
        {
           results.push_back(query.value(idTitle).toString());
           results.push_back(query.value(idAuthor).toString());
           results.push_back(query.value(idPrice).toString());
           results.push_back(query.value(idQty).toString());
           results.push_back(query.value(4).toString());
           results.push_back(query.value(3).toString());
           results.push_back(query.value(idYear).toString());
           results.push_back(query.value(idISBN).toString());

        }

       m_db.close();
       return results;
}
QVector<QVariant>QTBookinventory::addToShoppingCart(QString title){
    Log log;
    QVector<QVariant> results;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM BookInventory WHERE TITLE = ? ");
    query.addBindValue(title);
    query.exec();
    int idTitle = query.record().indexOf("TITLE");
    int idPrice = query.record().indexOf("PRICE");
    while (query.next())
        {
           results.push_back(query.value(idTitle).toString());
           results.push_back(query.value(idPrice).toString());
        }

       m_db.close();
       return results;

}

QString QTBookinventory::recordsAmount(){
    Log log;
    QString result;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    QSqlQuery query("SELECT Count(*) FROM BookInventory");
    int idName = query.record().indexOf("COUNT(*)");
    while(query.next()){
        result =query.value(idName).toString();
    }
    m_db.close();
    return result;
}
void QTBookinventory::newBook(QVector<QVariant> book)
{
    Log log;
    QString isbn = book[0].toString();
    QString author = book[1].toString();
    QString year = book[2].toString();
    QString publisher = book[3].toString();
    QString genre = book[4].toString();
    QString price = book[5].toString();
    QString quantity = book[6].toString();
    QString title = book[7].toString();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    //queries the database
    QSqlQuery query;
    query.prepare("INSERT INTO  BookInventory VALUES (?,?,?,?,?,?,?,?)");
    query.addBindValue(isbn);
    query.addBindValue(author);
    query.addBindValue(year);
    query.addBindValue(publisher);
    query.addBindValue(genre);
    query.addBindValue(price);
    query.addBindValue(quantity);
    query.addBindValue(title);
    query.exec();
    while (query.next())
    {
    }
    m_db.close();
}
void QTBookinventory::updateBook(QVector<QVariant> book)
{
    Log log;
    QString isbn = book[0].toString();
    QString author = book[1].toString();
    QString year = book[2].toString();
    QString publisher = book[3].toString();
    QString genre = book[4].toString();
    QString price = book[5].toString();
    QString quantity = book[6].toString();
    QString title = book[7].toString();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    //queries the database
    QSqlQuery query;
    query.prepare("UPDATE BookInventory SET ISBN = ?, AUTHOR = ?, YEAR = ?, PUBLISHER = ?, GENRE = ?, PRICE = ?, QUANTITY = ? WHERE TITLE = ?");
    query.addBindValue(isbn);
    query.addBindValue(author);
    query.addBindValue(year);
    query.addBindValue(publisher);
    query.addBindValue(genre);
    query.addBindValue(price);
    query.addBindValue(quantity);
    query.addBindValue(title);
    query.exec();
    while (query.next())
    {
    }
    m_db.close();

}
void QTBookinventory::updateQty(QString title, int qty)
{
    Log log;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("BookInventory.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    QSqlQuery query;
    query.prepare("UPDATE BookInventory SET QUANTITY = ? WHERE TITLE = ?");
    query.addBindValue(qty);
    query.addBindValue(title);
    query.exec();
    while (query.next())
    {
    }

    m_db.close();
}

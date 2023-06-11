#ifndef QTBOOKINVENTORY_H
#define QTBOOKINVENTORY_H

#include <string>
#include <vector>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QVector>
using namespace std;
class QTBookinventory
{
public:
    QTBookinventory();
    QVector<QVariant> bookSearchByTitle(QString title);
    QString recordsAmount();
    QVector<QVariant> addToShoppingCart(QString title);
    void newBook(QVector<QVariant> book);
    void updateQty(QString title, int qty);
    void updateBook(QVector<QVariant> book);

private:
    QSqlDatabase m_db;
};

#endif // QTBOOKINVENTORY_H

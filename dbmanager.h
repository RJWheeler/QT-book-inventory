#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <vector>
#include <string>
#include <QtSql/QtSql>
#include <QVector>
using namespace std;

class dbManager
{
public:
    dbManager(const QString& path);
    string createDB(const QString& path);
    vector<string> queryDB();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

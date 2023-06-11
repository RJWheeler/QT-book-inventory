#include "loginwindow2.h"
#include "admin.h"
#include "ui_loginwindow2.h"
#include "qsqlquery.h"
#include "log.h"
#include <QDesktopServices>
#include <QUrl>

#include <QSqlRecord>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <QMessageBox>
#include <QDialog>
#include <QCryptographicHash>

loginwindow2::loginwindow2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginwindow2)
{
    ui->setupUi(this);
}

loginwindow2::~loginwindow2()
{
    delete ui;
}

// Calls the login screen and begins the login process
void loginwindow2::onPushButtonClicked()
{        
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QByteArray ur = username.toUtf8();
    QByteArray hashedUser = QCryptographicHash::hash((ur),QCryptographicHash::Md5);

    QByteArray br = password.toUtf8();
    QByteArray hashedPass = QCryptographicHash::hash((br),QCryptographicHash::Md5);

    QString userResults;
    QString passResults;
    QString fNameResults;
    QString lNameResults;
    QString emailResults;
    double totalResults;
    int adminResults;
    Log log;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Login.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    //queries the database
    QSqlQuery query;
    query.prepare("SELECT * FROM Login WHERE USERNAME = ? ");
    query.addBindValue(username);
    query.exec();
    int idUser = query.record().indexOf("USERNAME");
    int idPass = query.record().indexOf("PASSWORD");
    int idFName = query.record().indexOf("FirstName");
    int idLName = query.record().indexOf("LastName");
    int idTotal = query.record().indexOf("TotalSpent");
    int idAdmin = query.record().indexOf("isAdmin");
    int idEmail = query.record().indexOf("Email");
    while (query.next())
        {
           userResults = query.value(idUser).toString();
           passResults = query.value(idPass).toString();
           fNameResults = query.value(idFName).toString();
           lNameResults = query.value(idLName).toString();
           totalResults = query.value(idTotal).toDouble();
           adminResults = query.value(idAdmin).toInt();
           emailResults = query.value(idEmail).toString();
        }
    QByteArray ur2 = userResults.toUtf8();
    QByteArray hashedUserResults = QCryptographicHash::hash((ur2),QCryptographicHash::Md5);
    QByteArray br2 = passResults.toUtf8();
    QByteArray hashedPassResults = QCryptographicHash::hash((br2),QCryptographicHash::Md5);
    // Returns a successful or failed login attempt
    if (hashedUser == hashedUserResults && hashedPass == hashedPassResults){
           if(adminResults == 1){
               Admin admin;
               admin.exec();
           }
        name.push_back(fNameResults);
        name.push_back(lNameResults);
        name.push_back(userResults);
        name.push_back(totalResults);
        name.push_back(passResults);
        name.push_back(emailResults);
        this->hide();
    }
    else{
        QMessageBox::information(this, "Login", "Username and Password are incorrect");
    }

    m_db.close();
}
QVector<QVariant> loginwindow2::nameReturn(){
    return name;
}
double loginwindow2::addTotal(double total,QString username,double totalResults)
{
    Log log;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Login.db");
    if(!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
        log.dbOperationSuccess();
    }
    //queries the database
        double newTotal = total + totalResults;
        QSqlQuery query2;
        query2.prepare("UPDATE Login SET TotalSpent = ? WHERE USERNAME = ?");
        query2.addBindValue(newTotal);
        query2.addBindValue(username);
        query2.exec();
        while(query2.next()){
            qDebug() << totalResults;
            qDebug() << newTotal;
        }

        return newTotal;
}
void loginwindow2::guestCheckout()
{
        QString username = "Guest";
        QString password = "Guest";
        QString userResults;
        QString passResults;
        QString fNameResults;
        QString lNameResults;
        double totalResults;
        Log log;
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("Login.db");
        if(!m_db.open()){
            qDebug() << "Error: connection with database failed";
        }
        else{
            qDebug() << "Database: connection ok";
            log.dbOperationSuccess();
        }
        //queries the database
        QSqlQuery query;
        query.prepare("SELECT * FROM Login WHERE USERNAME = ? ");
        query.addBindValue(username);
        query.exec();
        int idUser = query.record().indexOf("USERNAME");
        int idPass = query.record().indexOf("PASSWORD");
        int idFName = query.record().indexOf("FirstName");
        int idLName = query.record().indexOf("LastName");
        while (query.next())
        {
            userResults = query.value(idUser).toString();
            passResults = query.value(idPass).toString();
            fNameResults = query.value(idFName).toString();
            lNameResults = query.value(idLName).toString();
            totalResults = 0;
        }
        // Returns a successful or failed login attempt
        if (username == userResults && password == passResults){   
            name.push_back(fNameResults);
            name.push_back(lNameResults);
            name.push_back(userResults);
            name.push_back(totalResults);
            this->hide();
        }
        m_db.close();
}
void loginwindow2::newUser(QVector<QVariant> user)
{
        Log log;
        QString userName = user[0].toString();
        QString password = user[1].toString();
        QString isAdmin = user[2].toString();
        QString fName = user[3].toString();
        QString lName = user[4].toString();
        QString email = user[5].toString();
        QString total = user[6].toString();
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("Login.db");
        if(!m_db.open()){
            qDebug() << "Error: connection with database failed";
        }
        else{
            qDebug() << "Database: connection ok";
            log.dbOperationSuccess();
        }
        //queries the database
        QSqlQuery query;
        query.prepare("INSERT INTO  Login VALUES (?,?,?,?,?,?,?)");
        query.addBindValue(userName);
        query.addBindValue(password);
        query.addBindValue(isAdmin);
        query.addBindValue(fName);
        query.addBindValue(lName);
        query.addBindValue(email);
        query.addBindValue(total);
        query.exec();
        while (query.next())
        {
        }
        m_db.close();
}
QVector<QVariant> loginwindow2::searchedUser(QString username)
{
        QVector<QVariant> results;
        Log log;
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("Login.db");
        if(!m_db.open()){
            qDebug() << "Error: connection with database failed";
        }
        else{
            qDebug() << "Database: connection ok";
            log.dbOperationSuccess();
        }
        //queries the database
        QSqlQuery query;
        query.prepare("SELECT * FROM Login WHERE USERNAME = ? ");
        query.addBindValue(username);
        query.exec();
        int idUser = query.record().indexOf("USERNAME");
        int idPass = query.record().indexOf("PASSWORD");
        int idFName = query.record().indexOf("FirstName");
        int idLName = query.record().indexOf("LastName");
        int idTotal = query.record().indexOf("TotalSpent");
        int idAdmin = query.record().indexOf("isAdmin");
        int idEmail = query.record().indexOf("Email");
        while (query.next())
        {
            results.push_back(query.value(idUser).toString());
            results.push_back(query.value(idPass).toString());
            results.push_back(query.value(idAdmin).toString());
            results.push_back(query.value(idFName).toString());
            results.push_back(query.value(idLName).toString());
            results.push_back(query.value(idEmail).toString());
            results.push_back(query.value(idTotal).toString());
        }
        m_db.close();
        return results;
}
void loginwindow2::updateUser(QVector<QVariant> user)
{
        Log log;
        QString userName = user[0].toString();
        QString password = user[1].toString();
        QString isAdmin = user[2].toString();
        QString fName = user[3].toString();
        QString lName = user[4].toString();
        QString email = user[5].toString();
        QString total = user[6].toString();
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("Login.db");
        if(!m_db.open()){
            qDebug() << "Error: connection with database failed";
        }
        else{
            qDebug() << "Database: connection ok";
            log.dbOperationSuccess();
        }
        //queries the database
        QSqlQuery query;
        query.prepare("UPDATE Login SET Password = ?, isAdmin = ?, FirstName = ?, LastName = ?, Email = ?, TotalSpent = ? Where Username = ?");
        query.addBindValue(password);
        query.addBindValue(isAdmin);
        query.addBindValue(fName);
        query.addBindValue(lName);
        query.addBindValue(email);
        query.addBindValue(total);
        query.addBindValue(userName);
        query.exec();
        while (query.next())
        {
        }
        m_db.close();
}
void loginwindow2:: gameOn()
{
        QString link = "https://www.freepacman.org";
        QDesktopServices::openUrl(QUrl(link));
}

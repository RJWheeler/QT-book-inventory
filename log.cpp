#include "log.h"
#include "qvariant.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <QString>
#include <QVector>
#include <QTextStream>
using namespace std;
Log::Log()
{

}
int Log::dbOperationSuccess()
{
    ofstream file;
    file.open("Log.txt");
    file << "Database opened sucess. \n";
    file.close();
    return 0;
}
int Log::userLoginSuccess()
{
    ofstream file;
    file.open("Log.txt");
    file << "Login sucess. \n";
    file.close();
    return 0;
}
int Log::userExits()
{
    ofstream file;
    file.open("Log.txt");
    file << "Exit sucess. \n";
    file.close();
    return 0;
}

//Recently Added
int Log::printReceipt(QVector<QVariant> results, double subtotal, double discount){

    ofstream file;
    file.open("Receipt.txt");
    file << "Here is your Receipt: \n";
    for (int i = 0; i < results.size(); i++){
        if(i %2 == 0){
            file << "Book's title: ";
        }
        else{
            file << "Price: ";
        }
        string result = results[i].toString().toStdString();
        file << result << " \n";
    }
    double taxes = (subtotal - discount) * 0.06;
    double totalPrice = (subtotal - discount) * 1.06;
    QString subtotalString = QString::number(subtotal);
    QString totalString = QString::number(totalPrice,'f',2);
    QString taxesString = QString::number(taxes,'f',2);
    QString discountString = QString::number(discount,'f',2);
    file << "Subtotal: ";
    file << subtotalString.toStdString() << "\n";
    file << "Discount: ";
    file << discountString.toStdString()<< "\n";
    file << "Taxes: ";
    file << taxesString.toStdString() << "\n";
    file << "Total: ";
    file << totalString.toStdString() << "\n";
    file.close();
    return 0;
}

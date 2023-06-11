#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <QString>
using namespace std;

class Log
{
public:
    Log();
    int dbOperationSuccess();
    int userLoginSuccess();
    int userExits();
    int printReceipt(QVector<QVariant>, double subtotal, double discount);
};

#endif // LOG_H

#ifndef LOGINWINDOW2_H
#define LOGINWINDOW2_H

#include <QDialog>
#include "qsqldatabase.h"

namespace Ui {
class loginwindow2;
}

class loginwindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit loginwindow2(QWidget *parent = nullptr);
    ~loginwindow2();
    QVector<QVariant> name;
    QVector<QVariant> nameReturn();
    double addTotal(double total,QString username,double totalResults);
    QVector<QVariant> searchedUser(QString username);





private:
    Ui::loginwindow2 *ui;
    QSqlDatabase m_db;
 public slots:
    void onPushButtonClicked();
    void guestCheckout();
    void gameOn();
    void newUser(QVector<QVariant> user);
    void updateUser(QVector<QVariant> user);
};

#endif // LOGINWINDOW2_H

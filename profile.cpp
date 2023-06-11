#include "profile.h"
#include "loginwindow2.h"
#include "ui_profile.h"

profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);

    login.exec();
    name = login.nameReturn();
    ui->firstName->setText(name[0].toString());
    ui->lastName->setText(name[1].toString());
    ui->username->setText(name[2].toString());
    double total = name[3].toDouble();
    QString totalString = QString::number(total,'f',2);
    ui->totalSpent->setText(totalString);
    ui->password->setText(name[4].toString());
    ui->email->setText(name[5].toString());
}

profile::~profile()
{
    delete ui;
}
void profile::updatedProfile()
{

    QVector<QVariant> updateUserInfo;
    updateUserInfo.push_back(ui->username->text());
    updateUserInfo.push_back(ui->password->text());
    updateUserInfo.push_back(0);
    updateUserInfo.push_back(ui->firstName->text());
    updateUserInfo.push_back(ui->lastName->text());
    updateUserInfo.push_back(ui->email->text());
    updateUserInfo.push_back(ui->totalSpent->text());
    login.updateUser(updateUserInfo);
}

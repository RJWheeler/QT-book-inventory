#include "updateuser.h"
#include "loginwindow2.h"
#include "ui_updateuser.h"

updateUser::updateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateUser)
{
    ui->setupUi(this);
}

updateUser::~updateUser()
{
    delete ui;
}
void updateUser::enableButton()
{
    ui->passwordInput->setEnabled(true);
    ui->updateUserButton->setEnabled(true);
    ui->admincheck->setEnabled(true);
    ui->firstNameinput->setEnabled(true);
    ui->lastNameInput->setEnabled(true);
    ui->emailInput->setEnabled(true);
    ui->totalSpent->setEnabled(true);
}
void updateUser:: search()
{
    loginwindow2 login;
    username = ui->usernameInput->text();
    QVector<QVariant> results = login.searchedUser(username);
    ui->passwordInput->setText(results[1].toString());
    if(results[2].toString() == "1"){
        ui->admincheck->setCheckState(Qt::Checked);
    }
    ui->firstNameinput->setText(results[3].toString());
    ui->lastNameInput->setText(results[4].toString());
    double total = results[6].toDouble();
    QString totalString = QString::number(total,'f',2);
    ui->totalSpent->setText(totalString);
    ui->emailInput->setText(results[5].toString());
}
void updateUser:: updatedUser()
{
    loginwindow2 login;
    QVector<QVariant> updateUserInfo;
    updateUserInfo.push_back(username);
    updateUserInfo.push_back(ui->passwordInput->text());
    bool isAdmin = ui->admincheck->isChecked();
    int admin;
    if(isAdmin == true){
        admin = 1;
    }
    else{
        admin = 0;
    }
    updateUserInfo.push_back(admin);
    updateUserInfo.push_back(ui->firstNameinput->text());
    updateUserInfo.push_back(ui->lastNameInput->text());
    updateUserInfo.push_back(ui->emailInput->text());
    updateUserInfo.push_back(ui->totalSpent->text());
    login.updateUser(updateUserInfo);
}

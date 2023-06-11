#include "adduser.h"
#include "loginwindow2.h"
#include "ui_adduser.h"
#include <QMessageBox>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}
void AddUser::addNewUser()
{
    loginwindow2 login;
    QVector<QVariant> newUserInfo;
    newUserInfo.push_back(ui->UserNameInput->text());

    QMessageBox warning;
    warning.setText("Required Field");
    warning.setInformativeText("The field is required");
    newUserInfo.push_back(ui->PasswordInput->text());
    bool isAdmin = ui->AdminCheckBox->isChecked();
    int admin;
    if(isAdmin == true){
        admin = 1;
    }
    else{
        admin = 0;
    }
    newUserInfo.push_back(admin);
    newUserInfo.push_back(ui->FirstNameInput->text());
    newUserInfo.push_back(ui->LastNameInput->text());
    newUserInfo.push_back(ui->EmailInput->text());
    int totalspent = 0;
    newUserInfo.push_back(totalspent);
    if(ui->UserNameInput->text() != "" && ui->PasswordInput->text() != "" &&
        ui->EmailInput->text() !="" && ui->FirstNameInput->text() != "" && ui->LastNameInput->text() != "")
    {
        login.newUser(newUserInfo);
        this->hide();
    }
    else
    {
         QMessageBox::information(this, "Error", "Please fill in all the information.");
    }
}

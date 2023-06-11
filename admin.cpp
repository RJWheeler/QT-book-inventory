#include "admin.h"
#include "ui_admin.h"
#include "adduser.h"
#include "addbook.h"
#include "updatebook.h"
#include "updateuser.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}
void Admin:: adminAddUser()
{
    AddUser addUser;
    addUser.exec();
}
void Admin::adminAddBook()
{
    addBook addBook;
    addBook.exec();
}
void Admin::adminUpdateUser()
{
    updateUser user;
    user.exec();
}
void Admin::adminUpdateBook()
{
    updateBook book;
    book.exec();
}

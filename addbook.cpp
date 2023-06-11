#include "addbook.h"
#include "qtbookinventory.h"
#include "ui_addbook.h"
#include <QMessageBox>

addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}
void addBook::addNewBook()
{
    QTBookinventory book;
    QVector<QVariant> newBookInfo;
    newBookInfo.push_back(ui->isbnInput->text());
    newBookInfo.push_back(ui->authorInput->text());
    newBookInfo.push_back(ui->yearInput->text());
    newBookInfo.push_back(ui->publisherInput->text());
    newBookInfo.push_back(ui->genreInput->text());
    newBookInfo.push_back(ui->priceInput->text());
    newBookInfo.push_back(ui->quantityInput->text());
    newBookInfo.push_back(ui->titleInput->text());
    if(ui->isbnInput->text() != "" && ui->authorInput->text() != "" &&
      ui->yearInput->text() !="" && ui->publisherInput->text() != "" && ui->genreInput->text() != "" && ui->priceInput->text() != ""
        && ui->quantityInput->text() != "" && ui->titleInput->text() != "")
    {
        book.newBook(newBookInfo);
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "Error", "Please fill in all the information.");
    }

}


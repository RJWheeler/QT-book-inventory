#include "updatebook.h"
#include "qtbookinventory.h"
#include "ui_updatebook.h"

updateBook::updateBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateBook)
{
    ui->setupUi(this);
}

updateBook::~updateBook()
{
    delete ui;
}
void updateBook::enablebutton()
{
    ui->updateButton->setEnabled(true);
    ui->authorInput->setEnabled(true);
    ui->genreInput->setEnabled(true);
    ui->isbnInput->setEnabled(true);
    ui->priceInput->setEnabled(true);
    ui->publisherInput->setEnabled(true);
    ui->qtyInput->setEnabled(true);
    ui->yearInput->setEnabled(true);
}
void updateBook:: search()
{
    QTBookinventory book;
    title = ui->titleInput->text();
    QVector<QVariant> results = book.bookSearchByTitle(title);
    ui->titleInput->setText(results[0].toString());
    ui->authorInput->setText(results[1].toString());
    ui->priceInput->setText(results[2].toString());
    ui->qtyInput->setText(results[3].toString());
    ui->publisherInput->setText(results[5].toString());
    ui->genreInput->setText(results[4].toString());
    ui->yearInput->setText(results[6].toString());
    ui->isbnInput->setText(results[7].toString());
}
void updateBook:: updatedBook()
{
    QTBookinventory book;
    QVector<QVariant> updateBookInfo;
    updateBookInfo.push_back(ui->isbnInput->text());
    updateBookInfo.push_back(ui->authorInput->text());
    updateBookInfo.push_back(ui->yearInput->text());
    updateBookInfo.push_back(ui->publisherInput->text());
    updateBookInfo.push_back(ui->genreInput->text());
    updateBookInfo.push_back(ui->priceInput->text());
    updateBookInfo.push_back(ui->qtyInput->text());
    updateBookInfo.push_back(title);
    book.updateBook(updateBookInfo);

}

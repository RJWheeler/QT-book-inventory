#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QFile file("notes.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "file not open");
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}



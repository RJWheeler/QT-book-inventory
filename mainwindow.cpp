#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow2.h"
#include "qtbookinventory.h"
#include "profile.h"
#include "dialog.h"
#include <vector>
#include<QVector>
#include<QList>
#include <QTextStream>
#include <QMessageBox>
#include <QScreen>
#include <QDialog>
#include <QStatusBar>
#include <iostream>
#include <QSysInfo>
#include <QVariant>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include "log.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTBookinventory db;
    ui->statusbar->showMessage(db.recordsAmount());
    subtotal = 0;
    loginChecked = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}
// searches for entered book title
void MainWindow::searchTitle()
{
    QString title = ui->SearchBar->text();
    QTBookinventory db;
    QVector<QVariant> results = db.bookSearchByTitle(title);
    for(int i = 0; i < results.size(); i++){
                ui->SearchResults->append(results[i].toString());
            }
    if (results.size() == 0){
        ui->SearchResults->append("No results found");
        QMessageBox::information(this, "0 matches found", QString ("No matches found for %1. Please try again")
                .arg(title));
    }

}

// add item to shopping cart when button clicked
void MainWindow::addToShoppingCart()
{
    QString title = ui->SearchBar->text();
    QTBookinventory db;
    QVector<QVariant> results = db.addToShoppingCart(title);
    if(results.size() > 0){
        subtotal += results[1].toDouble();
    }
    for(int i = 0; i < results.size(); i++){
        shoppingCart.push_back(results[i]);
    }
    if (results.size() == 0){
        ui->SearchResults->append("Nothing in your cart.");
        QMessageBox::information(this, "Empty cart", "Your cart is empty");
    }

}

// Grabs the system information
QString cpuArch = QSysInfo::currentCpuArchitecture().toLocal8Bit().constData();
QString prodType = QSysInfo::prettyProductName().toLocal8Bit().constData();
QString kernelType = QSysInfo::kernelType().toLocal8Bit().constData();
QString kernelVersion = QSysInfo::kernelVersion().toLocal8Bit().constData();
QString machineID = QSysInfo::machineHostName().toLocal8Bit().constData();

QString Arch = "CPU: " + cpuArch + "\n";
QString Product = "Product: " + prodType + "\n";
QString KT = "Kernel Type: " + kernelType + "\n";
QString KV = "Kernel Version: " + kernelVersion + "\n";
QString Machine = "Machine ID: " + machineID;

// Displays sys_info when button pressed
void MainWindow::on_actionSystem_Info_triggered()
{
    QMessageBox::information(this, "Info Box", "System Info", QString("%1 %2 %3 %4 %5").arg(Arch).arg(Product).arg(KT).arg(KV).arg(Machine));
}

// login to system when button clicked
void MainWindow::on_actionLogin_triggered()
{
    loginwindow2 loginwindow;
    loginwindow.exec();
    namereturn = loginwindow.nameReturn();
    loginChecked = true;


}

// opens a view of the shopping cart
void MainWindow::open_shopping_cart()
{

    ui->SearchResults->clear();
    ui->SearchBar->clear();
    ui->SearchBar->setText("Shopping Cart");
    double taxes = subtotal * 0.06;
    double totalPrice = subtotal * 1.06;
    for(int i = 0; i < shoppingCart.size(); i++){
         ui->SearchResults->append(shoppingCart[i].toString());
    }
    QString subtotalString = QString::number(subtotal);
    QString totalString = QString::number(totalPrice,'f',2);
    QString taxesString = QString::number(taxes,'f',2);
    ui-> SearchResults->append("Subtotal:");
    ui -> SearchResults -> append(subtotalString);
    ui -> SearchResults -> append("Taxes:");
    ui -> SearchResults -> append(taxesString);
    ui -> SearchResults -> append("Total:");
    ui -> SearchResults  -> append(totalString);
}
void MainWindow::check_out(){
    loginwindow2 loginwindow;
    QTBookinventory book;
    Log log;
    //Discount codes
    double totalPrice;
    double discountAmount;
    if(loginChecked == true){
    QString discountCode = QInputDialog::getText(this, tr("Get text value(QLineEdit)"), "Enter Discount Code: ");
    if(discountCode == "fiveOff"){
         totalPrice = subtotal * 0.95;
         discountAmount = subtotal * 0.05;
    }
    else if(discountCode == "tenOff"){
         totalPrice = subtotal * 0.9;
         discountAmount = subtotal * 0.1;
    }
    else{
        totalPrice = subtotal * 1.00;
        discountAmount = 0.00;
    }
    }
    totalPrice = totalPrice * 1.06;
    if(namereturn.size() > 0){
    double lifetotal = loginwindow.addTotal(totalPrice,namereturn[2].toString(),namereturn[3].toDouble());
    QString nameString = "Thank you, " + namereturn[0].toString()+ " " + namereturn[1].toString() + "\n";
    QString discountString = "You savings on this purchase is " + QString::number(discountAmount,'f',2) + "\n";
    QString totalString = "Lifetime Total spent: " + QString::number(lifetotal,'f',2) + "\n";
    QMessageBox::information(this, "Checkout", "This trip: ", QString("%1 %3 %2").arg(nameString).arg(totalString).arg(discountString));
    for(int i = 0; i < shoppingCart.size(); i++){
        if(i%2 == 0){

            QVector<QVariant> results = book.bookSearchByTitle(shoppingCart[i].toString());
            int qty = results[3].toInt();
            qty--;
            book.updateQty(shoppingCart[i].toString(),qty);
        }
       }
    log.printReceipt(shoppingCart, subtotal , discountAmount);
    }
    else{
    loginwindow2 loginwindow;
    loginwindow.exec();
    namereturn = loginwindow.nameReturn();
    loginChecked = true;
    check_out();
    }
}

void MainWindow::on_actionNote_triggered()
{
    Dialog dialog;
    dialog.setModal(true);
    dialog.exec();
}
void MainWindow:: profileUser()
{
    profile userProfile;
    userProfile.exec();
}

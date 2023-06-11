#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QVariant> shoppingCart;
    double subtotal;
    QVector<QVariant> namereturn;
    bool loginChecked;


private:
    Ui::MainWindow *ui;
public slots:
    void searchTitle();
    void addToShoppingCart();
    void on_actionLogin_triggered();
    void on_actionSystem_Info_triggered();
    void open_shopping_cart();
    void check_out();
    void profileUser();

private slots:
    void on_actionNote_triggered();
};
#endif // MAINWINDOW_H

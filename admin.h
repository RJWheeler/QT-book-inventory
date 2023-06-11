#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private:
    Ui::Admin *ui;
private slots:
    void adminAddUser();
    void adminAddBook();
    void adminUpdateBook();
    void adminUpdateUser();
};

#endif // ADMIN_H

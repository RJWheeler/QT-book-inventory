#ifndef UPDATEUSER_H
#define UPDATEUSER_H

#include <QDialog>

namespace Ui {
class updateUser;
}

class updateUser : public QDialog
{
    Q_OBJECT

public:
    explicit updateUser(QWidget *parent = nullptr);
    ~updateUser();
    QString username;

private:
    Ui::updateUser *ui;
private slots:
    void enableButton();
    void search();
    void updatedUser();
};

#endif // UPDATEUSER_H

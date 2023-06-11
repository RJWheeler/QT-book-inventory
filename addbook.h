#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private:
    Ui::addBook *ui;
private slots:
    void addNewBook();
};

#endif // ADDBOOK_H

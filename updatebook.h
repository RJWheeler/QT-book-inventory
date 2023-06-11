#ifndef UPDATEBOOK_H
#define UPDATEBOOK_H

#include <QDialog>

namespace Ui {
class updateBook;
}

class updateBook : public QDialog
{
    Q_OBJECT

public:
    explicit updateBook(QWidget *parent = nullptr);
    ~updateBook();
    QString title;

private:
    Ui::updateBook *ui;
private slots:
    void enablebutton();
    void search();
    void updatedBook();
};

#endif // UPDATEBOOK_H

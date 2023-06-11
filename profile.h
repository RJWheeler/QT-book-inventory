#ifndef PROFILE_H
#define PROFILE_H

#include "loginwindow2.h"
#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();
    QVector<QVariant> name;
    loginwindow2 login;

private:
    Ui::profile *ui;
private slots:
    void updatedProfile();

};

#endif // PROFILE_H

#ifndef ADMINAUTHENTICATE_H
#define ADMINAUTHENTICATE_H

#include <QDialog>
#include <QMessageBox>
#include "admindes.h"

namespace Ui {
class adminauthenticate;
}

class adminauthenticate : public QDialog
{
    Q_OBJECT

public:
    explicit adminauthenticate(QWidget *parent = nullptr);
    ~adminauthenticate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::adminauthenticate *ui;
    admindes *ptradmin;
};

#endif // ADMINAUTHENTICATE_H

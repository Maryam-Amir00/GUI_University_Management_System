#ifndef STUDENTAUTHENTICATE_H
#define STUDENTAUTHENTICATE_H

#include <QDialog>
#include "studentdes.h"
#include <QMessageBox>

namespace Ui {
class studentauthenticate;
}

class studentauthenticate : public QDialog
{
    Q_OBJECT

public:
    explicit studentauthenticate(QWidget *parent = nullptr);
    ~studentauthenticate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::studentauthenticate *ui;
    studentdes *ptrstudent;
};

#endif // STUDENTAUTHENTICATE_H

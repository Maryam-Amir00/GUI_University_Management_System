#ifndef REMOVESTUDENT_H
#define REMOVESTUDENT_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include "struct.h"

namespace Ui {
class removestudent;
}


class removestudent : public QDialog
{
    Q_OBJECT

public:
    explicit removestudent(QWidget *parent = nullptr);
    ~removestudent();
    void onConfirmClicked();
    bool removeStudentData(int rollNo);

private slots:
    void on_pushButton_clicked();

private:
    Ui::removestudent *ui;
};

#endif // REMOVESTUDENT_H



#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include "struct.h"

namespace Ui {
class addstudent;
}


class addstudent : public QDialog
{
    Q_OBJECT

public:
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();
    void onConfirmClicked();
    bool rollNoExists(int rollNo);
    void saveStudentData(const Student& student);
    void clearInputFields();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addstudent *ui;
};

#endif // ADDSTUDENT_H

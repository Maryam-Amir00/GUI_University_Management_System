// studentexist.h
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include "struct.h"

class StudentExist : public QDialog
{
    Q_OBJECT
public:
    explicit StudentExist(QWidget *parent = nullptr);

private slots:
    void onCheckExistenceClicked();

private:
    QLineEdit *rollNoEdit;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *departmentEdit;
    QDateEdit *dateOfBirthEdit;
    QPushButton *checkExistenceButton;

    bool checkStudentExistence(const Student& student);
};

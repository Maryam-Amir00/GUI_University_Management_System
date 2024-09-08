// updatestudent.h
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

class updatestudent : public QDialog
{
    Q_OBJECT

public:
    explicit updatestudent(QWidget *parent = nullptr);

private slots:
    void onSearchClicked();
    void onUpdateClicked();

private:
    QLineEdit *rollNoEdit;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *departmentEdit;
    QDateEdit *dateOfBirthEdit;
    QPushButton *searchButton;
    QPushButton *updateButton;

    Student currentStudent;
    qint64 currentPosition;

    bool findStudent(int rollNo);
    void updateStudentInFile();
    void enableUpdateFields(bool enable);
    void clearInputFields();
};

#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include "teacherstruct.h"

class TeacherExist : public QDialog
{
    Q_OBJECT
public:
    explicit TeacherExist(QWidget *parent = nullptr);

private slots:
    void onCheckExistenceClicked();

private:
    QLineEdit *idEdit;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *courseEdit;
    QPushButton *checkExistenceButton;

    bool checkTeacherExistence(const Teacher& teacher);
};

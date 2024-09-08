// updateteacher.h
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

class updateteacher : public QDialog
{
    Q_OBJECT

public:
    explicit updateteacher(QWidget *parent = nullptr);

private slots:
    void onSearchClicked();
    void onUpdateClicked();

private:
    QLineEdit *idEdit;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *courseEdit;
    QPushButton *searchButton;
    QPushButton *updateButton;

    Teacher currentTeacher;
    qint64 currentPosition;

    bool findTeacher(int id);
    void updateTeacherInFile();
    void enableUpdateFields(bool enable);
    void clearInputFields();
};

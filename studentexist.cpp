#include "studentexist.h"
#include <cstring>

StudentExist::StudentExist(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Check Student Existence");
    resize(300, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    rollNoEdit = new QLineEdit(this);
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    departmentEdit = new QLineEdit(this);
    dateOfBirthEdit = new QDateEdit(this);
    checkExistenceButton = new QPushButton("Check Existence", this);

    layout->addWidget(new QLabel("Roll No:"));
    layout->addWidget(rollNoEdit);
    layout->addWidget(new QLabel("First Name:"));
    layout->addWidget(firstNameEdit);
    layout->addWidget(new QLabel("Last Name:"));
    layout->addWidget(lastNameEdit);
    layout->addWidget(new QLabel("Department:"));
    layout->addWidget(departmentEdit);
    layout->addWidget(new QLabel("Date of Birth:"));
    layout->addWidget(dateOfBirthEdit);
    layout->addWidget(checkExistenceButton);

    connect(checkExistenceButton, &QPushButton::clicked, this, &StudentExist::onCheckExistenceClicked);
}

void StudentExist::onCheckExistenceClicked()
{
    Student studentToCheck;

    bool ok;
    studentToCheck.rollNo = rollNoEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid Roll Number");
        return;
    }
    strncpy(studentToCheck.firstName, firstNameEdit->text().toUtf8().constData(), 25);
    studentToCheck.firstName[25] = '\0';
    strncpy(studentToCheck.lastName, lastNameEdit->text().toUtf8().constData(), 25);
    studentToCheck.lastName[25] = '\0';
    strncpy(studentToCheck.department, departmentEdit->text().toUtf8().constData(), 14);
    studentToCheck.department[14] = '\0';
    studentToCheck.dateOfBirth = dateOfBirthEdit->date();

    if (checkStudentExistence(studentToCheck)) {
        QMessageBox::information(this, "Existence Check", "The student with the given details exists in the file.");
    } else {
        QMessageBox::information(this, "Existence Check", "The student with the given details does not exist in the file.");
    }
}

bool StudentExist::checkStudentExistence(const Student& student)
{
    QFile file("students.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    Student fileStudent;
    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&fileStudent), sizeof(Student));
        if (fileStudent.rollNo == student.rollNo &&
            strcmp(fileStudent.firstName, student.firstName) == 0 &&
            strcmp(fileStudent.lastName, student.lastName) == 0 &&
            strcmp(fileStudent.department, student.department) == 0 &&
            fileStudent.dateOfBirth == student.dateOfBirth) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

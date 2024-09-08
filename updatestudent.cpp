// updatestudent.cpp
#include "updatestudent.h"

updatestudent::updatestudent(QWidget *parent)
    : QDialog(parent), currentPosition(-1)
{
    setWindowTitle("Update Student Record");
    resize(300, 250);

    QVBoxLayout *layout = new QVBoxLayout(this);

    rollNoEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    departmentEdit = new QLineEdit(this);
    dateOfBirthEdit = new QDateEdit(this);
    updateButton = new QPushButton("Update", this);

    layout->addWidget(new QLabel("Roll No:"));
    layout->addWidget(rollNoEdit);
    layout->addWidget(searchButton);
    layout->addWidget(new QLabel("First Name:"));
    layout->addWidget(firstNameEdit);
    layout->addWidget(new QLabel("Last Name:"));
    layout->addWidget(lastNameEdit);
    layout->addWidget(new QLabel("Department:"));
    layout->addWidget(departmentEdit);
    layout->addWidget(new QLabel("Date of Birth:"));
    layout->addWidget(dateOfBirthEdit);
    layout->addWidget(updateButton);

    connect(searchButton, &QPushButton::clicked, this, &updatestudent::onSearchClicked);
    connect(updateButton, &QPushButton::clicked, this, &updatestudent::onUpdateClicked);

    enableUpdateFields(false);
}

void updatestudent::onSearchClicked()
{
    bool ok;
    int rollNo = rollNoEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid Roll Number");
        return;
    }

    if (findStudent(rollNo)) {
        firstNameEdit->setText(currentStudent.firstName);
        lastNameEdit->setText(currentStudent.lastName);
        departmentEdit->setText(currentStudent.department);
        dateOfBirthEdit->setDate(currentStudent.dateOfBirth);
        enableUpdateFields(true);
    } else {
        QMessageBox::warning(this, "Error", "Student not found");
        enableUpdateFields(false);
        clearInputFields();
    }
}

void updatestudent::onUpdateClicked()
{
    strncpy(currentStudent.firstName, firstNameEdit->text().toUtf8().constData(), 25);
    currentStudent.firstName[25] = '\0';
    strncpy(currentStudent.lastName, lastNameEdit->text().toUtf8().constData(), 25);
    currentStudent.lastName[25] = '\0';
    strncpy(currentStudent.department, departmentEdit->text().toUtf8().constData(), 14);
    currentStudent.department[14] = '\0';
    currentStudent.dateOfBirth = dateOfBirthEdit->date();

    updateStudentInFile();
    QMessageBox::information(this, "Success", "Student record updated successfully");
    enableUpdateFields(false);
    clearInputFields();
}

bool updatestudent::findStudent(int rollNo)
{
    QFile file("students.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    while (!in.atEnd()) {
        currentPosition = file.pos();
        in.readRawData(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
        if (currentStudent.rollNo == rollNo) {
            file.close();
            return true;
        }
    }

    file.close();
    currentPosition = -1;
    return false;
}

void updatestudent::updateStudentInFile()
{
    QFile file("students.dat");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Could not open file for writing");
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    file.seek(currentPosition);
    out.writeRawData(reinterpret_cast<const char*>(&currentStudent), sizeof(Student));

    file.close();
}

void updatestudent::enableUpdateFields(bool enable)
{
    firstNameEdit->setEnabled(enable);
    lastNameEdit->setEnabled(enable);
    departmentEdit->setEnabled(enable);
    dateOfBirthEdit->setEnabled(enable);
    updateButton->setEnabled(enable);
}

void updatestudent::clearInputFields()
{
    rollNoEdit->clear();
    firstNameEdit->clear();
    lastNameEdit->clear();
    departmentEdit->clear();
    dateOfBirthEdit->setDate(QDate::currentDate());
}



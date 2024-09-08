#include "addstudent.h"
#include "ui_addstudent.h"
using namespace std;


addstudent::addstudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addstudent)
{
    ui->setupUi(this);
}

addstudent::~addstudent()
{
    delete ui;
}

void addstudent::onConfirmClicked()
{
    Student student;
    student.rollNo = ui->rollNoEdit->text().toInt(); // Convert directly to int

    // Get input strings from UI
    string firstNameInput = ui->firstNameEdit->text().toStdString();
    string lastNameInput = ui->lastNameEdit->text().toStdString();
    string departmentInput = ui->departmentEdit->text().toStdString();

    // Check lengths before copying
    if (firstNameInput.length() > 25 || lastNameInput.length() > 25 || departmentInput.length() > 14) {
        QMessageBox::warning(this, "Input Error", "Input exceeds maximum allowed length!");
        return;
    }

    // Copy input strings to character arrays
    strncpy(student.firstName, firstNameInput.c_str(), 25);
    strncpy(student.lastName, lastNameInput.c_str(), 25);
    strncpy(student.department, departmentInput.c_str(), 14);

    // Null-terminate the strings
    student.firstName[25] = '\0';
    student.lastName[25] = '\0';
    student.department[14] = '\0';

    // Check if roll number already exists
    if (rollNoExists(student.rollNo)) {
        QMessageBox::warning(this, "Input Error", "Roll number already exists. Please enter a valid roll number.");
        return;
    }

    // Function to check if a string contains only alphabetical characters
    auto isAlphabetical = [](const char* str) {
        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (!isalpha(static_cast<unsigned char>(str[i]))) {
                return false;
            }
        }
        return true;
    };

    // Validate inputs
    if (strlen(student.firstName) == 0 || strlen(student.lastName) == 0 || strlen(student.department) == 0 ||
        !isAlphabetical(student.firstName) || !isAlphabetical(student.lastName) || !isAlphabetical(student.department)) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled correctly and contain only alphabetical characters!");
        return;
    }

    // Process date of birth
    student.dateOfBirth = ui->dateOfBirthEdit->date();

    // Validate the year of the date of birth
    if (student.dateOfBirth.year() < 1995) {
        QMessageBox::warning(this, "Input Error", "Year of birth must be 1995 or later.");
        return;
    }

    // Attempt to save student data
    try {
        saveStudentData(student);
        QMessageBox::information(this, "Success", "Student added successfully!");
        clearInputFields();
    } catch (const exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void addstudent::clearInputFields()
{
    ui->firstNameEdit->clear();
    ui->lastNameEdit->clear();
    ui->departmentEdit->clear();
    ui->rollNoEdit->clear();
    ui->dateOfBirthEdit->setDate(QDate::currentDate());
}

void addstudent::saveStudentData(const Student& student)
{
    QFile file("students.dat");

    if (!file.open(QIODevice::Append)) {
        throw std::runtime_error("Failed to open the file.");
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);

    // Write the student data at the end of the file
    out.writeRawData(reinterpret_cast<const char*>(&student), sizeof(Student));

    if (file.error() != QFileDevice::NoError) {
        throw std::runtime_error("Failed to write data to the file.");
    }

    file.close();
}


bool addstudent::rollNoExists(int rollNo)
{
    QFile file("students.dat");

    if (!file.open(QIODevice::ReadOnly)) {
        return false; // File could not be opened
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);

    bool found = false;
    Student student;

    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&student), sizeof(Student));
        if (student.rollNo == rollNo) {
            found = true;
            break;
        }
    }

    file.close();
    return found;
}

void addstudent::on_pushButton_clicked()
{
    onConfirmClicked();
}




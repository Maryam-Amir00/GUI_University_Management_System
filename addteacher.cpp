#include "addteacher.h"
#include "ui_addteacher.h"
using namespace std;


addteacher::addteacher(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addteacher)
{
    ui->setupUi(this);
}

addteacher::~addteacher()
{
    delete ui;
}

void addteacher::onConfirmClicked()
{
    // Check if ID is empty
    if (ui->idEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "ID cannot be empty!");
        return;
    }

    // Validate ID (only integers)
    bool ok;
    int id = ui->idEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "ID must be an integer!");
        return;
    }

    Teacher teacher;
    teacher.id = id;

    // Get input strings from UI
    string firstNameInput = ui->firstNameEdit->text().toStdString();
    string lastNameInput = ui->lastNameEdit->text().toStdString();
    string courseInput = ui->courseEdit->text().toStdString();

    // Check if course is empty
    if (courseInput.empty()) {
        QMessageBox::warning(this, "Input Error", "Course cannot be empty!");
        return;
    }

    // Check lengths before copying
    if (firstNameInput.length() > 25 || lastNameInput.length() > 25 || courseInput.length() > 25) {
        QMessageBox::warning(this, "Input Error", "Input exceeds maximum allowed length!");
        return;
    }

    // Copy input strings to character arrays
    strncpy(teacher.firstName, firstNameInput.c_str(), 25);
    strncpy(teacher.lastName, lastNameInput.c_str(), 25);
    strncpy(teacher.course, courseInput.c_str(), 25);

    // Null-terminate the strings
    teacher.firstName[25] = '\0';
    teacher.lastName[25] = '\0';
    teacher.course[25] = '\0';

    // Check if ID already exists
    if (idExists(teacher.id)) {
        QMessageBox::warning(this, "Input Error", "ID already exists. Please enter a valid ID.");
        return;
    }

    // Function to check if a string contains only alphabetical characters and spaces
    auto isAlphabetical = [](const char* str) {
        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (!isalpha(static_cast<unsigned char>(str[i])) && !isspace(static_cast<unsigned char>(str[i]))) {
                return false;
            }
        }
        return true;
    };

    // Validate inputs
    if (strlen(teacher.firstName) == 0 || strlen(teacher.lastName) == 0) {
        QMessageBox::warning(this, "Input Error", "First name and last name must be filled!");
        return;
    }

    if (!isAlphabetical(teacher.firstName) || !isAlphabetical(teacher.lastName)) {
        QMessageBox::warning(this, "Input Error", "First name and last name must contain only alphabetical characters!");
        return;
    }

    if (!isAlphabetical(teacher.course)) {
        QMessageBox::warning(this, "Input Error", "Course must contain only alphabetical characters!");
        return;
    }

    // Attempt to save teacher data
    try {
        saveTeacherData(teacher);
        QMessageBox::information(this, "Success", "Teacher added successfully!");
        clearInputFields();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void addteacher::clearInputFields()
{
    ui->firstNameEdit->clear();
    ui->lastNameEdit->clear();
    ui->courseEdit->clear();
    ui->idEdit->clear();
}

void addteacher::saveTeacherData(const Teacher& teacher)
{
    QFile file("teachers.dat");

    if (!file.open(QIODevice::Append)) {
        throw std::runtime_error("Failed to open the file.");
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);

    // Write the teacher data at the end of the file
    out.writeRawData(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));

    if (file.error() != QFileDevice::NoError) {
        throw std::runtime_error("Failed to write data to the file.");
    }

    file.close();
}

bool addteacher::idExists(int id)
{
    QFile file("teachers.dat");

    if (!file.open(QIODevice::ReadOnly)) {
        return false; // File could not be opened, assume ID does not exist
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);

    Teacher teacher;
    while (!in.atEnd()) {
        if (in.readRawData(reinterpret_cast<char*>(&teacher), sizeof(Teacher)) == -1) {
            file.close();
            return false; // Error reading file
        }
        if (teacher.id == id) {
            file.close();
            return true; // ID found
        }
    }

    file.close();
    return false; // ID not found
}

void addteacher::on_pushButton_clicked()
{
    onConfirmClicked();
}

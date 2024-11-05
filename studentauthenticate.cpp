#include "studentauthenticate.h"
#include "ui_studentauthenticate.h"

studentauthenticate::studentauthenticate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::studentauthenticate)
{
    ui->setupUi(this);
    ptrstudent = new studentdes();
}

studentauthenticate::~studentauthenticate()
{
    delete ptrstudent;
    delete ui;
}

void studentauthenticate::on_pushButton_clicked()
{
    QString studentInput = ui->usernameLineEdit->text(); // Get the username from a QLineEdit
    QString passInput = ui->passwordLineEdit->text(); // Get the password from a QLineEdit

    try {
        if (studentInput == "student" && passInput == "1234") {
            ptrstudent->show(); // Show the student dialog if authenticated
        }
        else {
            throw std::invalid_argument("Invalid credentials.");
        }
    } catch (const std::invalid_argument& e) {
        QMessageBox::warning(this, "Authentication Failed", e.what()); // Show a warning message box
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    }
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();

    this->close();
}


#include "teacherauthenticate.h"
#include "ui_teacherauthenticate.h"

teacherauthenticate::teacherauthenticate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teacherauthenticate)
{
    ui->setupUi(this);
    ptrteacher = new teacherdes();
}

teacherauthenticate::~teacherauthenticate()
{
    delete ptrteacher;
    delete ui;
}

void teacherauthenticate::on_pushButton_clicked()
{
    QString teacherInput = ui->usernameLineEdit->text(); // Get the username from a QLineEdit
    QString passInput = ui->passwordLineEdit->text(); // Get the password from a QLineEdit

    try {
        if (teacherInput == "teacher" && passInput == "1234") {
            ptrteacher->show(); // Show the student dialog if authenticated
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


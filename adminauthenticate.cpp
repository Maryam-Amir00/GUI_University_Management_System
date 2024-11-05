#include "adminauthenticate.h"
#include "ui_adminauthenticate.h"
using namespace std;



adminauthenticate::adminauthenticate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminauthenticate)
{
    ui->setupUi(this);
    ptradmin = new admindes();
}

adminauthenticate::~adminauthenticate()
{
    delete ptradmin;
    delete ui;
}

void adminauthenticate::on_pushButton_clicked()
{
    QString adminInput = ui->usernameLineEdit->text(); // Get the username from a QLineEdit
    QString passInput = ui->passwordLineEdit->text(); // Get the password from a QLineEdit

    try {
        if (adminInput == "admin" && passInput == "1234") {
            ptradmin->show(); // Show the admin dialog if authenticated
        }
        else {
            throw invalid_argument("Invalid credentials.");
        }
    } catch (const invalid_argument& e) {
        QMessageBox::warning(this, "Authentication Failed", e.what()); // Show a warning message box
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
}
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();

    this->close();
}

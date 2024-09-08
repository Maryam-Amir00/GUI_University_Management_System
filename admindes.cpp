#include "admindes.h"
#include "ui_admindes.h"

admindes::admindes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admindes)
{
    ui->setupUi(this);
    ptraddstudent = new addstudent();
    ptrremovestudent = new removestudent();
    ptrcheckrecords = new CheckRecord();
    ptraddteacher = new addteacher();
    ptrremoveteacher = new removeteacher();
    ptrcheckteacher = new CheckTeacher();
    ptrupdatestudent = new updatestudent();
    ptrupdateteacher = new updateteacher();
}

admindes::~admindes()
{
    delete ptrupdateteacher;
    delete ptrcheckteacher;
    delete ptrremoveteacher;
    delete ptraddteacher;
    delete ptrcheckrecords;
    delete ptrupdatestudent;
    delete ptrremovestudent;
    delete ptraddstudent;
    delete ui;
}

void admindes::on_pushButton_clicked()
{
    ptraddstudent->show();
}


void admindes::on_pushButton_2_clicked()
{
    ptrremovestudent->show();
}


void admindes::on_pushButton_3_clicked()
{
    ptrupdatestudent->show();
}


void admindes::on_pushButton_4_clicked()
{
    ptrcheckrecords->show();
}


void admindes::on_pushButton_5_clicked()
{
    ptraddteacher->show();
}


void admindes::on_pushButton_6_clicked()
{
    ptrremoveteacher->show();
}


void admindes::on_pushButton_8_clicked()
{
    ptrcheckteacher->show();
}


void admindes::on_pushButton_9_clicked()
{
    this->close();
}


void admindes::on_pushButton_7_clicked()
{
    ptrupdateteacher->show();
}


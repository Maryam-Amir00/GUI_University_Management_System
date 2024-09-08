#include "studentdes.h"
#include "ui_studentdes.h"

studentdes::studentdes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::studentdes)
{
    ui->setupUi(this);
    ptrcheckinfo = new CheckInfo();
    ptrstudentexist = new StudentExist();
}

studentdes::~studentdes()
{
    delete ptrstudentexist;
    delete ptrcheckinfo;
    delete ui;
}

void studentdes::on_pushButton_clicked()
{
    ptrcheckinfo->show();
}


void studentdes::on_pushButton_4_clicked()
{
    this->close();
}


void studentdes::on_pushButton_3_clicked()
{
    ptrstudentexist->show();
}


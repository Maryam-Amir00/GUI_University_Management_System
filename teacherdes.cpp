#include "teacherdes.h"
#include "ui_teacherdes.h"

teacherdes::teacherdes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teacherdes)
{
    ui->setupUi(this);
    ptrcheckteacherinfo = new CheckTeacherInfo();
    ptrteacherexist = new TeacherExist();
}

teacherdes::~teacherdes()
{
    delete ptrteacherexist;
    delete ptrcheckteacherinfo;
    delete ui;
}

void teacherdes::on_pushButton_clicked()
{
    ptrcheckteacherinfo->show();
}


void teacherdes::on_pushButton_2_clicked()
{
    ptrteacherexist->show();
}


void teacherdes::on_pushButton_3_clicked()
{
    this->close();
}


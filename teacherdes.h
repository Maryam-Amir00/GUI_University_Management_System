#ifndef TEACHERDES_H
#define TEACHERDES_H

#include <QDialog>
#include "checkteacherinfo.h"
#include "teacherexist.h"

namespace Ui {
class teacherdes;
}

class teacherdes : public QDialog
{
    Q_OBJECT

public:
    explicit teacherdes(QWidget *parent = nullptr);
    ~teacherdes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::teacherdes *ui;
    CheckTeacherInfo *ptrcheckteacherinfo;
    TeacherExist *ptrteacherexist;
};

#endif // TEACHERDES_H

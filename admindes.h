#ifndef ADMINDES_H
#define ADMINDES_H

#include <QDialog>
#include "addstudent.h"
#include "removestudent.h"
#include "checkrecords.h"
#include "addteacher.h"
#include "removeteacher.h"
#include "checkteacher.h"
#include "updatestudent.h"
#include "updateteacher.h"

namespace Ui {
class admindes;
}

class admindes : public QDialog
{
    Q_OBJECT

public:
    explicit admindes(QWidget *parent = nullptr);
    ~admindes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::admindes *ui;
    addstudent *ptraddstudent;
    removestudent *ptrremovestudent;
    CheckRecord *ptrcheckrecords;
    addteacher *ptraddteacher;
    removeteacher *ptrremoveteacher;
    CheckTeacher *ptrcheckteacher;
    updatestudent *ptrupdatestudent;
    updateteacher *ptrupdateteacher;
};

#endif // ADMINDES_H

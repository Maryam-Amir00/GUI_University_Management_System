#ifndef STUDENTDES_H
#define STUDENTDES_H

#include <QDialog>
#include "checkinfo.h"
#include "studentexist.h"

namespace Ui {
class studentdes;
}

class studentdes : public QDialog
{
    Q_OBJECT

public:
    explicit studentdes(QWidget *parent = nullptr);
    ~studentdes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::studentdes *ui;
    CheckInfo *ptrcheckinfo;
    StudentExist *ptrstudentexist;
};

#endif // STUDENTDES_H

#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include "teacherstruct.h"

namespace Ui {
class addteacher;
}

class addteacher : public QDialog
{
    Q_OBJECT

public:
    explicit addteacher(QWidget *parent = nullptr);
    ~addteacher();
    void onConfirmClicked();
    bool idExists(int id);
    void saveTeacherData(const Teacher& teacher);
    void clearInputFields();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addteacher *ui;
};

#endif // ADDTEACHER_H

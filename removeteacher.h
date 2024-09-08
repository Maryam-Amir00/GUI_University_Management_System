#ifndef REMOVETEACHER_H
#define REMOVETEACHER_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include "teacherstruct.h"

namespace Ui {
class removeteacher;
}

class removeteacher : public QDialog
{
    Q_OBJECT

public:
    explicit removeteacher(QWidget *parent = nullptr);
    ~removeteacher();
    void onConfirmClicked();
    bool removeTeacherData(int id);

private slots:
    void on_pushButton_clicked();

private:
    Ui::removeteacher *ui;
};

#endif // REMOVETEACHER_H

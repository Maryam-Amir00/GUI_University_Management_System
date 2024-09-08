#ifndef TEACHERAUTHENTICATE_H
#define TEACHERAUTHENTICATE_H

#include <QDialog>
#include "teacherdes.h"
#include <QMessageBox>

namespace Ui {
class teacherauthenticate;
}

class teacherauthenticate : public QDialog
{
    Q_OBJECT

public:
    explicit teacherauthenticate(QWidget *parent = nullptr);
    ~teacherauthenticate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::teacherauthenticate *ui;
    teacherdes *ptrteacher;
};

#endif // TEACHERAUTHENTICATE_H

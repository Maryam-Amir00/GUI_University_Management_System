// CheckTeacher.h

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QFile>
#include <QCloseEvent>
#include <QDataStream>
#include "teacherstruct.h"

class CheckTeacher : public QDialog
{
    Q_OBJECT

public:
    explicit CheckTeacher(QWidget *parent = nullptr);

private slots:
    void loadAllRecords();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QVBoxLayout *layout;
    QTextEdit *recordDisplay;
    QPushButton *loadButton;

    void readAllRecordsFromFile();
    QString formatTeacherRecord(const Teacher& teacher);

    static const int RECORD_SIZE = sizeof(Teacher);
};

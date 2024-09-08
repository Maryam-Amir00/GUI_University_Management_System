// CheckRecord.h

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QCloseEvent>
#include <QDate>
#include "struct.h"

class CheckRecord : public QDialog
{
    Q_OBJECT

public:
    explicit CheckRecord(QWidget *parent = nullptr);

private slots:
    void loadAllRecords();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QVBoxLayout *layout;
    QTextEdit *recordDisplay;
    QPushButton *loadButton;

    void readAllRecordsFromFile();
    QString formatStudentRecord(const Student& student);

    static const int RECORD_SIZE = sizeof(Student);
};

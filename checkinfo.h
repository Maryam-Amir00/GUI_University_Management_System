#ifndef CHECKINFO_H
#define CHECKINFO_H

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDate>
#include "struct.h"

namespace Ui {
class CheckInfo;
}

class CheckInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInfo(QWidget *parent = nullptr);

private slots:
    void loadRecord();

private:

    QVBoxLayout *layout;
    QTextEdit *recordDisplay;
    QLineEdit *rollNoInput;
    QPushButton *loadButton;
    void readRecordFromFile(int rollNo);
    QString formatStudentRecord(const Student& student);

    static const int RECORD_SIZE = sizeof(Student);
};

#endif // CHECKINFO_H

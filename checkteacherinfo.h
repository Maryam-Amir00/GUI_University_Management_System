#ifndef CHECKTEACHERINFO_H
#define CHECKTEACHERINFO_H

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QFile>
#include <QDataStream>
#include "teacherstruct.h"

namespace Ui {
class CheckTeacherInfo;
}

class CheckTeacherInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CheckTeacherInfo(QWidget *parent = nullptr);

private slots:
    void loadRecord();

private:
    QVBoxLayout *layout;
    QTextEdit *recordDisplay;
    QLineEdit *idInput;
    QPushButton *loadButton;

    void readRecordFromFile(int id);
    QString formatTeacherRecord(const Teacher& teacher);

    static const int RECORD_SIZE = sizeof(Teacher);
};

#endif // CHECKTEACHERINFO_H

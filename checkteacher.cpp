// CheckTeacher.cpp

#include "checkteacher.h"
#include <QMessageBox>

CheckTeacher::CheckTeacher(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Teacher Records");
    resize(600, 400);

    layout = new QVBoxLayout(this);

    recordDisplay = new QTextEdit(this);
    recordDisplay->setReadOnly(true);
    layout->addWidget(recordDisplay);

    loadButton = new QPushButton("Load All Records", this);
    layout->addWidget(loadButton);

    connect(loadButton, &QPushButton::clicked, this, &CheckTeacher::loadAllRecords);
}

void CheckTeacher::loadAllRecords()
{
    readAllRecordsFromFile();
}

void CheckTeacher::readAllRecordsFromFile()
{
    QString fileName = "teachers.dat";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file: " + fileName);
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    Teacher teacher;
    QString allRecords;
    int recordCount = 0;

    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&teacher), RECORD_SIZE);
        allRecords += formatTeacherRecord(teacher) + "\n\n";
        recordCount++;
    }

    file.close();

    if (recordCount > 0) {
        recordDisplay->setPlainText(allRecords);
        QMessageBox::information(this, "Success", QString("Loaded %1 teacher records.").arg(recordCount));
    } else {
        QMessageBox::information(this, "No Records", "No teacher records found in the file.");
    }
}

QString CheckTeacher::formatTeacherRecord(const Teacher& teacher)
{
    return QString("First Name: %1\n"
                   "Last Name: %2\n"
                   "ID: %3\n"
                   "Course: %4")
        .arg(QString::fromLatin1(teacher.firstName).trimmed())
        .arg(QString::fromLatin1(teacher.lastName).trimmed())
        .arg(teacher.id)
        .arg(QString::fromLatin1(teacher.course).trimmed());
}

void CheckTeacher::closeEvent(QCloseEvent *event)
{
    recordDisplay->clear();
    event->accept();
}

// CheckRecord.cpp

#include "checkrecords.h"
#include <QMessageBox>

CheckRecord::CheckRecord(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Student Records");
    resize(600, 400);

    layout = new QVBoxLayout(this);

    recordDisplay = new QTextEdit(this);
    recordDisplay->setReadOnly(true);
    layout->addWidget(recordDisplay);

    loadButton = new QPushButton("Load All Records", this);
    layout->addWidget(loadButton);

    connect(loadButton, &QPushButton::clicked, this, &CheckRecord::loadAllRecords);
}

void CheckRecord::loadAllRecords()
{
    readAllRecordsFromFile();
}

void CheckRecord::readAllRecordsFromFile()
{
    QString fileName = "students.dat";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file: " + fileName);
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    Student student;
    QString allRecords;
    int recordCount = 0;

    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&student), RECORD_SIZE);
        allRecords += formatStudentRecord(student) + "\n\n";
        recordCount++;
    }

    file.close();

    if (recordCount > 0) {
        recordDisplay->setPlainText(allRecords);
        QMessageBox::information(this, "Success", QString("Loaded %1 student records.").arg(recordCount));
    } else {
        QMessageBox::information(this, "No Records", "No student records found in the file.");
    }
}

QString CheckRecord::formatStudentRecord(const Student& student)
{
    return QString("First Name: %1\n"
                   "Last Name: %2\n"
                   "Roll No: %3\n"
                   "Department: %4\n"
                   "Date of Birth: %5")
        .arg(QString::fromLatin1(student.firstName).trimmed())
        .arg(QString::fromLatin1(student.lastName).trimmed())
        .arg(student.rollNo)
        .arg(QString::fromLatin1(student.department).trimmed())
        .arg(student.dateOfBirth.toString("dd-MM-yyyy"));
}

void CheckRecord::closeEvent(QCloseEvent *event)
{
    recordDisplay->clear();
    event->accept();
}

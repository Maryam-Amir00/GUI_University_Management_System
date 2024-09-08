#include "checkinfo.h"
#include <QMessageBox>
#include <QLabel>

CheckInfo::CheckInfo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Student Records");
    resize(400, 300);

    layout = new QVBoxLayout(this);

    recordDisplay = new QTextEdit(this);
    recordDisplay->setReadOnly(true);
    layout->addWidget(recordDisplay);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *label = new QLabel("Roll Number:", this);
    inputLayout->addWidget(label);

    rollNoInput = new QLineEdit(this);
    inputLayout->addWidget(rollNoInput);

    loadButton = new QPushButton("Load Record", this);
    inputLayout->addWidget(loadButton);

    layout->addLayout(inputLayout);

    connect(loadButton, &QPushButton::clicked, this, &CheckInfo::loadRecord);
}

void CheckInfo::loadRecord()
{
    bool ok;
    int rollNo = rollNoInput->text().toInt(&ok);
    if (ok && rollNo > 0) {
        readRecordFromFile(rollNo);
    } else {
        QMessageBox::warning(this, "Error", "Please enter a valid roll number.");
    }
}

void CheckInfo::readRecordFromFile(int rollNo)
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
    bool found = false;

    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&student), RECORD_SIZE);
        if (student.rollNo == rollNo) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        QString recordText = formatStudentRecord(student);
        recordDisplay->setPlainText(recordText);
    } else {
        QMessageBox::information(this, "Not Found", "No record found for the given roll number.");
    }
}

QString CheckInfo::formatStudentRecord(const Student& student)
{
    return QString("First Name: %1\n"
                   "Last Name: %2\n"
                   "Roll No: %3\n"
                   "Department: %4\n"
                   "Date of Birth: %5")
        .arg(QString::fromLatin1(student.firstName))
        .arg(QString::fromLatin1(student.lastName))
        .arg(student.rollNo)
        .arg(QString::fromLatin1(student.department))
        .arg(student.dateOfBirth.toString("dd-MM-yyyy"));
}

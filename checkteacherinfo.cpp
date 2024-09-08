#include "checkteacherinfo.h"
#include <QMessageBox>
#include <QLabel>

CheckTeacherInfo::CheckTeacherInfo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Teacher Records");
    resize(400, 300);

    layout = new QVBoxLayout(this);

    recordDisplay = new QTextEdit(this);
    recordDisplay->setReadOnly(true);
    layout->addWidget(recordDisplay);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *label = new QLabel("Teacher ID:", this);
    inputLayout->addWidget(label);

    idInput = new QLineEdit(this);
    inputLayout->addWidget(idInput);

    loadButton = new QPushButton("Load Record", this);
    inputLayout->addWidget(loadButton);

    layout->addLayout(inputLayout);

    connect(loadButton, &QPushButton::clicked, this, &CheckTeacherInfo::loadRecord);
}

void CheckTeacherInfo::loadRecord()
{
    bool ok;
    int id = idInput->text().toInt(&ok);
    if (ok && id > 0) {
        readRecordFromFile(id);
    } else {
        QMessageBox::warning(this, "Error", "Please enter a valid teacher ID.");
    }
}

void CheckTeacherInfo::readRecordFromFile(int id)
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
    bool found = false;

    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&teacher), RECORD_SIZE);
        if (teacher.id == id) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        QString recordText = formatTeacherRecord(teacher);
        recordDisplay->setPlainText(recordText);
    } else {
        QMessageBox::information(this, "Not Found", "No record found for the given teacher ID.");
    }
}

QString CheckTeacherInfo::formatTeacherRecord(const Teacher& teacher)
{
    return QString("First Name: %1\n"
                   "Last Name: %2\n"
                   "ID: %3\n"
                   "Course: %4")
        .arg(QString::fromLatin1(teacher.firstName))
        .arg(QString::fromLatin1(teacher.lastName))
        .arg(teacher.id)
        .arg(QString::fromLatin1(teacher.course));
}



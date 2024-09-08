#include "teacherexist.h"
#include <cstring>

TeacherExist::TeacherExist(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Check Teacher Existence");
    resize(300, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    idEdit = new QLineEdit(this);
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    courseEdit = new QLineEdit(this);
    checkExistenceButton = new QPushButton("Check Existence", this);

    layout->addWidget(new QLabel("ID:"));
    layout->addWidget(idEdit);
    layout->addWidget(new QLabel("First Name:"));
    layout->addWidget(firstNameEdit);
    layout->addWidget(new QLabel("Last Name:"));
    layout->addWidget(lastNameEdit);
    layout->addWidget(new QLabel("Course:"));
    layout->addWidget(courseEdit);
    layout->addWidget(checkExistenceButton);

    connect(checkExistenceButton, &QPushButton::clicked, this, &TeacherExist::onCheckExistenceClicked);
}

void TeacherExist::onCheckExistenceClicked()
{
    Teacher teacherToCheck;

    bool ok;
    teacherToCheck.id = idEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid ID");
        return;
    }
    strncpy(teacherToCheck.firstName, firstNameEdit->text().toUtf8().constData(), 25);
    teacherToCheck.firstName[25] = '\0';
    strncpy(teacherToCheck.lastName, lastNameEdit->text().toUtf8().constData(), 25);
    teacherToCheck.lastName[25] = '\0';
    strncpy(teacherToCheck.course, courseEdit->text().toUtf8().constData(), 25);
    teacherToCheck.course[25] = '\0';

    if (checkTeacherExistence(teacherToCheck)) {
        QMessageBox::information(this, "Existence Check", "The teacher with the given details exists in the file.");
    } else {
        QMessageBox::information(this, "Existence Check", "The teacher with the given details does not exist in the file.");
    }
}

bool TeacherExist::checkTeacherExistence(const Teacher& teacher)
{
    QFile file("teachers.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    Teacher fileTeacher;
    while (!in.atEnd()) {
        in.readRawData(reinterpret_cast<char*>(&fileTeacher), sizeof(Teacher));
        if (fileTeacher.id == teacher.id &&
            strcmp(fileTeacher.firstName, teacher.firstName) == 0 &&
            strcmp(fileTeacher.lastName, teacher.lastName) == 0 &&
            strcmp(fileTeacher.course, teacher.course) == 0) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

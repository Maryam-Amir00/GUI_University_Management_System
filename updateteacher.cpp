#include "updateteacher.h"

updateteacher::updateteacher(QWidget *parent)
    : QDialog(parent), currentPosition(-1)
{
    setWindowTitle("Update Teacher Record");
    resize(300, 250);

    QVBoxLayout *layout = new QVBoxLayout(this);

    idEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    courseEdit = new QLineEdit(this);
    updateButton = new QPushButton("Update", this);

    layout->addWidget(new QLabel("ID:"));
    layout->addWidget(idEdit);
    layout->addWidget(searchButton);
    layout->addWidget(new QLabel("First Name:"));
    layout->addWidget(firstNameEdit);
    layout->addWidget(new QLabel("Last Name:"));
    layout->addWidget(lastNameEdit);
    layout->addWidget(new QLabel("Course:"));
    layout->addWidget(courseEdit);
    layout->addWidget(updateButton);

    connect(searchButton, &QPushButton::clicked, this, &updateteacher::onSearchClicked);
    connect(updateButton, &QPushButton::clicked, this, &updateteacher::onUpdateClicked);

    enableUpdateFields(false);
}

void updateteacher::onSearchClicked()
{
    bool ok;
    int id = idEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid ID");
        return;
    }

    if (findTeacher(id)) {
        firstNameEdit->setText(currentTeacher.firstName);
        lastNameEdit->setText(currentTeacher.lastName);
        courseEdit->setText(currentTeacher.course);
        enableUpdateFields(true);
    } else {
        QMessageBox::warning(this, "Error", "Teacher not found");
        enableUpdateFields(false);
        clearInputFields();
    }
}

void updateteacher::onUpdateClicked()
{
    strncpy(currentTeacher.firstName, firstNameEdit->text().toUtf8().constData(), 25);
    currentTeacher.firstName[25] = '\0';
    strncpy(currentTeacher.lastName, lastNameEdit->text().toUtf8().constData(), 25);
    currentTeacher.lastName[25] = '\0';
    strncpy(currentTeacher.course, courseEdit->text().toUtf8().constData(), 25);
    currentTeacher.course[25] = '\0';

    updateTeacherInFile();
    QMessageBox::information(this, "Success", "Teacher record updated successfully");
    enableUpdateFields(false);
    clearInputFields();
}

bool updateteacher::findTeacher(int id)
{
    QFile file("teachers.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    while (!in.atEnd()) {
        currentPosition = file.pos();
        in.readRawData(reinterpret_cast<char*>(&currentTeacher), sizeof(Teacher));
        if (currentTeacher.id == id) {
            file.close();
            return true;
        }
    }

    file.close();
    currentPosition = -1;
    return false;
}

void updateteacher::updateTeacherInFile()
{
    QFile file("teachers.dat");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Could not open file for writing");
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    file.seek(currentPosition);
    out.writeRawData(reinterpret_cast<const char*>(&currentTeacher), sizeof(Teacher));

    file.close();
}

void updateteacher::enableUpdateFields(bool enable)
{
    firstNameEdit->setEnabled(enable);
    lastNameEdit->setEnabled(enable);
    courseEdit->setEnabled(enable);
    updateButton->setEnabled(enable);
}

void updateteacher::clearInputFields()
{
    idEdit->clear();
    firstNameEdit->clear();
    lastNameEdit->clear();
    courseEdit->clear();
}

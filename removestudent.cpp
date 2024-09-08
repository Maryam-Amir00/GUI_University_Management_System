#include "removestudent.h"
#include "ui_removestudent.h"

removestudent::removestudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::removestudent)
{
    ui->setupUi(this);
}

removestudent::~removestudent()
{
    delete ui;
}

void removestudent::onConfirmClicked()
{
    int rollNo = ui->rollNoEdit->text().toInt(); // Convert directly to int

    // Attempt to remove student data
    try {
        if (removeStudentData(rollNo)) {
            QMessageBox::information(this, "Success", "Student removed successfully!");
        } else {
            QMessageBox::warning(this, "Invalid Roll No", "Roll number does not exist.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}


bool removestudent::removeStudentData(int rollNo)
{
    QFile file("students.dat");
    if (!file.open(QIODevice::ReadWrite)) {
        throw std::runtime_error("Failed to open the file.");
    }

    QFile tempFile("temp.dat");
    if (!tempFile.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Failed to open the temporary file.");
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    QDataStream out(&tempFile);
    out.setVersion(QDataStream::Qt_5_0);

    bool found = false;
    while (!in.atEnd()) {
        Student student;
        in.readRawData(reinterpret_cast<char*>(&student), sizeof(Student));
        if (student.rollNo == rollNo) {
            found = true;
        } else {
            out.writeRawData(reinterpret_cast<const char*>(&student), sizeof(Student));
        }
    }

    file.close();
    tempFile.close();

    if (!found) {
        tempFile.remove();
        return false; // Roll number not found
    }

    if (!QFile::remove("students.dat") || !QFile::rename("temp.dat", "students.dat")) {
        throw std::runtime_error("Failed to replace the original file.");
    }

    return true; // Roll number found and student removed
}


void removestudent::on_pushButton_clicked()
{
    onConfirmClicked();
    ui->rollNoEdit->clear();
}

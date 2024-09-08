#include "removeteacher.h"
#include "ui_removeteacher.h"

removeteacher::removeteacher(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::removeteacher)
{
    ui->setupUi(this);
}

removeteacher::~removeteacher()
{
    delete ui;
}

void removeteacher::onConfirmClicked()
{
    int id = ui->idEdit->text().toInt(); // Convert directly to int

    // Attempt to remove teacher data
    try {
        if (removeTeacherData(id)) {
            QMessageBox::information(this, "Success", "Teacher removed successfully!");
        } else {
            QMessageBox::warning(this, "Invalid ID", "Teacher ID does not exist.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

bool removeteacher::removeTeacherData(int id)
{
    QFile file("teachers.dat");

    if (!file.open(QIODevice::ReadWrite)) {
        throw std::runtime_error("Failed to open the file.");
    }

    QFile tempFile("teachers_temp.dat");
    if (!tempFile.open(QIODevice::ReadWrite)) {
        file.close();
        throw std::runtime_error("Failed to create temporary file.");
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);

    QDataStream out(&tempFile);
    out.setVersion(QDataStream::Qt_5_0);

    bool found = false;
    while (!in.atEnd()) {
        Teacher teacher;
        in.readRawData(reinterpret_cast<char*>(&teacher), sizeof(Teacher));
        if (teacher.id == id) {
            found = true;
        } else {
            out.writeRawData(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));
        }
    }

    file.close();
    tempFile.close();

    if (!found) {
        tempFile.remove(); // Remove temporary file
        return false; // Teacher ID not found
    }

    // Replace original file with temporary file
    if (!file.remove()) {
        tempFile.remove();
        throw std::runtime_error("Failed to remove original file.");
    }
    if (!tempFile.rename("teachers.dat")) {
        throw std::runtime_error("Failed to rename temporary file.");
    }

    return true; // Teacher ID found and teacher removed
}


void removeteacher::on_pushButton_clicked()
{
    onConfirmClicked();
    ui->idEdit->clear();
}

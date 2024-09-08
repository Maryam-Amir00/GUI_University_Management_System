#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptradminauthenticate = new adminauthenticate();
    ptrstudentauthenticate = new studentauthenticate();
    ptrteacherauthenticate = new teacherauthenticate();
}

MainWindow::~MainWindow()
{
    delete ptradminauthenticate;
    delete ptrstudentauthenticate;
    delete ptrteacherauthenticate;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ptradminauthenticate->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrstudentauthenticate->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ptrteacherauthenticate->show();
}


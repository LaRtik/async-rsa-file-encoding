#include "mainwindow.h"
#include "encryptwindow.h"
#include "ui_mainwindow.h"
#include "encryptwindow.h"
#include "decryptwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    EncryptWindow encryptwindow;
    encryptwindow.setModal(true);
    encryptwindow.exec();
    encryptwindow.show();
}


void MainWindow::on_pushButton_2_clicked()
{
    DecryptWindow decryptwindow;
    decryptwindow.setModal(true);
    decryptwindow.exec();
    decryptwindow.show();
}


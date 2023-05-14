#include "decryptwindow.h"
#include "ui_decryptwindow.h"
#include <QFileDialog.h>

DecryptWindow::DecryptWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecryptWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

DecryptWindow::~DecryptWindow()
{
    delete ui;
}

void DecryptWindow::on_pushButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для расшифрования", "D:\\");
    //qDebug() << fileName;
    ui->textBrowser->setText(fileName);
}


void DecryptWindow::on_pushButton_2_clicked()
{
    QString folderName;
    folderName = QFileDialog::getExistingDirectory(this, "Выбрать папку назначения", "D:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << fileName;
    ui->textBrowser_2->setText(folderName);
}


void DecryptWindow::on_pushButton_4_clicked()
{
    QString fileNameKey;
    fileNameKey = QFileDialog::getOpenFileName(this, "Выбрать файл с ключами", "D:\\");
    //qDebug() << fileName;
    ui->textBrowser_3->setText(fileNameKey);
}


#include "encryptwindow.h"
#include "ui_encryptwindow.h"
#include "QFileDialog"


EncryptWindow::EncryptWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncryptWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

EncryptWindow::~EncryptWindow()
{
    delete ui;
}

void EncryptWindow::on_pushButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для шифрования", "C:\\");
    //qDebug() << fileName;
    ui->textBrowser->setText(fileName);
}


void EncryptWindow::on_pushButton_2_clicked()
{
    QString folderName;
    folderName = QFileDialog::getExistingDirectory(this, "Выбрать папку назначения", "C:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << fileName;
    ui->textBrowser_2->setText(folderName);
}


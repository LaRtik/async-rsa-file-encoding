#include "encryptwindow.h"
#include "ui_encryptwindow.h"
#include "QFileDialog"
#include <QMessageBox>
#include <rsaparallel.h>
#include <QString>
#include <string>


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
    fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для шифрования", "D:\\");
    //qDebug() << fileName;
    ui->textBrowser->setText(fileName);
}


void EncryptWindow::on_pushButton_2_clicked()
{
    QString folderName;
    folderName = QFileDialog::getExistingDirectory(this, "Выбрать папку назначения", "D:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << fileName;
    ui->textBrowser_2->setText(folderName);
}


void EncryptWindow::on_pushButton_3_clicked()
{
    bool success = false;
    QString fileName = ui->textBrowser->toPlainText(); // Получаем имя файла для расшифровки из QTextBrowser
    QString folderName = ui->textBrowser_2->toPlainText(); // Получаем имя файла с ключами из QTextBrowser

    try
    {
        QFile file(fileName); // Открываем файл для чтения
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("Не удалось открыть файл для расшифровки."); // Генерируем исключение, если файл не удалось открыть
        }

        try
        {
            QMessageBox informationBox;
            informationBox.setIcon(QMessageBox::Information);
            informationBox.setWindowTitle("Ожидайте");
            informationBox.setText("В данный момент происходит шифрование вашего файла. Подождите пожалуйста.");
            informationBox.addButton(QMessageBox::Ok);
            informationBox.show();

            RSAParallel rsa;
            //rsa.decrypt(fileName.toStdString(), folderName.toStdString());

            informationBox.close();
        }
        catch (const std::exception& e)
        {
            QMessageBox::critical(this, "Ошибка", e.what());
        }

        file.close(); // Закрываем файл после использования
        success = true;
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }

    if(success)
        QMessageBox::information(this, "Успех", "Ваш файл успешно зашифрован и находится по указанному вами пути вместе с файлом, содержащим ключи.");
}


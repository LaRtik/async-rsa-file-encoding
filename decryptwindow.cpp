#include "decryptwindow.h"
#include "ui_decryptwindow.h"
#include <QFileDialog.h>
#include <QMessageBox>
#include <rsaparallel.h>
#include <QString>
#include <string>


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


void DecryptWindow::on_pushButton_3_clicked()
{
    bool success = false;
    QString fileName = ui->textBrowser->toPlainText(); // Получаем имя файла для расшифровки из QTextBrowser
    QString fileNameKey = ui->textBrowser_3->toPlainText(); // Получаем имя файла с ключами из QTextBrowser
    QString folderName = ui->textBrowser_2->toPlainText(); // Получаем имя файла с ключами из QTextBrowser

    try
    {
        QFile file(fileName); // Открываем файл для чтения
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("Не удалось открыть файл для расшифровки."); // Генерируем исключение, если файл не удалось открыть
        }

        QFile fileKey(fileNameKey); // Открываем файл для чтения
        if (!fileKey.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("Не удалось открыть файл с ключами."); // Генерируем исключение, если файл не удалось открыть
        }

        try
        {
            QMessageBox informationBox;
            informationBox.setIcon(QMessageBox::Information);
            informationBox.setWindowTitle("Ожидайте");
            informationBox.setText("В данный момент происходит расшифровка вашего файла. Подождите пожалуйста.");
            informationBox.addButton(QMessageBox::Ok);
            informationBox.setVisible(true);
            informationBox.show();
            QCoreApplication::processEvents();

            RSAParallel rsa;
            rsa.decrypt(fileName.toStdString(), fileNameKey.toStdString(), folderName.toStdString());

            informationBox.close();
        }
        catch (const std::exception& e)
        {
            QMessageBox::critical(this, "Ошибка", e.what());
        }

        file.close(); // Закрываем файл после использования
        success = true;

        file.close(); // Закрываем файл после использования
        fileKey.close(); // Закрываем файл после использования
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Ошибка", e.what());
    }

    if(success)
        QMessageBox::information(this, "Успех", "Ваш файл успешно расшифрован и находится по указанному вами пути.");
}


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
    QString fileName = ui->textBrowser->toPlainText(); // Получаем имя файла из QTextBrowser

    try {
        QFile file(fileName); // Открываем файл для чтения
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error("Не удалось открыть файл."); // Генерируем исключение, если файл не удалось открыть
        }

        QTextStream in(&file);
        QString key1, key2;
        in >> key1 >> key2; // Считываем два ключа из файла

        // Ваши действия с ключами
        qDebug() << "Ключ 1:" << key1;
            qDebug() << "Ключ 2:" << key2;

                                         file.close(); // Закрываем файл после использования
    }
    catch (const std::exception& e) {
        qCritical() << "Произошла ошибка:" << e.what();
    }
}


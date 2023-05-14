#include "mainwindow.h"
#include "rsaparallel.h"
#include <filesystem>
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
    //qDebug() << QDir::currentPath();
    BinaryFile bin;
    auto data = bin.read_file("D:\\Education\\sem_6\\Course_Project_code\\async-rsa-file-encoding\\in.pdf");
    qDebug() << "Data loaded!";
    auto splitted = bin.split_data(data);
    qDebug() << "Data splitted!";
    //for (const auto &i : splitted) qDebug() << i;
    RSAParallel rsa;
    qDebug() << "Debug1";
    bool crypted = rsa.crypt(splitted);
    qDebug() << "Debug2";
    auto decrypted = rsa.decrypt("");
    qDebug() << "Debug3";
    auto desplitted = bin.desplit_data(decrypted);
    qDebug() << "Debug4";
    bin.write_file(desplitted);
    //bin.write_file(result);
    qDebug() << "End";
    */

   // RSAParallel crypting;
   // crypting.crypt("in.pdf", "");
   // crypting.decrypt("crypted_data", "private.txt", "");

    return a.exec();
}

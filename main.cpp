#include "mainwindow.h"
#include "binaryfile.h"
#include "rsaparallel.h"
#include <filesystem>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    BinaryFile bin;
    auto data = bin.read_file("in.pdf");
    qDebug() << "Data loaded!";
    auto splitted = bin.split_data(data);
    qDebug() << "Data splitted!";
    //for (const auto &i : splitted) qDebug() << i;
    RSAParallel rsa;
    bool crypted = rsa.crypt(splitted);
    auto decrypted = rsa.decrypt("");
    auto desplitted = bin.desplit_data(decrypted);
    bin.write_file(desplitted);
    //bin.write_file(result);

    return a.exec();
}

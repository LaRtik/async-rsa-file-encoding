#include "rsaparallel.h"
#include "rsa.h"
#include <QDebug>
#include <cmath>
#include <thread>
#include <future>
#include <fstream>
#include "binaryfile.h"

bool RSAParallel::crypt(const std::string &file_path, const std::string &save_path)
{
    BinaryFile bin;
    auto data = bin.read_file(file_path);
    auto splitted_data = bin.split_data(data);

    data.clear();
    data.shrink_to_fit();

    RSA rsa;
    RSA::Keys keys = rsa.calculateRSAKeys();
    auto confused_data = rsa.confuseData(splitted_data, keys._public);
    splitted_data.clear();
    splitted_data.shrink_to_fit();

    rsa.cryptMessage(confused_data, keys._public, save_path);

    confused_data.clear();
    confused_data.shrink_to_fit();

    // add private key to the same dir
    std::ofstream fout(save_path + "/private.txt", std::ios::out);
    fout << keys._private.first;
    fout << "\n";
    fout << keys._private.second;
    fout.close();

    return true;
}

bool RSAParallel::decrypt(const std::string &file_path,
             const std::string &key_path,
             const std::string &save_path)
{
    std::ifstream fin(file_path, std::ios::in);
    char splitter = '\n';
    std::string acumm;
    std::vector<largeIntegerType> crypted_data;
    for (;;) {
        char c;
        fin.read(&c, sizeof(c));
        //Debug() << c;
        if (!fin.good())
            break;
        if (c == splitter) {
            crypted_data.push_back(std::stoll(acumm));
            acumm.clear();
        }

        else
            acumm += c;
    }
    //qDebug() << "Crypted data";
    //for (auto s : crypted_data)
    //    qDebug() << s;
    fin.close();


    std::ifstream kin(key_path, std::ios::in);
    std::pair<largeIntegerType, largeIntegerType> _private;
    kin >> _private.first;
    kin >> _private.second;
    RSA rsa;
    auto confused_data = rsa.encryptMessage(crypted_data, _private);

    //qDebug() << "Encrypted confused data";
    //for (auto s : crypted_data)
    //    qDebug() << s;
    auto data = rsa.deconfuseData(confused_data, _private);
    confused_data.clear();
    confused_data.shrink_to_fit();

    BinaryFile bin;
    auto desplitted = bin.desplit_data(data);
    data.clear();
    data.shrink_to_fit();
    bin.write_file(desplitted, save_path);
    return true;
}



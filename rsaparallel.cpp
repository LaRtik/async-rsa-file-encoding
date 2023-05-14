#include "rsaparallel.h"
#include <QDebug>
#include <cmath>
#include <thread>
#include <future>
#include <fstream>


bool RSAParallel::crypt(std::vector<std::string> splitted_data, const std::string &path)
{
    //for (auto s : splitted_data)
    //    qDebug() << s;
    auto confused_data = rsa.confuseData(splitted_data, keys._public);
    qDebug() << "Data confused!";
    auto crypted_data = rsa.cryptMessage(confused_data, keys._public);

    // add private key to the same dir
    std::ofstream fout(path + "private.txt", std::ios::out);
    fout << keys._private.first;
    fout << "\n";
    fout << keys._private.second;
    fout.close();

    return true;
}

std::vector <std::string> RSAParallel::decrypt(const std::string &path_to_data, const std::string &path_to_key)
{
    std::ifstream fin(path_to_data, std::ios::in);
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


    std::ifstream kin(path_to_key, std::ios::in);
    std::pair<largeIntegerType, largeIntegerType> _private;
    kin >> _private.first;
    kin >> _private.second;
    auto confused_data = rsa.encryptMessage(crypted_data, _private);

    //qDebug() << "Encrypted confused data";
    //for (auto s : crypted_data)
    //    qDebug() << s;
    auto data = rsa.deconfuseData(confused_data, _private);
    return data;
}



#include "rsaparallel.h"
#include <QDebug>
#include <cmath>
#include <thread>
#include <future>


bool RSAParallel::crypt(std::vector<std::string> splitted_data)
{
    //for (auto s : splitted_data)
    //    qDebug() << s;
    auto confused_data = rsa.confuseData(splitted_data, keys._public);
    qDebug() << "Data confused!";
    auto crypted_data = rsa.cryptMessage(confused_data, keys._public);

    return true;
}

std::vector <std::string> RSAParallel::decrypt(const std::string &path)
{
    std::ifstream fin("crypted_data", std::ios::in);
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


    auto confused_data = rsa.encryptMessage(crypted_data, keys._private);

    //qDebug() << "Encrypted confused data";
    //for (auto s : crypted_data)
    //    qDebug() << s;
    auto data = rsa.deconfuseData(confused_data, keys._public);
    return data;
}



#ifndef RSA_H
#define RSA_H
#include "utils.h"

#include <algorithm>
#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <QDebug>

class RSA
{
public:
    struct Keys
    {
        std::pair<largeIntegerType, largeIntegerType> _public;
        std::pair<largeIntegerType, largeIntegerType> _private;
    };

    Keys calculateRSAKeys();

    largeIntegerType cryptData(largeIntegerType data, std::pair<largeIntegerType, largeIntegerType> _publicKey);

    largeIntegerType encryptData(largeIntegerType data, std::pair<largeIntegerType, largeIntegerType> _privateKey);

    bool cryptMessage(std::vector <largeIntegerType> data, std::pair<largeIntegerType, largeIntegerType> _publicKey, std::string path = "");

    std::vector <largeIntegerType> encryptMessage(const std::vector<largeIntegerType> &data, std::pair<largeIntegerType, largeIntegerType> _privateKey);

    std::vector<largeIntegerType> confuseData(const std::vector <std::string> &data, std::pair<largeIntegerType, largeIntegerType>_anyKey);

    std::vector <std::string> deconfuseData(const std::vector <largeIntegerType> &confusedData, std::pair<largeIntegerType, largeIntegerType> _anyKey);

    std::vector<long long> encr(const std::vector<long long> &data,
                                int l,
                                int r,
                                std::pair<largeIntegerType, largeIntegerType> _private);

};

#endif // RSA_H

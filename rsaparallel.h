#ifndef RSAPARALLEL_H
#define RSAPARALLEL_H

#include <vector>
#include <string>
#include "rsa.h"

class RSAParallel
{
public:
    RSA rsa = RSA();
    RSA::Keys keys = rsa.calculateRSAKeys();
    bool crypt(std::vector<std::string> splitted_data, const std::string &path = "");
    std::vector <std::string> decrypt(const std::string &path_to_data, const std::string &path_to_key);
};

#endif // RSAPARALLEL_H

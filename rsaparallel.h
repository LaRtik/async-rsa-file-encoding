#ifndef RSAPARALLEL_H
#define RSAPARALLEL_H

#include <vector>
#include <string>

class RSAParallel
{
public:
    //RSA rsa = RSA();
    //RSA::Keys keys = rsa.calculateRSAKeys();
    bool crypt(const std::string &file_path, const std::string &save_path);
    bool decrypt(const std::string &file_path,
                 const std::string &key_path,
                 const std::string &save_path);
    //bool crypt(std::vector<std::string> splitted_data, const std::string &path = "");
    //std::vector <std::string> decrypt(const std::string &path_to_data, const std::string &path_to_key);
};

#endif // RSAPARALLEL_H

#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <vector>
#include <string>
#include <fstream>
#include <QDebug>
#include <QFile>

class BinaryFile
{
public:
    BinaryFile();
    std::vector <char> read_file(const std::string &path);
    void write_file(const std::vector<char>& data);
    std::vector <std::string> split_data(const std::vector <char> &data);
    std::vector<char> desplit_data(const std::vector<std::string> &splitted_data);
};

#endif // BINARYFILE_H

#include "binaryfile.h"


BinaryFile::BinaryFile()
{

}

std::vector <char> BinaryFile::read_file(const std::string &path)
{
    std::ifstream fin;
    fin.open(path, std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        //qDebug() << "Error reading file";
        return {};
    }
    std::vector <char> data;
    // add 24 bytes with file extension
    std::string extension;
    for (int i = path.size() - 1; i!= 0; i--)
    {
        extension = path[i] + extension;
        if (path[i] == '.') break;
    }

    while (extension.size() < 23) extension.push_back('0');
    for (const auto &c : extension) data.push_back(c);
    //qDebug() << data.size();

    for (;;)
    {
        char c;
        fin.read(&c, sizeof(c));
        if (!fin.good()) break;
        //qDebug() << int(c);
        data.push_back(c);
    }
    return data;
}


void BinaryFile::write_file(const std::vector<char> &data)
{
    std::ofstream fout;
    std::string path = "out";
    for (int i = 0; i < 23; i++)
    {
        if (data[i] != '0') path += data[i];
        else break;
    }

    fout.open(path, std::ios::out | std::ios::binary);
    for (int i = 23; i < int(data.size()); i++)
    {
        char c = data[i];
        fout.write(&c, sizeof(c));
    }
    fout.close();
}

std::vector <std::string> BinaryFile::split_data(const std::vector <char> &data)
{
    std::vector <std::string> result;
    for (const auto &c : data)
    {
        int16_t value = c + 128;
        std::string s_value = std::to_string(value);
        while (s_value.size() < 3) s_value = '0' + s_value;
        result.push_back(s_value);
    }
    return result;
}

std::vector<char> BinaryFile::desplit_data(const std::vector<std::string> &splitted_data)
{
    std::vector<char> result;
    for (const auto &s : splitted_data) {
        int16_t value = std::stoi(s);
        value -= 128;
        result.push_back(char(value));
    }
    return result;
}

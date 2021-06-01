/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#include "ConfigFile.hpp"

ConfigFile::ConfigFile()
{
}

ConfigFile::ConfigFile(const std::string &filename)
{
    this->loadFile(filename);
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::loadFile(const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    std::regex isAscii ("^[\\x00-\\x7F]+$");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (!std::regex_search(line, isAscii) && !line.empty()) {
                break;
            } else {
                _fileContent.push_back(line);
            }
        }
    } else {
        throw std::invalid_argument("File close");
    }
}

int ConfigFile::getInt(const std::string name) const
{
    return 0;
}

float ConfigFile::getFloat(const std::string name) const
{
    return 0.0;
}

std::string ConfigFile::getString(const std::string name) const
{
    return std::string("");
}